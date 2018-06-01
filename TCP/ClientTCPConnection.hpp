#ifndef ClientTCPConnection_hpp
#define ClientTCPConnection_hpp

#include <string>
#include <SDL2/SDL_net.h>
#include <vector>
#include <iostream>
#include "../Exceptions/NetworkTerminatedException.hpp"

class ClientTCPConnection {
private:
    std::string _ip;
    IPaddress _ip_address;
    int32_t _port = 5000;
    int32_t _wait_time = 60000;
    static const int _buffer_size = 10;
    TCPsocket _socket;
    bool _active;
    
    void* convert_string_to_void_ptr(const std::string& str) const;
public:
    ClientTCPConnection(const std::string& ip);
    
    void setup_ip();
    void open_connection_to_server();
    void send(const std::string& msg) const;
    bool check_for_activity() const;
    std::string read();
    bool is_active() const { return _active; }
    void add_to_socket_set(SDLNet_SocketSet* socket_set) const;
    void close();
};

#endif
