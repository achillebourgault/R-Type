/*
** EPITECH PROJECT, 2024
** BinaryPacket.h
** File description:
** Created by Leo Fabre
*/
#ifndef BINARYPACKET_H
#define BINARYPACKET_H

#include <cstdint>
#include <iostream>
#include <vector>

#define HEADER_LEN 24

class BinaryPacket {
public:
    enum PacketType {
        None,
        ConnectionRequest,
        ConnectionAccepted,
        PlayerJoinedLobby,
        PlayerLeftLobby,
        PlayerIsReady,
        GameStart,
        GameStateUpdate,
        PlayerUpdate,
        PlayerDied, //data : playerindex
        MonsterDied, //data : monsterindex
        MonsterSpawned, //data : monsterindex
        GameOver
    };
    BinaryPacket(
        PacketType type, uint32_t data_length, char *newData
    );
    BinaryPacket(
        PacketType type, uint32_t data_length, const char *newData
    );
    BinaryPacket();
    explicit BinaryPacket(PacketType type);
    explicit BinaryPacket(const char *buffer);

    uint64_t timestamp;
    PacketType type;
    uint32_t data_length;

    void decode(const char *buffer);
    std::vector<char> encode(void);
    std::string getPacketTypeString() const;

    friend std::ostream &operator<<(
        std::ostream &os, const BinaryPacket &packet
    );
    std::vector<char> data;
};

#endif //BINARYPACKET_H