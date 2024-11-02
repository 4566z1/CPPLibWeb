#include "EventLoop.hpp"

#include "Channel.hpp"
#include "Logger.hpp"

void LibWeb::EventLoop::update_channel(Channel& channel)
{
	m_epoller.update_channel(channel);
}

void LibWeb::EventLoop::loop()
{
	if (!m_is_init) m_is_init = true;
	else Logger::throw_runtime_error("EventLoop has been initialized!");

	while(!m_is_quit)
	{
		m_active_channels.clear();
		m_epoller.poll(m_active_channels);
		for (const Channel* channel : m_active_channels)
		{
			channel->handle_event();
		}
	}
}
