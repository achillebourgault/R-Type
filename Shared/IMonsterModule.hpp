/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Created by Frédéric Lawecki--Walkowiak
*/

#ifndef IMONSTERMODULE_HPP
#define IMONSTERMODULE_HPP

#include <tuple>
#include <vector>
#include <GameState.h>

class IMonsterModule {
public:
    virtual void updateMonster(struct MonsterInfo &monster, double d) = 0;
};

#endif //IMONSTERMODULE_HPP

/*
extern "C" IMonsterModule *initMonster() {
    return new Monster;
}

extern "C" void destroyMonster(IMonsterModule *m) {
    delete m;
}
*/