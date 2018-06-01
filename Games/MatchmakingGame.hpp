#ifndef MatchmakingGame_hpp
#define MatchmakingGame_hpp

#include "IGame.h"
#include "../TCP/NetworkManager.hpp"

class MatchmakingGame : public IGame {
private:
    NetworkManager _net_manager;
    std::string _hash;
    bool _player_is_white;
    
    char player_id();
public:
    MatchmakingGame() { _white_turn = true; }
    ~MatchmakingGame();
    
    void play();
    void init();
};

#endif
