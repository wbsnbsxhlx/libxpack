#include "pack_log.h"
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <stdint.h>
#include <iostream>

const uint32_t LOG_LENGTH_MAX = 1024;

void log(LogType type, const char* formatTxt, ...) {
	va_list argList;
	va_start(argList, formatTxt);

	char buf[LOG_LENGTH_MAX];

	vsprintf_s(buf, LOG_LENGTH_MAX - 1, formatTxt, argList);

#ifdef PACK_DEBUG
	std::cout << buf << std::endl;
#endif // PACK_DEBUG

	std::ofstream ofs;

	ofs.open("pack_log.log", std::ios::app);

	ofs << buf << std::endl;
	ofs.close();
}