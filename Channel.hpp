#pragma once
#include "EventLoop.hpp"

#include <functional>
using std::function;

namespace LibWeb
{
	class Channel
	{
	public:
		virtual ~Channel() = default;
		Channel(EventLoop& loop, int fd)
		: m_fd(fd)
		{
			loop.update_channel(*this);
		}

		[[nodiscard]] const int& get_fd() const;
		[[nodiscard]] const unsigned int& get_current_event() const; 

		void set_current_event(const unsigned int& event) { m_current_event = event; }
		void set_setting_event();
		void handle_event() const;

		void set_error_callback(function<void()> func);
		void set_read_callback(function<void(int)> func);
		void set_write_callback(function<void(int)> func);

		void enable_write();
		void enable_read();
	private:
		int m_fd;
		unsigned int m_current_event;
		unsigned int m_setting_event;

		function<void(int)> m_read_callback;
		function<void(int)> m_write_callback;
		function<void()> m_error_callback;
	};
}
