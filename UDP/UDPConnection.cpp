#include "UDPConnection.h"
#include <time.h>

void UDPConnection::close_connection()
{
	SDLNet_FreePacket(_packet);
	SDLNet_Quit();
}

bool UDPConnection::init(const std::string &ip)
{
	if (!init_SDL_Net())
		return false;

	if (!open_port())
		return false;

	if (!set_ip_and_port(ip))
		return false;

	if (!create_packet(512))
		return false;

	return true;
}

bool UDPConnection::init_SDL_Net()
{
	if (SDLNet_Init() == -1)
	{
		return false;
	}

	return true;
}

bool UDPConnection::create_packet(int32_t packet_size)
{
	// Allocate memory for the packet
	_packet = SDLNet_AllocPacket(packet_size);

	if (_packet == nullptr)
	{
		return false;
	}

	// Set the destination host and port
	// We got these from calling SetIPAndPort()
	_packet->address.host = _server_ip.host;
	_packet->address.port = _server_ip.port;

	return true;
}

bool UDPConnection::open_port()
{
	_local_port = 5000;
	_remote_port = 5001;

	_our_socket = SDLNet_UDP_Open(_local_port);
	if (_our_socket == nullptr)
	{
		_our_socket = SDLNet_UDP_Open(++_local_port);
		_remote_port--;

		if (_our_socket == nullptr)
		{
			return false;
		}
	}

	return true;
}

bool UDPConnection::set_ip_and_port(const std::string &ip)
{
	if (SDLNet_ResolveHost(&_server_ip, ip.c_str(), _remote_port) == -1)
	{
		return false;
	}

	return true;
}

bool UDPConnection::send(const char* msg)
{
	memcpy(_packet->data, msg, strlen(msg));
	_packet->len = (int)strlen(msg);

	if (SDLNet_UDP_Send(_our_socket, -1, _packet) == 0)
	{
		return false;
	}

	return true;
}

char* UDPConnection::check_for_data()
{
	if (SDLNet_UDP_Recv(_our_socket, _packet))
	{
		return (char*)_packet->data;
	}

	return nullptr;
}