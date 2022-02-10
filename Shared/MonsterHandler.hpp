/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Created by Frédéric Lawecki--Walkowiak
*/

#ifndef MONSTERHANDLER_HPP
#define MONSTERHANDLER_HPP

#include "IMonsterModule.hpp"
#include <string>
#include <tuple>
#include <vector>
#include <GameState.h>

#if defined _WIN32
#include <Windows.h>
    #define OPEN_LIB(X) LoadLibrary((LPCSTR)X)
    #define LIB_PTR HMODULE
    #define GET_METHOD GetProcAddress
#else
    #include <dlfcn.h>
#include <functional>

    #define OPEN_LIB(libPath) dlopen(libPath, RTLD_NOW)
    #define LIB_PTR void*
    #define GET_METHOD dlsym
#endif

typedef IMonsterModule *initMonster_t();
typedef void destroyMonster_t(IMonsterModule *);

class Server;
class MonsterHandler {
public:
    MonsterHandler();
    ~MonsterHandler();
    void Update(Server &server, double d);
    struct MonsterInfo createNewMonster(
        int monsterCount, int totalTypes
    );
    //void addMonster(std::string libpath); TODO: enable load of new libraries
private:
    std::vector<std::string> _knownMonsters;
    std::vector<initMonster_t (*)> _monsterInitList;
    std::vector<destroyMonster_t (*)> _monsterDestroyList;
    std::vector<IMonsterModule (*)> _updaterList;
};

#endif //MONSTERHANDLER_HPP