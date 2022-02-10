/*
** EPITECH PROJECT, 2024
** Client.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "SFML/Graphics.hpp"
#include "ClientNetworking.hpp"
#include "Mediator.hpp"
#include <ECS/Manager.hpp>

class Client {
public:
    explicit Client();
    int run();
    void ConnectToServer(std::string endpointstr, std::string Playername);
    void OnClickedReadyToPlay();
    void processPacket(const BinaryPacket& packet);
    Manager mgr;
    Mediator mediator;
    ClientNetworking net;
    bool isInGame = false;
    void onKilledMonster(unsigned int i);
private:
    std::string _playername;
    sf::RenderWindow window;
    void SceneLoop();
    bool connected = true;
    void sendInfoToServer();
    void OnGameStart();
    void OnRecvPlayerReady(BinaryPacket packet);
    void OnPlayerDied(const BinaryPacket &packet);
    void OnGameOver();
};

#endif //CLIENT_HPP
