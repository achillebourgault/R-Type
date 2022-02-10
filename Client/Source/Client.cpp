/*
** EPITECH PROJECT, 2024
** Client.cpp
** File description:
** Created by Leo Fabre
*/
#include <Scenes/MenuScene.hpp>
#include <Scenes/GameScene.hpp>
#include <Scenes/LaunchScene.hpp>
#include "Client.hpp"
#include "Scenes/LobbyScene.hpp"
#include "ECS/Entity.hpp"
#include "Scenes/GameOverScene.hpp"

Client::Client()
    : window(
    sf::RenderWindow(
        sf::VideoMode(1200, 600, sf::VideoMode::getDesktopMode().bitsPerPixel),
        "R-Type Client",
        sf::Style::Titlebar | sf::Style::Close)),
      mgr(window, this, [this]() {SceneLoop();}),
      net(
          "127.0.0.1", 7777, [this](const BinaryPacket &pkt) {
              processPacket(pkt);
          }),
      mediator(mgr)
{
    auto desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2<int> newPos = {
        static_cast<int>(desktop.width / 2 - window.getSize().x / 2),
        static_cast<int>(desktop.height / 2 - window.getSize().y / 2)
    };
    window.setPosition(newPos);
}

int Client::run()
{
    return mgr.LoadScene<LaunchScene>();
}

void Client::SceneLoop()
{
    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::Time runTime = sf::Time::Zero;
    window.setFramerateLimit(60);
    std::cout << "=========SCENE LOOP BEGIN" << std::endl;
    while (mgr.isSceneAlive() && window.isOpen() &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        net.poll();

        while (accumulator >= timePerFrame) {
            mgr.processInputs();
            mgr.update(
                runTime.asSeconds(), timePerFrame.asSeconds(), mgr.inputs);
            mgr.refresh();
            if (isInGame)
                sendInfoToServer();
            runTime += timePerFrame;
            accumulator -= timePerFrame;
        }
        accumulator += clock.restart();
        mgr.draw();
    }
    std::cout << "=========SCENE LOOP END" << std::endl;
    if (mgr.sceneToLoad != nullptr) {
        mgr.doLoadScene();
    }
}

void Client::processPacket(const BinaryPacket &packet)
{
    //std::cout << "Received packet: " << packet << std::endl;
    switch (packet.type) {
    case BinaryPacket::PacketType::ConnectionAccepted:
        //todo: get playernames and put em in mediator.playernames
        mediator.OnConnectionAccepted(packet);
        mgr.LoadScene<LobbyScene>();
        break;
    case BinaryPacket::None:
        break;
    case BinaryPacket::ConnectionRequest:
        break;
    case BinaryPacket::PacketType::PlayerJoinedLobby:
        mediator.OnPlayerJoinedLobby(packet);
        break;
    case BinaryPacket::PlayerLeftLobby:
        break;
    case BinaryPacket::PlayerIsReady:
        OnRecvPlayerReady(packet);
        break;
    case BinaryPacket::GameStart:
        OnGameStart();
        break;
    case BinaryPacket::GameStateUpdate:
        mediator.applyGameState(packet);
        break;
    case BinaryPacket::PlayerUpdate:
        break;
    case BinaryPacket::PlayerDied:
        OnPlayerDied(packet);
        break;
    case BinaryPacket::GameOver:
        OnGameOver();
        break;
    case BinaryPacket::MonsterDied:
        mediator.onMonsterDied(packet);
        break;
    case BinaryPacket::MonsterSpawned:
        mediator.onMonsterSpawned(packet);
        break;
    }
}

void Client::OnGameOver()
{
    if (isInGame) {
        isInGame = false;
        mgr.LoadScene<GameOverScene>();
    }
}

void Client::ConnectToServer(std::string endpointstr, std::string Playername)
{
    //Todo : send connection request to ip with playername
    net.setEndPoint(endpointstr);
    std::cout << "Connecting to " << endpointstr << " as " << Playername.c_str()
        << std::endl;
    BinaryPacket pkt
        (
            BinaryPacket::PacketType::ConnectionRequest, Playername.length(),
            Playername.c_str()
        );
    net.sendPacket(pkt);
}

void Client::sendInfoToServer()
{
    PlayerInfo info = mediator.getPlayerInfo();
    size_t len = sizeof(PlayerInfo);
    std::vector<char> infoString(len);
    std::memcpy(infoString.data(), &info, len);
    BinaryPacket
        packet(BinaryPacket::PacketType::PlayerUpdate, len, infoString.data());
    net.sendPacket(packet.encode());
}

void Client::OnClickedReadyToPlay()
{
    std::string id = std::to_string(mediator.getLocalPlayerId());
    std::cout << "READY TO PLAY ! SENDING DATA " << id << std::endl;
    BinaryPacket pkt(BinaryPacket::PacketType::PlayerIsReady, 1, id.c_str());
    mediator.nb_connected++;
    std::cout << "nb_connected = [" << mediator.nb_connected << "]"
        << std::endl;
    net.sendPacket(pkt);
}

void Client::OnGameStart()
{
    std::cout << "loading game scene" << std::endl;
    mgr.LoadScene<GameScene>();
}

void Client::OnRecvPlayerReady(BinaryPacket packet)
{
    int playerID = std::stoi(packet.data.data());
    std::cout << "Received player is ready from "
        << packet.data.data() << " (" << mediator.playernames[playerID]
        << ")" << std::endl;
    mediator.readiness[playerID] = true;
}

void Client::OnPlayerDied(const BinaryPacket &packet)
{
    unsigned int id = std::atoi(packet.data.data());
    mediator.killPlayer(id);
}

void Client::onKilledMonster(unsigned int id)
{
    std::string data = std::to_string(id);
    net.sendPacket(
        BinaryPacket(BinaryPacket::MonsterDied, data.size(), data.data())
    );
}
