/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Created by Frédéric Lawecki--Walkowiak
*/

#ifndef FIRST_HPP
#define FIRST_HPP

#include <IMonsterModule.hpp>
#include <GameState.h>

class First : public IMonsterModule{
public:
    First();
    void updateMonster(struct MonsterInfo &monster, double d) override;
private:
    std::tuple<float, float> position;
    int speed;
    int direction;
    bool goingUp;
    bool goingLeft;
    double delta;
};

#endif //FIRST_HPP