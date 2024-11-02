#pragma once

#include "Epoller.hpp"

#include <vector>
using std::vector;

namespace LibWeb
{
	class Channel;

	class EventLoop
	{
	public:
		virtual ~EventLoop() = default;
		EventLoop()
		: m_is_quit(false), m_is_init(false)
		{
			
		}

		void loop();
		void update_channel(Channel& channel);
		void remove_channel();
	private:
		bool m_is_quit;
		bool m_is_init;

		vector<Channel*> m_active_channels;
		Epoller m_epoller;
	};
}