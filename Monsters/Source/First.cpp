/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Created by Frédéric Lawecki--Walkowiak
*/

#include <First.hpp>
#include <iostream>
#include <csignal>

First::First() : position(0, 0), speed(-110), direction(0), goingUp(false), delta(0)
{
}

void First::updateMonster(struct MonsterInfo &monster, double d)
{
    float x = std::get<0>(monster.monsterPos);
    float y = std::get<1>(monster.monsterPos);
    srand(time(nullptr));

    delta += d;
    if (!monster.shotMissile) {
        monster.shotMissile = true;
        monster.missileDirection = {1,((rand() % 2)) };
        delta = 0;
    }
    else monster.shotMissile = false;
    if (!goingUp) {
        if (y < 450) {
            y += (float(d) * 100);
            monster.monsterPos = {x, y};
        } else goingUp = true;
    } else {
        if (y > 1) {
            y -= (float(d) * 100);
            monster.monsterPos = {x, y};
        } else goingUp = false;
    }
    if (x > -50) {
        x += (float(d) * speed);
        monster.monsterPos = {x, y};
    } else if (x < -50) {
        x += ((rand() % (1400 - 1200) + 1200));
        y = ((rand() % (400 - 100) + 100)) % getpid();
        monster.monsterPos = {x, y};
    }
}

extern "C" IMonsterModule *initMonster() {
    return new First;
}

extern "C" void destroyMonster(IMonsterModule *m) {
    delete m;
}