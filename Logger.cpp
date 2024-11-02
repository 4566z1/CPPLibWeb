#include "Logger.hpp"

#include <stdexcept>
#include <cerrno>
#include <cstring>
using std::runtime_error;

void LibWeb::Logger::throw_runtime_error(std::string_view error_msg)
{
	throw runtime_error(std::string(error_msg));
}


void LibWeb::Logger::throw_sys_error_msg()
{
	throw runtime_error(sys_error_msg());
}


char* LibWeb::Logger::sys_error_msg()
{
	return strerror(errno);
}
