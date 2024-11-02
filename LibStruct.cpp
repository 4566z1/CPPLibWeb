#include "LibStruct.hpp"
#include "Logger.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
 *
 * EPOLL
 *
 */

LibWeb::Epoll::Epoll(const int& max_epoll_events)
{
	m_max_epoll_events = max_epoll_events;
	m_epoll_fd = epoll_create(max_epoll_events);
	if (m_epoll_fd < 0) Logger::throw_sys_error_msg();
}

void LibWeb::Epoll::set_fd(const int& fd, const unsigned& setting_event) const
{
	epoll_event event = { 0 };
	event.data.fd = fd;
	event.events = setting_event;

	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, fd, &event) < 0) Logger::throw_sys_error_msg();
}

void LibWeb::Epoll::reset_fd(const int& fd, const unsigned& setting_event) const
{
	epoll_event event = { 0 };
	event.data.fd = fd;
	event.events = setting_event;

	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, fd, &event) < 0) Logger::throw_sys_error_msg();
}

void LibWeb::Epoll::wait(const int& time_out)
{
	epoll_wait(m_epoll_fd, m_epoll_events.data(), m_max_epoll_events, time_out);
}

/*
 *
 * InetAddress
 *
 */

LibWeb::InetAddress::InetAddress(string_view address, const short& port)
{
	m_sockaddr.sin_addr.s_addr = inet_addr(address.data());
	m_sockaddr.sin_port = htons(port);
	m_sockaddr.sin_family = AF_INET;
}

/*
 *
 * Socket
 *
 */

LibWeb::Socket::Socket(const int& type, const int& protocol)
{
	m_socket_fd = socket(AF_INET, type, protocol);
}

void LibWeb::Socket::bind(const InetAddress& inet_address) const
{
	int ret = ::bind(m_socket_fd, reinterpret_cast<const sockaddr*>(&inet_address.get_sockaddr()), 
	sizeof(sockaddr));
	if (ret < 0) Logger::throw_sys_error_msg();
}

void LibWeb::Socket::listen(const int& backlog) const
{
	if (::listen(m_socket_fd, backlog) < 0) Logger::throw_sys_error_msg();
}

void LibWeb::Socket::close() const
{
	::close(m_socket_fd);
}
