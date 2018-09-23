#include "Arduino.h"

class CommunicationController {
  typedef void (*CommandCallback)(String command, int value);

  public:
    CommunicationController();
    void setup(unsigned long speed);
    void update();
    void setCommandCallback(CommandCallback callback);
    void sendCommand(const char* command, unsigned int payload);
    void sendCommand(const char* command, int payload);
    void sendCommand(const char* command, String payload);
  
  private:
    CommandCallback _commandCallback;
};
