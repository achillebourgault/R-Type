/*
** EPITECH PROJECT, 2024
** BinaryPacket.cpp
** File description:
** Created by Leo Fabre
*/

#include "BinaryPacket.h"
#include <bitset>
#include <cstring>
#include <ctime>

BinaryPacket::BinaryPacket()
    :
    timestamp(0u),
    type(None),
    data_length(0u)
{
}
BinaryPacket::BinaryPacket(PacketType type): timestamp(0), type(type), data_length(0), data(0)
{
}


BinaryPacket::BinaryPacket(PacketType type, uint32_t data_length, char *newData)
    : BinaryPacket(type, data_length, (const char *) newData)
{
}

BinaryPacket::BinaryPacket(
    BinaryPacket::PacketType type, uint32_t data_length, const char *newData
)
    : timestamp(std::time(nullptr)),
      type(type),
      data_length(data_length),
      data(data_length + 1)
{
    for (int i = 0; i < this->data_length; i++) {
        std::memcpy(&this->data[i], newData + (i * sizeof(char)),
            sizeof(char));
    }
    data[data_length] = 0;
}

BinaryPacket::BinaryPacket(const char *buffer)
{
    this->decode(buffer);
}

// Encode outgoing data
std::vector<char> BinaryPacket::encode()
{
    size_t fullsize =
        sizeof(uint64_t) + sizeof(BinaryPacket::PacketType) + sizeof(uint32_t) +
            (this->data_length * sizeof(char));
    std::vector<char> data(fullsize);
    //fill packet
    size_t nbBytes = 0;
    std::memcpy(data.data(), &this->timestamp, sizeof(uint64_t));
    nbBytes += sizeof(uint64_t);
    std::memcpy(data.data() + nbBytes, &this->type,
        sizeof(BinaryPacket::PacketType));
    nbBytes += sizeof(BinaryPacket::PacketType);
    std::memcpy(data.data() + nbBytes, &this->data_length, sizeof(uint32_t));
    nbBytes += sizeof(uint32_t);
    for (int i = 0; i < this->data_length; i++) {
        std::memcpy(data.data() + nbBytes + (i * sizeof(char)), &this->data[i],
            sizeof(char));
    }
    return data;
}

// Decode incoming data
void BinaryPacket::decode(const char *buffer)
{
    size_t nbBytes = 0;
    std::memcpy(&this->timestamp, buffer + nbBytes, sizeof(uint64_t));
    nbBytes += sizeof(uint64_t);
    std::memcpy(&this->type, buffer + nbBytes,
        sizeof(BinaryPacket::PacketType));
    nbBytes += sizeof(BinaryPacket::PacketType);
    std::memcpy(&this->data_length, buffer + nbBytes, sizeof(uint32_t));
    nbBytes += sizeof(uint32_t);
    this->data.resize(this->data_length + 1);
    for (int i = 0; i < this->data_length; i++) {
        std::memcpy(&this->data[i], buffer + nbBytes + (i * sizeof(char)),
            sizeof(char));
    }
    data[data_length] = 0;
}

std::ostream &operator<<(std::ostream &os, const BinaryPacket &packet)
{
    os << " timestamp: [" << packet.timestamp << "]" << std::endl
        << " type: [" << (int) packet.type << "] (aka. "
        << packet.getPacketTypeString() << ")" << std::endl
        << " data_length: [" << packet.data_length << "]";
    if (packet.data_length > 0) {
        os << std::endl << " data: [" << packet.data.data() << "]";
    }
    return os;
}

std::string BinaryPacket::getPacketTypeString() const
{
    switch (type) {
    case None:
        return "None";
    case ConnectionRequest:
        return "ConnectionRequest";
    case ConnectionAccepted:
        return "ConnectionAccepted";
    case PlayerJoinedLobby:
        return "PlayerJoinedLobby";
    case PlayerLeftLobby:
        return "PlayerLeftLobby";
    case PlayerIsReady:
        return "PlayerIsReady";
    case GameStart:
        return "GameStart";
    case GameStateUpdate:
        return "GameStateUpdate";
    default:
        return "bad packet type ! (or not implemented in gpts()...)";
    }
}
