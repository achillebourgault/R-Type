/*
** EPITECH PROJECT, 2024
** ClientNetworking.cpp
** File description:
** Created by Leo Fabre
*/

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "ClientNetworking.hpp"
#include "BinaryPacket.h"

ClientNetworking::ClientNetworking(
    const std::string &hostAddress, int hostPort,
    std::function<void(const BinaryPacket &pkt)> processPacketLambda
)
    : _socket{_io_context},
      connected(false),
      _processPacketLambda(processPacketLambda)
{
    _socket.open(boost::asio::ip::udp::v4());
    start_receive();
}

void ClientNetworking::sendPacket(std::vector<char> data)
{
    _socket.send_to(boost::asio::buffer(data), _endPoint);
}

void ClientNetworking::sendPacket(std::string data)
{
    _socket.send_to(boost::asio::buffer(data), _endPoint);
}

char *ClientNetworking::start_receive()
{
   // std::cout << "babouin" << std::endl;
    _socket.async_receive_from(
        boost::asio::buffer(recv_str),
        _myendpoint, [this](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                BinaryPacket recPacket(recv_str);
                HandlePacket(recPacket);
                start_receive();
            } else {
                start_receive();
            }
        });
    //std::cout << "after lambda" << std::endl;

    return recv_str;
}

void ClientNetworking::write_handler(
    const boost::system::error_code &error, // Result of operation.
    std::size_t bytes_transferred           // Number of bytes sent.
)
{
    std::cout << "wrote " << bytes_transferred << " bytes to socket"
        << std::endl;
}

void ClientNetworking::sendPacket(BinaryPacket pkt)
{
    std::cout << "SendPacket : sending packet" << std::endl << pkt << std::endl;

    _socket.async_send_to(boost::asio::buffer(pkt.encode()), _endPoint,
        boost::bind(&ClientNetworking::write_handler, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void ClientNetworking::HandlePacket(const BinaryPacket &packet)
{
    _processPacketLambda(packet);
}

void ClientNetworking::poll()
{
    _io_context.poll();
}

void ClientNetworking::setEndPoint(const std::string &endpointstr)
{
    std::string::size_type pos = endpointstr.find(':');
    std::string ip;
    std::string portStr;
    size_t portNb;
    if (pos != std::string::npos)
    {
        ip = endpointstr.substr(0, pos);
        portStr = endpointstr.substr(pos + 1);
    }
    else
    {
        std::cerr << "invalid connect string using default" << std::endl;
        return;
    }
    portNb = std::atoi(portStr.c_str());
    _endPoint = {
        boost::asio::ip::make_address(ip),
        static_cast<boost::asio::ip::port_type>(portNb)
    };
}



