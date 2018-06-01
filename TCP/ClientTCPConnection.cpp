#include "ClientTCPConnection.hpp"

ClientTCPConnection::ClientTCPConnection(const std::string& ip) :
    _ip(ip)
{
    
}

void ClientTCPConnection::setup_ip() {
    int success = SDLNet_ResolveHost(&_ip_address, _ip.c_str(), _port);
    
    if (success == -1)
    {
        std::cout << "Failed to resolve host" << std::endl;
        throw "Failed to resolve host";
    }
}

void ClientTCPConnection::open_connection_to_server()
{
    setup_ip();
    
    _socket = SDLNet_TCP_Open(&_ip_address);
    
    if (_socket == nullptr) {
        std::cout << "Port " << _port << " is occupied." << std::endl;
        _port++;
        open_connection_to_server();
    } else {
        std::cout << "Connected on port " << _port << std::endl;
        _active = true;
    }
}

void* ClientTCPConnection::convert_string_to_void_ptr(const std::string &str) const
{
    const char* char_ptr = str.c_str();
    
    return const_cast<char*>(char_ptr);
}

void ClientTCPConnection::send(const std::string &msg) const
{
    void* msg_ptr = convert_string_to_void_ptr(msg);
    int msg_size = static_cast<int>(msg.length());
    
    int bytes_sent = SDLNet_TCP_Send(_socket, msg_ptr, msg_size);
    
    if (bytes_sent != msg_size) {
        throw SDLNet_GetError();
    }
}

std::string ClientTCPConnection::read()
{
    char buffer[_buffer_size];
    memset(buffer, 0, _buffer_size);

    int byte_count = SDLNet_TCP_Recv(_socket, buffer, _buffer_size);
    std::string msg_got("");
    if (byte_count > 0) {
        buffer[byte_count] = '\0';
        msg_got = buffer;
    } else if (byte_count == 0) {
        _active = false;
        throw NetworkTerminatedException();
    } else {
        _active = false;
        std::cout << "Read failed. " << SDLNet_GetError() << std::endl;
    }
    
    return msg_got;
}

void ClientTCPConnection::add_to_socket_set(SDLNet_SocketSet* socket_set) const
{
    SDLNet_TCP_AddSocket(*socket_set, _socket);
}

void ClientTCPConnection::close()
{
    _active = false;
    std::cout << "Closing connection.." << std::endl;
    SDLNet_TCP_Close(_socket);
}

bool ClientTCPConnection::check_for_activity() const
{
    int activities = SDLNet_SocketReady(_socket);
    
    return activities != 0;
}
