#pragma once
#include <string>
class Logger {
public:
	Logger(std::string);
private:
	bool doLog = false;
};
