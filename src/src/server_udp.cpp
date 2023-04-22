#include <Server.hpp>
#include <serverConf.hpp>

int main()
{
    std::shared_ptr<ServiceManagerAdapter> vsomeService_shared = std::make_shared<ServiceManagerAdapter>(SERVICE_ID, INSTANCE_ID, EVENTGROUP_ID, "World");
    std::shared_ptr<std::vector<uint16_t>> events = std::make_shared<std::vector<uint16_t>>();
    events->push_back(DSRC_EVENT_ID);
    events->push_back(DIAGNOSTIC_EVENT_ID);
    if (!vsomeService_shared->init())
    {
        std::cerr << "Couldn't initialize vsomeip services" << std::endl;
        return -1;
    }
    vsomeService_shared->offer();
    Server server(PORT, vsomeService_shared, events);
    server.Start();
    return 0;
}