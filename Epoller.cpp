#include "Epoller.hpp"

#include "Channel.hpp"

void LibWeb::Epoller::poll(vector<Channel*>& active_channel, const int& time_out)
{
	m_epoll.wait(time_out);
	
	for(const epoll_event& event : m_epoll.get_events())
	{
		Channel* channel = m_channels[event.data.fd];
		channel->set_current_event(event.events);
		active_channel.emplace_back(channel);
	}
}

void LibWeb::Epoller::update_channel(Channel& channel)
{
	m_channels[channel.get_fd()] = &channel;
	m_epoll.set_fd(channel.get_fd(), channel.get_current_event());
}

void LibWeb::Epoller::remove_channel(Channel& channel)
{
	m_channels.erase(channel.get_fd());
}

