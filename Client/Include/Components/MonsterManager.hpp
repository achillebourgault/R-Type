/*
** EPITECH PROJECT, 2024
** MonsterManager.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef MONSTERMANAGER_HPP
#define MONSTERMANAGER_HPP
#include "ECS/Component.hpp"
#include "GameState.h"

class MonsterManager : public Component {
public:
    void SpawnMonster(MonsterInfo info);
    void applyState(GameState state);
};

#endif //MONSTERMANAGER_HPP
