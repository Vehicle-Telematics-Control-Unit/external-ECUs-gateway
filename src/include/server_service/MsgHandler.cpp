#include "MsgHandler.hpp"
#include <json.hpp>

MsgHandler::MsgHandler(std::shared_ptr<ServiceManagerAdapter> servManger, std::shared_ptr<std::vector<uint16_t>> events)
    : serviceManager{servManger},
      msgHandlerEvents{events}
{
}

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
    case (int)SRC_PORTS::SPEED_PORT:
        currentEvent = msgHandlerEvents->front();
        msgType = MSG_TYPE::DSRC;
        break;
    case (int)SRC_PORTS::HEADING_PORT:
        currentEvent = msgHandlerEvents->back();
        msgType = MSG_TYPE::DSRC;
        break;
    case (int)SRC_PORTS::TYRES_PORT:
        jsonMessage["code"] = "C1234";
        jsonMessage["description"] = "Tyre pressure";
        msgType = MSG_TYPE::DIAGNOSTIC;
        break;
    case (int)SRC_PORTS::BATTERY_PORT:
        jsonMessage["code"] = "P0562";
        jsonMessage["description"] = "Main 12v battery";
        msgType = MSG_TYPE::DIAGNOSTIC;
        break;
    case (int)SRC_PORTS::HEAD_LIGHT_PORT:
        jsonMessage["code"] = "B2425";
        jsonMessage["description"] = "Head lights";
        msgType = MSG_TYPE::DIAGNOSTIC;
        break;
    default:
        break;
    }

    if (msgType == MSG_TYPE::DIAGNOSTIC)
    {
        std::string message = jsonMessage.dump(4);
        serviceManager->waitForServiceToBeAvailable(REQUEST_SERVICE_ID, REQUEST_INSTANCE_ID);
        serviceManager->SendRequest(REQUEST_SERVICE_ID, REQUEST_INSTANCE_ID, REQUEST_METHOD_ID, std::vector<uint8_t>(message.begin(), message.end()));
        std::cout << "request sent!!!\n";
    }
    else
    {
        std::cout << "updated event!!!\n";
        std::vector<uint8_t> dataToBeSent(data.begin(), data.end());
        serviceManager->updateEvent(currentEvent, dataToBeSent);
    }
}