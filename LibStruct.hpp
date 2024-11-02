#pragma once

#include <sys/epoll.h>
#include <netinet/in.h>

#include <vector>
#include <string_view>
using std::vector;
using std::string_view;

namespace LibWeb
{
	class Epoll
	{
	public:
		virtual ~Epoll() = default;
		Epoll(const int& max_epoll_events = 10);

		[[nodiscard]] const int& get_max_events() const { return m_max_epoll_events; }
		[[nodiscard]] const int& get_epoll_fd() const { return m_epoll_fd; }
		[[nodiscard]] const vector<epoll_event>& get_events() const { return m_epoll_events; }

		void wait(const int& time_out = -1);
		void set_fd(const int& fd, const unsigned int& setting_event) const;
		void reset_fd(const int& fd, const unsigned int& setting_event) const;
	private:
		int m_max_epoll_events;
		int m_epoll_fd;

		vector<epoll_event> m_epoll_events;
	};

	class InetAddress
	{
	public:
		virtual ~InetAddress() = default;
		InetAddress(string_view address, const short& port);

		[[nodiscard]] const sockaddr_in& get_sockaddr() const { return m_sockaddr; }
	private:
		socklen_t m_sockaddr_len;
		sockaddr_in m_sockaddr;
	};

	class Socket
	{
	public:
		virtual ~Socket() { close(); }
		Socket(const int& type = SOCK_STREAM, const int& protocol = 0);

		void bind(const InetAddress& inet_address) const;
		void listen(const int& backlog = 10) const;
		void close() const;
	private:
		int m_socket_fd;
	};

	
}