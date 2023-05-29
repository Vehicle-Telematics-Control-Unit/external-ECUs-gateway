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
    using json = nlohmann::json;
    json jsonMessage = {
        {"route", "tests"},
        {"code", ""},
        {"state", ""},
        {"description", ""},
    };
    jsonMessage["state"] = 
        (stoi(data) == (uint8_t)DIAG_STATE::OKAY) ? "OKAY" : "FAULTY";

    switch (endpoint.port())
    {
    case SRC_PORTS::TYRES_PORT:
        jsonMessage["code"]= "C1234";
        jsonMessage["description"]= "Tyre pressure";
        break;
    case SRC_PORTS::BATTERY_PORT:
        jsonMessage["code"]= "P0562";
        jsonMessage["description"]= "Main 12v battery";
        break;
    case SRC_PORTS::HEAD_LIGHT_PORT:
        jsonMessage["code"]= "B2425";
        jsonMessage["description"]= "Head lights";
        break;
    default:
        break;
    }

    std::string message = jsonMessage.dump(4);
    serviceManager->SendRequest(REQUEST_SERVICE_ID, REQUEST_INSTANCE_ID, REQUEST_METHOD_ID, std::vector<uint8_t>(message.begin(), message.end()));
    std::cout << "request sent!!!\n";
}