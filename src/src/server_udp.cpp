#include <Server.hpp>

void on_message(const std::shared_ptr<vsomeip::message> &_response)
{

    std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
    vsomeip::length_t l = its_payload->get_length();

    // Get payload
    std::stringstream ss;
    for (vsomeip::length_t i = 0; i < l; i++)
    {
        ss << *(its_payload->get_data() + i) << " ";
    }

    std::cout << ss.str() << std::endl;
}

int main()
{
    std::shared_ptr<ServiceManagerAdapter> vsomeService_shared = std::make_shared<ServiceManagerAdapter>(0x1235, 0x5679, EVENTGROUP_ID, "Hello");
    std::shared_ptr<std::vector<uint16_t>> events = std::make_shared<std::vector<uint16_t>>();
    events->push_back(DSRC_EVENT_ID);
    events->push_back(DIAGNOSTIC_EVENT_ID);
    if (!vsomeService_shared->init())
    {
        std::cerr << "Couldn't initialize vsomeip services" << std::endl;
        return -1;
    }
    std::vector<ServiceManagerAdapter::METHOD> methods;
    methods.push_back({METHOD_ID, on_message});
    vsomeService_shared->requestServicesANDRegisterMethods(SERVICE_ID, INSTANCE_ID, methods);
    vsomeService_shared->offer();
    Server server(PORT, vsomeService_shared, events);
    server.Start();
    return 0;
}