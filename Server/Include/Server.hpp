/*
** EPITECH PROJECT, 2024
** Server.hpp
** File description:
** Created by Leo Fabre
*/
#ifndef SERVER_HPP
#define SERVER_HPP

#include <GameState.h>
#include "ServerNetworking.hpp"
#include "BinaryPacket.h"
#include "CollisionHandler.hpp"
#include "MonsterHandler.hpp"

class Server {
public:
    explicit Server(size_t port);
    void run();
    GameState state;

    const unsigned int windowX;
    const unsigned int windowY;
    void OnPlayerDied(unsigned int playerIndex);
    void OnMonsterDied(unsigned int monsterIndex);
    std::vector<MissileInfo> PlayersMissiles;
    std::vector<MissileInfo> MonstersMissiles;
    void NotifyMonsterSpawned(MonsterInfo &info);
private:
    int _listenPort;
    ServerNetworking _net;
    void HandlePacket(const BinaryPacket &packet);
    void OnConnectionRequest(const BinaryPacket &packet);
    void OnPlayerReady(const BinaryPacket &packet);
    void OnPlayerUpdate(const BinaryPacket &packet);
    void StartGame();
    void update(
        std::chrono::time_point<std::chrono::_V2::steady_clock,
            std::chrono::duration<double>> t,
        std::chrono::duration<double> dt
    );
    void gameLogic(
        std::chrono::time_point<std::chrono::_V2::steady_clock,
            std::chrono::duration<double>> timeNow,
        std::chrono::duration<double> elapsedTime
    );
    bool running;
    bool inGame;
    std::array<bool, 4> playersReadiness;
    using Time = std::chrono::time_point<std::chrono::_V2::steady_clock,
        std::chrono::duration<double>>;
    Time gameStartTime;
    std::vector<Time> keepAliveTimers;
    size_t monsterIdCount;
    MonsterHandler monsters;
    CollisionHandler col;
    bool goingUp;
    void UpdateMissiles(double dt);
    void OnReceivedMonsterDied(const BinaryPacket &packet);
};

#endif //SERVER_HPP
