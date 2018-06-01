#ifndef NetworkManager_hpp
#define NetworkManager_hpp

#include <string>
#include <SDL2/SDL_net.h>

#include "ClientTCPConnection.hpp"
#include "../ConsoleWriter.h"

class NetworkManager {
private:
    unsigned short _port;
    std::string _server_ip;
    std::unique_ptr<ClientTCPConnection> _connection;
    SDLNet_SocketSet _client_socket_set;
    
public:
    NetworkManager();
    void connect_to_server();
    void send(const std::string& msg) const { _connection->send(msg); }
    std::string read() const { return _connection->read(); }
    bool msg_got() const  { return _connection->check_for_activity(); }
    void close_connection() const { _connection->close(); }
    int count_client_sockets_with_activity() const;
};

#endif
