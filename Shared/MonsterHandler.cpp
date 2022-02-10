/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Created by Frédéric Lawecki--Walkowiak
*/

#include "MonsterHandler.hpp"
#include "Server.hpp"
#include <iostream>
#include <filesystem>

MonsterHandler::~MonsterHandler()
{
}

MonsterHandler::MonsterHandler()
{
    int fileCount = 0;
    std::string path = ".monsters";

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        fileCount++;
        _knownMonsters.push_back(entry.path());
    }
    if (fileCount != 0) {
        for (auto i: _knownMonsters) {
            std::cout << "Opening file: " << i << std::endl;
            LIB_PTR openedLib = OPEN_LIB(i.c_str());
            if (openedLib) {
                std::cout << "Found working library: " << i << std::endl;
                initMonster_t *newMonster = (initMonster_t*) GET_METHOD(openedLib, "initMonster");
                destroyMonster_t *destroyMonster = (destroyMonster_t*) GET_METHOD(openedLib, "destroyMonster");
                std::cout << "Added library " << i << " to working library list." << std::endl;
                _monsterInitList.push_back(newMonster);
                _monsterDestroyList.push_back(destroyMonster);
            }
        }
    } else {
        throw std::invalid_argument("No monster library found in .monsters or the folder does not exists.");
    }
    for(int i = 0; i < _monsterInitList.size(); i++) {
        _updaterList.push_back(_monsterInitList[i]());
    }
}

struct MonsterInfo MonsterHandler::createNewMonster(int monsterCount, int totalTypes)
{
    MonsterInfo monster;
    srand(time(nullptr));
    float posx = ((rand() * (monsterCount - 1)) % (1100 - 1000) + 1000);
    float posy = ((rand() * (monsterCount - 1))  % (400 - 100) + 100);

    if(posy < 0)
        posy += (-posy);
    monster.monsterPos = std::tuple<float, float>(posx, posy);
    monster.monsterID = monsterCount - 1;
    monster.monsterType = totalTypes - 1;
    if (monster.monsterID < 0)
        monster.monsterID = 0;
    if (monster.monsterType < 0)
        monster.monsterType = 0;
    return monster;
}

void MonsterHandler::Update(Server &server, double d)
{
    while(server.state.monsters.size() < 3) {
        srand(time(NULL));
        server.state.monsters.emplace_back(createNewMonster(server.state.monsters.size(), _monsterInitList.size()));
        server.NotifyMonsterSpawned(server.state.monsters[server.state.monsters.size() - 1]);
    }
    for(int i = 0; i < server.state.monsters.size(); i++) {
        _updaterList[server.state.monsters[i].monsterType]->updateMonster(server.state.monsters[i], d);
    }
}
