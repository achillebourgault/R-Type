/*
** EPITECH PROJECT, 2024
** GameStateUpdate.h
** File description:
** Created by Leo Fabre
*/

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <ostream>
#include <cstring>
#include <tuple>
#include <vector>

struct MissileInfo {
    using vec = std::tuple<float, float>;
    unsigned int shotBy;
    vec position;
    vec direction;
    vec size;
    float speed;
};

struct PlayerInfo {
    using vec = std::tuple<float, float>;
    uint8_t playerID = 0; // 0->3

    vec playerPos = {0.f, 0.f};
    bool shotMissile = false;
    size_t missileSize = 0;

    friend std::ostream &operator<<(std::ostream &os, const PlayerInfo &info)
    {
        os << "playerID: " << std::to_string(info.playerID) << " playerPos: "
            << " x: " << std::get<0>(info.playerPos) << " y: "
            << std::get<1>(info.playerPos);
        return os;
    }

    //    uint8_t nb_missiles = 0;
    //    std::vector<std::tuple<const char *, vec, uint8_t>> missiles; //id, vec, type (0->5)
    bool alive = true;
};

struct MonsterInfo {
    using vec = std::tuple<float, float>;
    using veci = std::tuple<int, int>;
    uint8_t monsterID = 0; // 0->n
    uint8_t monsterType = 0; // 0->n

    vec monsterPos = {0.f, 0.f};
    bool shotMissile = false;
    veci missileDirection = {0, 0};

    friend std::ostream &operator<<(std::ostream &os, const MonsterInfo &info)
    {
        os << "monsterID: " << std::to_string(info.monsterID) << " monsterPos: "
            << " x: " << std::get<0>(info.monsterPos) << " y: "
            << std::get<1>(info.monsterPos);
        return os;
    }

    //    uint8_t nb_missiles = 0;
    //    std::vector<std::tuple<const char *, pos, uint8_t>> missiles; //id, pos, type (0->5)
    bool alive = true;
};

struct GameState {
    std::vector<PlayerInfo> players;
    std::vector<MonsterInfo> monsters;

    std::vector<char> encode()
    {
        size_t totalSize =
            (players.size() * sizeof(PlayerInfo)) + sizeof(size_t) +
                (monsters.size() * sizeof(MonsterInfo));
        std::vector<char> encoded(totalSize);
        size_t memsofar = 0;
        for (int i = 0; i < players.size(); i++) {
            std::memcpy(encoded.data() + memsofar, &players[i],
                sizeof(PlayerInfo));
            memsofar += (sizeof(PlayerInfo));
        }
        size_t msize = monsters.size();
        std::memcpy(encoded.data() + memsofar, &msize,
            sizeof(size_t));
        memsofar += sizeof(size_t);
        for (int i = 0; i < monsters.size(); i++) {
            std::memcpy(encoded.data() + memsofar, &monsters[i],
                sizeof(MonsterInfo));
            memsofar += sizeof(MonsterInfo);
        }

        return encoded;
    }

    void decode(const std::vector<char> &encoded, const size_t &nbPLayers)
    {
        size_t monsternb = 0;
        players.resize(nbPLayers);
        size_t memsofar = 0;
        for (int i = 0; i < players.size(); i++) {
            std::memcpy(&players[i], encoded.data() + memsofar,
                sizeof(PlayerInfo));
            memsofar += (sizeof(PlayerInfo));
        }
        std::memcpy(&monsternb, encoded.data() + memsofar,
            sizeof(size_t));
        memsofar += (sizeof(size_t));
        monsters.resize(monsternb);
        for (int i = 0; i < monsternb; i++) {
            std::memcpy(&monsters[i], encoded.data() + memsofar,
                sizeof(MonsterInfo));
            memsofar += (sizeof(MonsterInfo));
        }
    }
};

#endif //GAMESTATE_H
