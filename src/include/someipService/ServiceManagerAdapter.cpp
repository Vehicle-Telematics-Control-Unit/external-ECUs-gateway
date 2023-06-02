#include "ServiceManagerAdapter.hpp"

ServiceManagerAdapter::ServiceManagerAdapter(const uint16_t &service_id, const uint16_t &instance_id, const std::string &name)
    : m_service_id(service_id),
      m_instance_id(instance_id),
      m_app_(vsomeip::runtime::get()->create_application(name))
{
}

ServiceManagerAdapter::ServiceManagerAdapter(const uint16_t &service_id, const uint16_t &instance_id, const uint16_t &event_group_id, const std::string &name)
    : m_service_id(service_id),
      m_instance_id(instance_id),
      m_app_(vsomeip::runtime::get()->create_application(name))
{
    its_groups.insert(event_group_id);
}

void ServiceManagerAdapter::start()
{
    m_app_->start();
}

bool ServiceManagerAdapter::init()
{
    if (!m_app_->init())
    {
        std::cerr << "Couldn't initialize application" << '\n';
        return false;
    }
    return true;
}

void ServiceManagerAdapter::offer()
{
    m_app_->offer_service(m_service_id, m_instance_id);
}

void ServiceManagerAdapter::addEvent(const uint16_t &event)
{
    m_events[event];
}

void ServiceManagerAdapter::updateEvent(const uint16_t &event, const std::vector<uint8_t> &payload)
{
    std::unique_lock<std::mutex> its_lock(m_mutex_);
    m_events[event].payload = std::move(payload);
    m_events[event].active = true;
    m_condition_.notify_all();
}

void ServiceManagerAdapter::offerEvents()
{
    for (const auto &event : m_events)
    {
        m_app_->offer_event(m_service_id, m_instance_id, event.first, its_groups);
        threads.push_back(std::move(std::thread([event, this]()
                                                {
            for(;;)
            {
                std::unique_lock<std::mutex> its_lock(m_mutex_);
                while(!m_events[event.first].active)
                    m_condition_.wait(its_lock);
                std::shared_ptr<vsomeip::payload> payload = vsomeip::runtime::get()->create_payload();
                payload->set_data(m_events[event.first].payload);
                m_app_->notify(m_service_id,m_instance_id,event.first,payload);
                m_events[event.first].active=false;
            } })));
    }
}

// void ServiceManagerAdapter::addMethod(const uint16_t &method, const std::function<void(const std::shared_ptr<vsomeip::message> &)> callback)
// {
//     methods.push_back({method, callback});
// }

void ServiceManagerAdapter::requestServicesANDRegisterMethods(const uint16_t &service_id, const uint16_t &instance_id, const std::vector<METHOD> &methods)
{
    serviceAvailable[service_id + instance_id] = false;
    m_app_->register_availability_handler(service_id, instance_id, [this](vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
                                          {
                                              std::cout << "CLIENT: Service ["
                                                        << std::hex << _service << "." << _instance
                                                        << "] is "
                                                        << (_is_available ? "available." : "NOT available.")
                                                        << std::endl;
                                              serviceAvailable[_service + _instance] = true;
                                              m_condition_.notify_one(); });
    m_app_->request_service(service_id, instance_id);
    for (auto method : methods)
        m_app_->register_message_handler(service_id, instance_id, method.method_id, method.callback);
    std::cout << "checking for service!!!\n";
}

void ServiceManagerAdapter::waitForServiceToBeAvailable(const uint16_t service_id, const uint16_t instance_id)
{
    std::unique_lock<std::mutex> its_lock(m_mutex_);
    while (!serviceAvailable[service_id + instance_id])
        m_condition_.wait(its_lock);
}

void ServiceManagerAdapter::subOnEvent(const uint16_t service_id, const uint16_t instance_id, const uint16_t event_id)
{
    waitForServiceToBeAvailable(service_id, instance_id);
    m_app_->request_event(service_id, instance_id, event_id, its_groups);
    m_app_->subscribe(service_id, instance_id, *its_groups.begin());
}

void ServiceManagerAdapter::SendRequest(uint16_t service_id, uint16_t instance_id, uint16_t method_id, const std::vector<uint8_t> &payload)
{
    std::shared_ptr<vsomeip::message> request;
    request = vsomeip::runtime::get()->create_request();
    request->set_service(service_id);
    request->set_instance(instance_id);
    request->set_method(method_id);

    std::shared_ptr<vsomeip::payload> its_payload = vsomeip::runtime::get()->create_payload();
    its_payload->set_data(payload);
    request->set_payload(its_payload);
    m_app_->send(request);
}

// void ServiceManagerAdapter::registerMethods()
// {
//     for (auto method : methods)
//         m_app_->register_message_handler(m_service_id, m_instance_id, method.method_id, method.callback);
// }

void ServiceManagerAdapter::sendResponse(const std::vector<uint8_t> &payload, const std::shared_ptr<vsomeip::message> &_message)
{
    std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_message);
    std::shared_ptr<vsomeip::payload> its_payload = vsomeip::runtime::get()->create_payload();
    its_payload->set_data(payload);
    its_response->set_payload(its_payload);
    m_app_->send(its_response);
}