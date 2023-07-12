#ifndef __MSG_HANDLER__
#define __MSG_HANDLER__

#include <boost/asio.hpp>
#include <iostream>
#include "msg.hpp"
#include <string>
#include <serverConf.hpp>
#include <ServiceManagerAdapter.hpp>

class MsgHandler
{
private:
    /* data */
    std::shared_ptr<ServiceManagerAdapter> serviceManager;
    uint16_t currentEvent;
    MSG_TYPE msgType;

public:
    MsgHandler(std::shared_ptr<ServiceManagerAdapter> servManger);
    void HandleMsg(const boost::asio::ip::udp::endpoint &endpoint, const std::string &data);
};

#endif
