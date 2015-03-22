#include <string>
#include <vector>
#include "serial/serial.h"

class SIM900
{
private:
	std::string port;
	int baud;
	int timeout;
	serial::Serial serial_device;
	bool sendMessage(std::string message);
	//void addMessageListener(std::function& callback);
public:
	SIM900(std::string port, int baud, int timeout);
	bool sendSMS(std::string phone_number, std::string message);
	std::vector<std::string> getMessages();
};
