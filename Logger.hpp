#pragma once
#include <string_view>

namespace LibWeb
{
	class Logger
	{
	public:
		static void throw_runtime_error(std::string_view error_msg);
		static void throw_sys_error_msg();
		static char* sys_error_msg();
	};

}
