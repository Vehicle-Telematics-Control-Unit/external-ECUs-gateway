#include <Server.hpp>

void on_message(const std::shared_ptr<vsomeip::message> &_response)
{

    std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
    vsomeip::length_t l = its_payload->get_length();

    // Get payload
    std::stringstream ss;
    for (vsomeip::length_t i = 0; i < l; i++)
    {
        ss << *(its_payload->get_data() + i);
    }
    ss << '\n';

    std::cout << "received a vsomeip response :" << _response << ss.str() << '\n';
}

int main()
{
    std::shared_ptr<ServiceManagerAdapter> vsomeService_shared = std::make_shared<ServiceManagerAdapter>(SERVICE_ID, INSTANCE_ID, EVENTGROUP_ID, "UDP_Service");
    if (!vsomeService_shared->init())
    {
        std::cerr << "Couldn't initialize vsomeip services" << std::endl;
        return -1;
    }
    vsomeService_shared->addEvent(SPEED_EVENT_ID);
    vsomeService_shared->addEvent(HEADING_EVENT_ID);
    std::vector<ServiceManagerAdapter::METHOD> methods;
    methods.push_back({REQUEST_METHOD_ID, on_message});
    vsomeService_shared->requestServicesANDRegisterMethods(REQUEST_SERVICE_ID, REQUEST_INSTANCE_ID, methods);
    vsomeService_shared->offer();
    vsomeService_shared->offerEvents();
    std::cout << "starting server!!!\n";
    Server server(PORT, vsomeService_shared);
    server.Start();
    return 0;
}