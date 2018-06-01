#pragma once
#include <sstream>
#include <SDL2/SDL_net.h>
#include <iostream>
#include <string>

class UDPConnection
{
private:
	UDPsocket _our_socket;
	int32_t _local_port;
	int32_t _remote_port;
	IPaddress _server_ip;
	UDPpacket* _packet;

	bool create_packet(int32_t packetSize);
	bool open_port();
	bool set_ip_and_port(const std::string &ip);
	bool init_SDL_Net();

public:
	void close_connection();
	bool init(const std::string &ip);
	bool send(const char* msg);
	char* check_for_data();
};
