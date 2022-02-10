/*
** EPITECH PROJECT, 2024
** CollisionHandler.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include "GameState.h"

class Server;

class CollisionHandler {
public:
    //rect<x, y, width, height>
    struct rect {
        int x;
        int y;
        int width;
        int height;
    };
    void Update(Server &srv);
    const std::tuple<int, int> playerSize = {33,17};
    const std::tuple<int, int> monster1Size = {33,36};
    const std::tuple<int, int> projSize = {16,10};
    void CheckPlayerMonsterCollisions(Server &server);
    void CheckPlayerMissilesCollisions(Server &server);
    void CheckMonsterMissilesCollisions(Server &server);
    rect makeRect(PlayerInfo info);
    rect makeRect(MonsterInfo info);
    rect makeProjRect(MissileInfo info);
    bool Collides(PlayerInfo a, MonsterInfo b);
    bool Collides(rect a, rect b);
};

#endif //COLLISIONHANDLER_HPP
