/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Created by Adrien Courbebaisse
*/

#include "../Include/ServerNetworking.hpp"
#include "GameState.h"
#include <string.h>

#include <utility>

std::string make_daytime_string();

ServerNetworking::ServerNetworking(
    unsigned short portNb, std::function<void(BinaryPacket)> handle_packet
)
    :
    _mySocket(io_context, asio::ip::udp::endpoint{asio::ip::udp::v4(), portNb}),
    nbClients(0),
    phase(LOBBY),
    handlePacket(std::move(handle_packet))
{
    _client_endPoints.resize(4);
    start_receive();
}

void ServerNetworking::poll()
{
    io_context.poll();
}

void ServerNetworking::start_receive()
{
//    std::cout << "babouin" << std::endl;
    _mySocket.async_receive_from(
        asio::buffer(recv_str, 1024), packetEndPoint,
        [this](std::error_code ec, std::size_t bytes_recvd) {
//            std::cout << "in da lambda " << std::endl;
            if (!ec && bytes_recvd > 0) {
                BinaryPacket recPacket(recv_str);
                handlePacket(recPacket);
                start_receive();
            } else {
                start_receive();
            }
        });
}

void ServerNetworking::sendPacket(
    asio::ip::udp::endpoint enpoint, BinaryPacket packet
)
{
    _mySocket.send_to(
        asio::buffer(packet.encode()),
        enpoint);
}

void ServerNetworking::broadcastPacket(BinaryPacket packet)
{
    for (int i = 0; i < nbClients; i++) {
        sendPacket(_client_endPoints[i].first, packet);
    }
}

void ServerNetworking::broadcastPacketExceptFor(
    const BinaryPacket &packet, int PlayerID
)
{
    for (int i = 0; i < nbClients; ++i) {
        if (i == PlayerID) continue;
        sendPacket(_client_endPoints[i].first, packet);
    }
}

bool ServerNetworking::isNewUser(const BinaryPacket &packet)
{
    return std::find( //check if its a new user
            _client_endPoints.begin(), _client_endPoints.end(),
            std::pair<asio::ip::udp::endpoint, std::string>(packetEndPoint,
                std::string(packet.data.data()))) == _client_endPoints.end();
}
