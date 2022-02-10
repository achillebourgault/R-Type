/*
** EPITECH PROJECT, 2024
** ClientNetworking.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef CLIENTNETWORKING_HPP
#define CLIENTNETWORKING_HPP
#include <iostream>
#include <vector>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <BinaryPacket.h>

class ClientNetworking {
public:
    enum ConnectionAnswer{
        Accepted,
        ServerFull,
        TimedOut
    };
    enum ConnectionStatus {
        Disconnected,
        Connecting,
        Connected
    };
    ClientNetworking(const std::string& hostAddress, int hostPort,
        std::function<void(const BinaryPacket &pkt)> processPacketLambda);
    void sendPacket(std::vector<char> data);
    void sendPacket(std::string data);
    void sendPacket(BinaryPacket pkt);
    char *start_receive();
    void poll();
    void setEndPoint(const std::string &endpointstr);
private:
    boost::asio::io_context _io_context;
    boost::asio::ip::udp::socket _socket;//{_io_context};
    boost::asio::ip::udp::endpoint _endPoint;
    boost::asio::ip::udp::endpoint _myendpoint;
    void write_handler(
        const boost::system::error_code &error, size_t bytes_transferred
    );
    char recv_str[1024] = {};
    void HandlePacket(const BinaryPacket &packet);
    bool connected;
    std::function<void(const BinaryPacket &pkt)> _processPacketLambda;
    void logPacketToCout(BinaryPacket &pkt) const;
};

#endif //CLIENTNETWORKING_HPP
