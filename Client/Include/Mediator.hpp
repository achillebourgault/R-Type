/*
** EPITECH PROJECT, 2024
** Mediator.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

#include <ECS/Manager.hpp>
#include <BinaryPacket.h>
#include "GameState.h"
#include "MonsterManager.hpp"

class Mediator {
public:
    Mediator(Manager &mgr)
        : _mgr(mgr),
          playernames(4, "<waiting for player>"),
          nb_connected(0),
          readiness({false, false, false, false}),
          shotMissile(false),
          missileSize(0),
          monster_manager(nullptr)
    {
    }
    void applyGameState(BinaryPacket pkt);
    PlayerInfo getPlayerInfo();
    void onGameBegin();
    std::vector<std::string> playernames;
    std::array<bool, 4> readiness;
private:
    Manager _mgr;
    uint8_t _localPlayerID;
    std::vector<PlayerInfo> players;
    sf::String _localPlayerName;
    int _playerScore = 0;
    public:
    int get_player_score() const;
    void set_player_score(int player_score);
    public:
    uint8_t getLocalPlayerId() const;
    void setLocalPlayerId(uint8_t local_player_id);
    void OnConnectionAccepted(const BinaryPacket &packet);
    void OnPlayerJoinedLobby(const BinaryPacket &packet);
    void SetLocalPlayerName(const sf::String &string);
    std::string getLocalPlayerName() const;
    std::vector<Entity *> PlayerEnts;
    size_t nb_connected;
    bool shotMissile;
    size_t missileSize;
    MonsterManager *monster_manager;
    void killPlayer(unsigned int i);
    void onMonsterDied(const BinaryPacket &packet);
    void onMonsterSpawned(const BinaryPacket &packet);
};

#endif //MEDIATOR_HPP
