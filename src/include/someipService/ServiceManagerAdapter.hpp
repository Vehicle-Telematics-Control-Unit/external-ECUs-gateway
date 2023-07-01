#ifndef __SERVICE_MANAGER_ADAPTER__
#define __SERVICE_MANAGER_ADAPTER__

#include <functional>
#include <vsomeip/vsomeip.hpp>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <atomic>
#include <map>
#include <vector>

class ServiceManagerAdapter
{
public:
    typedef struct
    {
        /* data */
        uint16_t method_id;
        std::function<void(const std::shared_ptr<vsomeip::message> &)> callback;
    } METHOD;

public:
    ServiceManagerAdapter(const uint16_t &service_id, const uint16_t &instance_id, const std::string &name);
    ServiceManagerAdapter(const uint16_t &service_id, const uint16_t &instance_id, const uint16_t &event_group_id, const std::string &name);
    void start();
    bool init();
    void addEvent(const uint16_t &event);
    void updateEvent(const uint16_t &event, const std::vector<uint8_t> &payload);
    void offer();
    void offerEvents();
    void sendResponse(const std::vector<uint8_t> &payload, const std::shared_ptr<vsomeip::message> &_message);
    void requestServicesANDRegisterMethods(const uint16_t &service_id, const uint16_t &instance_id, const std::vector<METHOD> &methods);
    void SendRequest(uint16_t service_id, uint16_t instance_id, uint16_t method_id, const std::vector<uint8_t> &payload);
    void waitForServiceToBeAvailable(const uint16_t service_id, const uint16_t instance_id);
    void subOnEvent(const uint16_t service_id, const uint16_t instance_id, const uint16_t event_id);

private:
    typedef struct
    {
        /* data */
        std::vector<uint8_t> payload;
        bool active;
    } EVENT;

    std::shared_ptr<vsomeip::application> m_app_;
    std::mutex m_mutex_;
    std::condition_variable m_condition_;
    uint16_t m_instance_id;
    uint16_t m_service_id;
    std::map<uint16_t, EVENT> m_events;
    std::vector<std::thread> threads;
    std::set<vsomeip::eventgroup_t> its_groups;
    std::vector<METHOD> methods;

public:
    std::map<uint32_t, bool> serviceAvailable;
};
#endif