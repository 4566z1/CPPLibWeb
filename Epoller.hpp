#pragma once

#include "LibStruct.hpp"

#include <unordered_map>
using std::unordered_map;

namespace LibWeb
{
	class Channel;

	class Epoller
	{
	public:
		virtual ~Epoller() = default;
		Epoller() = default;

		void poll(vector<Channel*>& active_channel, const int& time_out = -1);
		void update_channel(Channel& channel);
		void remove_channel(Channel& channel);
	private:
		unordered_map<int, Channel*> m_channels;
		Epoll m_epoll;
	};

}
