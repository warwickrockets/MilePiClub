#include "sim900.h"
#include <iostream>
#include <chrono>
#include <thread>

SIM900::SIM900(std::string _port, int _baud, int _timeout):
	serial_device(_port, _baud, serial::Timeout::simpleTimeout(_timeout))
{
	port = _port;
	baud = _baud;
	timeout = _timeout;
	auto delay = std::chrono::milliseconds(timeout);

	if(serial_device.isOpen())
		std::cout << "Connected." << std::endl;
	else
		std::cout << "Failed to connect." << std::endl;

	sendMessage("AT+IPR=" + std::to_string(baud));
	std::this_thread::sleep_for(delay);
	sendMessage("AT+CMGF=1");
	std::this_thread::sleep_for(delay);
}

bool SIM900::sendMessage(std::string message)
{
	const std::string line_end = "\r\n";
	std::string full_message = message + line_end;
	int bytes_written = serial_device.write(full_message);
	serial_device.flush();
	if(bytes_written != full_message.size())
	{
		return false;
	}
	return true;
}

bool SIM900::sendSMS(std::string phone_number, std::string message)
{
	sendMessage("AT+CMGS=\"" + phone_number + "\"");
	serial_device.flush();
	auto delay = std::chrono::milliseconds(timeout);
	std::this_thread::sleep_for(delay);

	const std::string message_end = "\x1a";
	std::string full_message = message + message_end;
	int bytes_written = serial_device.write(full_message);
	serial_device.flush();
	if(bytes_written != full_message.size())
	{
		return false;
	}
	return true;
}

std::vector<std::string> SIM900::getMessages()
{
	std::vector<std::string> result;
	result = serial_device.readlines();
	return result;
}
