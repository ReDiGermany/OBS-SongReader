#include "Logger.h"
#include <obs.h>
/// <summary>
/// Simple Logger to quickly enable/disable logging.
/// </summary>
/// <param name="inp">The Text to log</param>
Logger::Logger(std::string inp){
	if (doLog) {
		std::string l = "[SONGREADER] " + inp;
		blog(LOG_INFO, l.c_str());
	}
}
