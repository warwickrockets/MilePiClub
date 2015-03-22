#include <iostream>
#include <string>

#include "sim900.h"

int main()
{
	std::string phone_number = "+441111222233";
	std::string port = "/dev/ttyAMA0";
	int baud = 19200;
	int timeout = 100;

	SIM900 gsm(port, baud, timeout);
	gsm.sendSMS(phone_number, "Testing\nTesting again");

	std::vector<std::string> lines;
	lines = gsm.getMessages();
	for(const auto & line : lines)
	{
		std::cout << line;
	}
}
