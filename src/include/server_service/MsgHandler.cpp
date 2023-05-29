#include "MsgHandler.hpp"
#include <json.hpp>


MsgHandler::MsgHandler(std::shared_ptr<ServiceManagerAdapter> servManger, std::shared_ptr<std::vector<uint16_t>> events)
    : serviceManager{servManger},
      msgHandlerEvents{events}
{
}

// void MsgHandler::Serialize()
// {
//     if (msgHandlerEvents->front() == currentEvent)
//     {
//         serializedMsg.resize(sizeof(msg_DSRC));
//         memcpy(serializedMsg.data(), &msgDRC, sizeof(msg_DSRC));
//     }
//     else
//     {
//         serializedMsg.resize(sizeof(msg_diagnostic));
//         memcpy(serializedMsg.data(), &msgDiagnostic, sizeof(msg_diagnostic));
//     }
// }

void MsgHandler::HandleMsg(const boost::asio::ip::udp::endpoint &endpoint, const std::string &data)
{
    std::vector<uint8_t> msg;
    switch (endpoint.port())
    {
    case SRC_PORTS::TYRES_PORT:
        for (auto i : std::string("Tyres"))
            msg.push_back(i);
        break;
    case SRC_PORTS::BATTERY_PORT:
        for (auto i : std::string("Battery"))
            msg.push_back(i);
        break;
    default:
        for (auto i : std::string("Head Light"))
            msg.push_back(i);
        break;
    }
    // using json = nlohmann::json;
    // json msg = {
    //     {"route", "test"},
    //     {"ObdCode", "B2425"},
    //     {"Description", "fault in my ass"},
    //     {"isGeneric", false}
    // };

    serviceManager->SendRequest(REQUEST_SERVICE_ID, REQUEST_INSTANCE_ID, REQUEST_METHOD_ID, msg);
    std::cout << "request sent!!!\n";
}