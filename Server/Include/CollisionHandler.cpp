/*
** EPITECH PROJECT, 2024
** CollisionHandler.cpp
** File description:
** Created by Leo Fabre
*/

#include "CollisionHandler.hpp"
#include "Server.hpp"

void CollisionHandler::Update(Server &srv)
{
    CheckPlayerMonsterCollisions(srv);
    CheckPlayerMissilesCollisions(srv);
    CheckMonsterMissilesCollisions(srv);
}

void CollisionHandler::CheckPlayerMonsterCollisions(Server &server)
{
    for (const auto &player: server.state.players) {
        if (!player.alive) continue;
        for (const auto &monster: server.state.monsters) {
            if (!monster.alive) {continue;}
            if (Collides(player, monster)) {
                std::cout << "PLAYER/MONSTER HIT !!!" << std::endl;
                server.OnPlayerDied(player.playerID);
                server.OnMonsterDied(monster.monsterID);
            }
        }
    }
}

bool CollisionHandler::Collides(
    CollisionHandler::rect rect1, CollisionHandler::rect rect2
)
{
    return rect1.x < rect2.x + rect2.width &&
        rect1.x + rect1.width > rect2.x &&
        rect1.y < rect2.y + rect2.height &&
        rect1.height + rect1.y > rect2.y;
}

bool CollisionHandler::Collides(PlayerInfo a, MonsterInfo b)
{
    return Collides(makeRect(a), makeRect(b));
}

void CollisionHandler::CheckPlayerMissilesCollisions(Server &server)
{
    for (const auto &missile: server.PlayersMissiles)
        for (const auto &monster: server.state.monsters) {
            if (!monster.alive) {continue;}
            if (Collides(makeProjRect(missile), makeRect(monster))) {
                std::cout << "MONSTER KILLED BY " << missile.shotBy << std::endl;
                server.OnMonsterDied(monster.monsterID);
            }
        }
}

void CollisionHandler::CheckMonsterMissilesCollisions(Server &server)
{
    for (const auto &missile: server.MonstersMissiles)
        for (const auto &player: server.state.players)
            if (Collides(makeProjRect(missile), makeRect(player)))
                server.OnPlayerDied(player.playerID);
}

CollisionHandler::rect CollisionHandler::makeRect(PlayerInfo info)
{
    return CollisionHandler::rect
        {
            (int) std::get<0>(info.playerPos),
            (int) std::get<1>(info.playerPos),
            std::get<0>(playerSize),
            std::get<1>(playerSize)
        };
}

CollisionHandler::rect CollisionHandler::makeRect(MonsterInfo info)
{
    return CollisionHandler::rect{
        (int) std::get<0>(info.monsterPos),
        (int) std::get<1>(info.monsterPos),
        std::get<0>(monster1Size), //make a method to get size from info.type
        std::get<1>(monster1Size)
    };
}

CollisionHandler::rect CollisionHandler::makeProjRect(MissileInfo info)
{
    return CollisionHandler::rect{
        (int) std::get<0>(info.position),
        (int) std::get<1>(info.position),
        (int) std::get<0>(info.size), //make a method to get size from info.type
        (int) std::get<1>(info.size)
    };
}