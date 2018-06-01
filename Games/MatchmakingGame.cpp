#include "MatchmakingGame.hpp"

MatchmakingGame::~MatchmakingGame()
{
    _net_manager.close_connection();
}

void MatchmakingGame::init()
{
    _net_manager.connect_to_server();
    init_board_fields();
    
    std::cout << "Waiting for opponent..." << std::endl;
    while(true) {
        if (_net_manager.count_client_sockets_with_activity() == 1) {
            
            std::string _msg = _net_manager.read();
            
            char color = _msg[0];
            
            _player_is_white = color == 'W';
            _hash = _msg.substr(1);
            
            std::cout << "Opponent found!" << std::endl;
            std::cout << "Your color is " << (_white_turn ? "white" : "black") << std::endl;
            std::cout << "Your hash is " << _hash << std::endl;
            std::cout << "Game will start in a moment..." << std::endl;
            SDL_Delay(500);
            break;
        } else {
            SDL_Delay(300);
        }
    }
    
    _window_manager.create_window();
}

char MatchmakingGame::player_id()
{
    if (_player_is_white) {
        return '1';
    }
    
    return '2';
}

void MatchmakingGame::play()
{
    SDL_Event event;
    
    while (true)
    {
        _window_manager.render_board(_board_fields);
        
        if (_player_is_white != _white_turn) {
            if (_net_manager.count_client_sockets_with_activity() == 1) {
                std::string data_got = _net_manager.read();
                std::cout << "Full msg - " << data_got << std::endl;
                
                while (data_got.size() > 0) {
                    
                    std::string msg_chunk = data_got.substr(0, 2);
                    data_got = data_got.substr(2);
                    
                    std::cout << "Chunk to proccess - " << msg_chunk << std::endl;
                    std::cout << "Data left - " << data_got << std::endl;
                    
                    // Got notification for loose
                    if (msg_chunk.compare("XX") == 0) {
                        ConsoleWriter::you_lost();
                        return;
                    }
                    
                    int y = msg_chunk[0] - '0';
                    int x = msg_chunk[1] - '0';
                    
                    on_field_click(_board_fields[y][x]);
                    
                    if (_selected_field == nullptr) {
                        set_default_colors();
                    }
                    
                   _window_manager.render_board(_board_fields);
                }
            }
        }
        
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                return;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT && _player_is_white == _white_turn) {
                    BoardField* field_clicked = find_field(event.button.x, event.button.y);
                    if (on_field_click(field_clicked))
                    {
                        std::string data = player_id() + _hash + std::to_string(field_clicked->coordinates().y) + std::to_string(field_clicked->coordinates().x);
                        _net_manager.send(data);
                        std::cout << "Data send - " << data << std::endl;
                    }
                    else {
                        // send notification that you won
                        std::string won = player_id() + _hash + "XX";
                        _net_manager.send(won);
                        ConsoleWriter::you_won();
                        return;
                    }
                    
                    if (_selected_field == nullptr) {
                        set_default_colors();
                    }
                    
                    break;
                }
            default:
                break;
        }
    }
}
