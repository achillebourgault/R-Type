/*
** EPITECH PROJECT, 2024
** Session.hpp
** File description:
** Created by Leo Fabre
*/
#ifndef NETSESSION_HPP
#define NETSESSION_HPP

#include <memory>
#include <iostream>
#include <optional>
#include <boost/asio.hpp>

class ServerNetworking;
class NetSession : public std::enable_shared_from_this<NetSession> {
public:
    struct SessionInfo {
        std::string username;
    };
    /**
    *  Constructor NetSession
    */
    explicit NetSession(
        boost::asio::ip::tcp::socket &&socket, ServerNetworking &server
    );

    /**
    *  Destructor NetSession
    */
    ~NetSession()
    {
        std::cout << "Destroying session " << std::endl;
    }

    /**
    *   Function to start the session
    *   Read with Boost asio on _mySocket server and process items read
    */
    void start();

    /**
    *  Return port of TCP server
    */
    int getRemotePort();

    /**
    *  Return server IP on string
    */
    std::string getRemoteIP();

    /**
    *  Set the username of NetSession
    */
    void setUsername(const std::string &username);

    /**
    *  Return the username of NetSession
    */
    const std::string &getUsername() const;

    /**
    *   Asynchronous send message to the client with Boost
    */
    void SendMsg(std::string message);

    std::string getLocalIP();
    int getLocalPort();
    void SendPacket(int type, std::string data = "");
    SessionInfo info;
private:
    /**
    *  Socket client when the server accept him
    */
    boost::asio::ip::tcp::socket _socket;
    ServerNetworking *_server;
    std::string username;
    boost::asio::streambuf _headerbuf;
    boost::asio::streambuf _databuf;
};

#endif //NETSESSION_HPP