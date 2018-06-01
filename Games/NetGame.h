#pragma once

#include "IGame.h"
#include "../UDP/UDPConnection.h"

class NetGame : public IGame
{
private:
	UDPConnection _connection;
	bool _player_is_white;

	bool determine_player_color();
public:
	NetGame();
	~NetGame();
	UDPConnection connection() const { return _connection; }
	void init();
	void play();
};

