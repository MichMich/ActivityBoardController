#include "CommunicationController.h"
#include <ArduinoJson.h>

CommunicationController::CommunicationController()
{
}

void CommunicationController::setup(unsigned long speed)
{
    Serial.begin(speed);
}

void CommunicationController::setCommandCallback(CommandCallback callback)
{
    _commandCallback = callback;
}

void CommunicationController::sendCommand(const char* command, unsigned int payload)
{
    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    root[command] = payload;

    root.printTo(Serial);
}

void CommunicationController::sendCommand(const char* command, int payload)
{
    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    root[command] = payload;

    root.printTo(Serial);
}

void CommunicationController::sendCommand(const char* command, String payload)
{
    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    root[command] = payload;

    root.printTo(Serial);
}