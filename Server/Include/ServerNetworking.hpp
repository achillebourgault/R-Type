/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Created by Adrien Courbebaisse
*/

#ifndef SERVERNETWORKING_HPP
#define SERVERNETWORKING_HPP

#include <ctime>
#include <iostream>
#include <string>
#include <asio.hpp>
#include <system_error>
#include <BinaryPacket.h>

class ServerNetworking {
    enum GamePhase {
        LOBBY,
        GAMELOADING,
        INGNAME
    };
public:
    explicit ServerNetworking(
        unsigned short portNb, std::function<void(BinaryPacket)> handle_packet
    );

    void start_receive();
    void sendPacket(asio::ip::udp::endpoint enpoint, BinaryPacket packet);
    void broadcastPacket(BinaryPacket packet);
    void poll();
    std::function<void(BinaryPacket)> handlePacket;

    asio::ip::basic_endpoint<asio::ip::udp> packetEndPoint;
    std::vector<std::pair<asio::ip::udp::endpoint, std::string>>
        _client_endPoints; //endpoint, playerName
    size_t nbClients;
    bool isNewUser(const BinaryPacket &packet);
private:
    size_t _portNb;
    asio::io_context io_context;
    asio::ip::udp::socket _mySocket;
    std::vector<char> _recv_buffer;
    char recv_str[1024] = {};
    GamePhase phase;
    void logPacketToCout(const BinaryPacket &packet) const;
    void broadcastPacketExceptFor(const BinaryPacket &packet, int PlayerID);
};

#endif //SERVERNETWORKING_HPP
