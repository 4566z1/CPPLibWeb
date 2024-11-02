#include "Channel.hpp"
#include <sys/epoll.h>

const unsigned int& LibWeb::Channel::get_current_event() const
{
	return m_current_event;
}


const int& LibWeb::Channel::get_fd() const
{
	return m_fd;
}


void LibWeb::Channel::enable_read()
{
	m_setting_event |= EPOLLIN;
}

void LibWeb::Channel::enable_write()
{
	m_setting_event |= EPOLLOUT;
}

void LibWeb::Channel::set_error_callback(function<void()> func)
{
	m_error_callback = std::move(func);
}

void LibWeb::Channel::set_read_callback(function<void(int)> func)
{
	m_read_callback = std::move(func);
}

void LibWeb::Channel::set_write_callback(function<void(int)> func)
{
	m_write_callback = std::move(func);
}

void LibWeb::Channel::handle_event() const
{
	if(m_current_event & EPOLLIN)
	{
		if (m_read_callback) m_read_callback(m_fd);
	}
	else if(m_current_event & EPOLLOUT)
	{
		if (m_write_callback) m_write_callback(m_fd);
	}
	else
	{
		if (m_error_callback) m_error_callback();
	}
}
