/*
** EPITECH PROJECT, 2024
** Mediator.cpp
** File description:
** Created by Leo Fabre
*/

#include "Mediator.hpp"
#include "MonsterComp.hpp"
#include "MonsterManager.hpp"
#include "Player/PlayerComp.hpp"
#include "ExplosionFxComp.hpp"
#include <ECS/Entity.hpp>
#include <ProjectileComp.hpp>
#include <StringCleaner.h>
#include <StringSplitter.hpp>
#include <Client.hpp>
#include <Player/PlayerShootComp.hpp>

uint8_t Mediator::getLocalPlayerId() const
{
    return _localPlayerID;
}

void Mediator::setLocalPlayerId(uint8_t local_player_id)
{
    _localPlayerID = local_player_id;
}

PlayerInfo Mediator::getPlayerInfo()
{
    PlayerInfo myInfo;
    auto pos =
        PlayerEnts[getLocalPlayerId()]->getComponent<TransformComp>().position;
    auto missiles = _mgr.getEntitiesInGroup(MyProjectiles);
    myInfo.playerID = _localPlayerID;
    myInfo.playerPos = {pos.x, pos.y};
    if (shotMissile) {
        myInfo.shotMissile = true;
        myInfo.missileSize = missileSize;
        shotMissile = false;
    }
    return myInfo;
}

void Mediator::onGameBegin()
{
    //get nb of players from lobby comp
    int nb_players = playernames.size();
}

void Mediator::OnConnectionAccepted(const BinaryPacket &packet)
{
    //packet data is  "[PLAYERID]username,readiness:<others,their_readiness>"
    // split and put em into playernames
    //this player's name should be last one
    auto data = packet.data.data();
    char playerId = data[0];
    int i = 0;

    if (packet.data_length > 1) {
        auto namesAndReadiness =
            StringSplitter::split(packet.data.data() + 1, ':');
        std::cout << "playerId = [" << playerId << "]" << std::endl;
        //start at 1 because the clients username has been set to the first
        for (; i < namesAndReadiness.size() - 1; ++i) {
            auto split = StringSplitter::split(namesAndReadiness[i], ',');
            auto name = split[0];
            bool isReady = (split[1][0] == '1');
            std::cout << "namesAndReadiness[i] = [" << namesAndReadiness[i]
                << "]" << std::endl;
            playernames[i] = name;
            readiness[i] = isReady;
        }
    }
    playernames[i] = getLocalPlayerName();
    setLocalPlayerId(std::atoi(&playerId));
    nb_connected = i;
    std::cout << "nb_connected = [" << nb_connected << "]" << std::endl;
}

void Mediator::SetLocalPlayerName(const sf::String &string)
{
    _localPlayerName = string;
}

std::string Mediator::getLocalPlayerName() const
{
    return _localPlayerName.toAnsiString();
}

void Mediator::OnPlayerJoinedLobby(const BinaryPacket &packet)
{
    nb_connected++;
    playernames[nb_connected] = packet.data.data();
    std::cout << "nb_connected = [" << nb_connected << "]" << std::endl;
}

void Mediator::applyGameState(BinaryPacket pkt)
{
    if (!_mgr._client.isInGame)
        return;

    GameState newState;//todo: fill this with packet decoded data
    newState.decode(pkt.data, nb_connected);
    //std::cout << "after decode" << std::endl;
    for (int i = 0; i < newState.players.size(); i++) {
        if (newState.players[i].playerID == getLocalPlayerId()) continue;
        auto &tc =
            PlayerEnts[newState.players[i].playerID]->getComponent<TransformComp>();
        //  std::cout << "after get entity" << std::endl;
        tc.position.x = std::get<0>(newState.players[i].playerPos);
        tc.position.y = std::get<1>(newState.players[i].playerPos);
        if (newState.players[i].shotMissile) {
            std::cout << "Player " << i << " shot bitch" << std::endl;
            auto &sc =
                PlayerEnts[newState.players[i].playerID]->getComponent<PlayerShootComp>();
            sc.SpawnProjectileProxy(newState.players[i].missileSize);
        }
        //check if player.shotMissile
        // true-> spawm rocket with correct size(type), set sent rocket to false so players dont keep on spawning rockets
        //TODO: set state correctly when clients throw rockets
    }
    //monsters
    monster_manager->applyState(newState);
}

void Mediator::killPlayer(unsigned int id)
{
    Entity *playerToKill = PlayerEnts[id];
    auto& booment = _mgr.addEntity("boom");
    booment.addComponent<ExplosionFXComp>(
        playerToKill->getComponent<TransformComp>().position);
    playerToKill->getComponent<PlayerComp>().kill();
}

void Mediator::onMonsterDied(const BinaryPacket &packet)
{
    auto &monsters = _mgr.getEntitiesInGroup(Monsters);
    unsigned int idToKill = std::atoi(packet.data.data());
    for (auto &monster: monsters) {
        if (monster->getComponent<MonsterComp>().id == idToKill) {
            auto& booment = _mgr.addEntity("boom");
            booment.addComponent<ExplosionFXComp>(
                monster->getComponent<TransformComp>().position);
            monster->destroy();//todo : add killer id to packet and add score to player
            std::cout << "OnMonsterDied : Killed monster " << idToKill << std::endl;
            break;
        }
    }
}

void Mediator::onMonsterSpawned(const BinaryPacket &packet)
{
    std::cout << "ON MONSTER SPAWNED " << packet.data.data() << std::endl;
    auto split = StringSplitter::split(packet.data.data(), ';');
    int monsterId = std::stoi(split[0]);
    int monsterType = std::stoi(split[1]);
    int posX = std::stoi(split[2]);
    int posY = std::stoi(split[3]);
    MonsterInfo newMonster
        {
            static_cast<uint8_t>(monsterId),
            static_cast<uint8_t>(monsterType),
            {posX, posY}
        };
    monster_manager->SpawnMonster(newMonster);
}

int Mediator::get_player_score() const
{
    return _playerScore;
}

void Mediator::set_player_score(int player_score)
{
    _playerScore = player_score;
}
