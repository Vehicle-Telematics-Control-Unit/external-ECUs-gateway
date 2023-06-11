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
    // msg_DSRC msgDRC{EMPTY_MESSAGE, EMPTY_MESSAGE};
    // msg_diagnostic msgDiagnostic{TYRES::TYRES_CONDITION_OKAY, BATTERY::BATTERY_OKAY, HEAD_LIGHT::HEAD_LIGHT_OKAY, OIL_LEVEL::OIL_LEVEL_OKAY};
    std::shared_ptr<ServiceManagerAdapter> serviceManager;
    uint16_t currentEvent;
    MSG_TYPE msgType;
    std::shared_ptr<std::vector<uint16_t>> msgHandlerEvents;

public:
    MsgHandler(std::shared_ptr<ServiceManagerAdapter> servManger, std::shared_ptr<std::vector<uint16_t>> events);
    void HandleMsg(const boost::asio::ip::udp::endpoint &endpoint, const std::string &data);

    // private:
    //     void Serialize();
};

#endif
