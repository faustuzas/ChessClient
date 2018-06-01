#include "../TCP/NetworkManager.hpp"

NetworkManager::NetworkManager() :
    _server_ip(ConsoleWriter::get_ip()),
    _connection(new ClientTCPConnection(_server_ip)),
    _client_socket_set(SDLNet_AllocSocketSet(10))
{
    
}

void NetworkManager::connect_to_server()
{
    _connection->open_connection_to_server();
    _connection->add_to_socket_set(&_client_socket_set);
}

int NetworkManager::count_client_sockets_with_activity() const
{
    return SDLNet_CheckSockets(_client_socket_set, 5);
}
