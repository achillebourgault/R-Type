/*
** EPITECH PROJECT, 2024
** Server.cpp
** File description:
** Created by Leo Fabre
*/

#include "Server.hpp"

Server::Server(size_t port)
    : _listenPort(port),
      _net(
          _listenPort,
          [this](BinaryPacket pkt) {HandlePacket(pkt);}),
      windowX(1200),
      windowY(600),
      running(false),
      inGame(false),
      playersReadiness({false, false, false, false}),
      gameStartTime(std::chrono::duration<double>(0)),
      monsterIdCount(0),
      goingUp(false),
      keepAliveTimers(0)
{
}

void Server::run()
{
    running = true;

    double t = 0.0;
    double dtms = 1.0 / 60.0;
    struct timeval lastUpdate{};
    //gettimeofday(&lastUpdate, nullptr);
    time_t
        lastUpdatems = (lastUpdate.tv_sec * 1000) + (lastUpdate.tv_usec / 1000);

    std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::duration<double>>
        lastupdate2 = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::duration<double>>
        timenow2 = std::chrono::steady_clock::now();
    time_t timediff = 0;
    std::chrono::duration<double> elapsed_seconds = timenow2 - lastupdate2;

    while (running) {
        //        std::cout << "LOOP" << std::endl;
        _net.poll();

        //get time diff since last time in loop

        timenow2 = std::chrono::steady_clock::now();
        elapsed_seconds = timenow2 - lastupdate2;

        if (std::chrono::duration<double>(elapsed_seconds).count() > dtms) {
            update(timenow2,
                elapsed_seconds);//TODO: refactor with std::chrono stuff
            lastupdate2 = std::chrono::steady_clock::now();
        }
        /*else {
            usleep(1);
        }*/
    }
}

void Server::HandlePacket(const BinaryPacket &packet)
{
    switch (packet.type) {
    case BinaryPacket::PacketType::ConnectionRequest:
        OnConnectionRequest(packet);
        break;
    case BinaryPacket::PacketType::None:
        break;
    case BinaryPacket::PacketType::ConnectionAccepted:
        break;
    case BinaryPacket::PlayerJoinedLobby:
        break;
    case BinaryPacket::PlayerLeftLobby:
        break;
    case BinaryPacket::PlayerIsReady:
        OnPlayerReady(packet);
        break;
    case BinaryPacket::GameStart:
        break;
    case BinaryPacket::GameStateUpdate:
        break;
    case BinaryPacket::PlayerUpdate:
        OnPlayerUpdate(packet);
        break;
    case BinaryPacket::PlayerDied:
        break;
    case BinaryPacket::MonsterDied:
        OnReceivedMonsterDied(packet);
        break;
    case BinaryPacket::MonsterSpawned:
        break;
    case BinaryPacket::GameOver:
        break;
    }
}

void Server::OnConnectionRequest(const BinaryPacket &packet)
{
    std::cout << "OnConnectionRequest()" << std::endl;
    if (_net.isNewUser(packet) && _net.nbClients <= 4) {
        std::cout << "adding new endpoint" << std::endl;
        _net._client_endPoints[_net.nbClients].first = _net.packetEndPoint;
        _net._client_endPoints[_net.nbClients].second = packet.data.data();
        //data protocol
        //send all usernames to connecting user
        std::string data =
            std::to_string(_net.nbClients); //first byte (new player's ID)
        if (_net.nbClients != 0) {
            for (int i = 0; i < _net.nbClients; i++) {
                data.append(_net._client_endPoints[i].second); //playername
                data.append(",");
                data.append(
                    std::to_string(playersReadiness[i])); //readiness (0 or 1)
                data.append(":");

                //while cycling, notify others of this new connection
                _net.sendPacket(
                    _net._client_endPoints[i].first,
                    BinaryPacket(
                        BinaryPacket::PlayerJoinedLobby,
                        packet.data_length, (char *) packet.data.data()));
            }
        }
        //send connection accepted with [id]<username,readiness>[:]
        _net.sendPacket(
            _net._client_endPoints[_net.nbClients].first, BinaryPacket(
                BinaryPacket::ConnectionAccepted, data.size(),
                (char *) data.c_str()));
        _net.nbClients++;
        std::cout << "Sent packet" << std::endl;
    }
}

void Server::OnPlayerReady(const BinaryPacket &packet)
{
    int playerID = std::stoi(packet.data.data());
    std::cout << "Player " << playerID << " is ready" << std::endl;
    playersReadiness[playerID] = true;
    _net.broadcastPacket(packet);
    bool shouldStartGame = true;
    for (int i = 0; i < _net.nbClients; ++i)
        if (!playersReadiness[i]) shouldStartGame = false;
    if (shouldStartGame) {
        inGame = true;
        usleep(50); //la touche du chef
        StartGame();
    }
}

void Server::OnPlayerUpdate(const BinaryPacket &packet)
{
    if (!inGame)
        return;
    PlayerInfo recInfo;
    std::memcpy(&recInfo, packet.data.data(), packet.data_length);
    //    std::cout << recInfo << std::endl;
    state.players[recInfo.playerID] = recInfo;
    if (recInfo.shotMissile) {
        PlayersMissiles.emplace_back(
            MissileInfo{
                recInfo.playerID,
                recInfo.playerPos,
                {1, 0},
                {16, 10},
                1500
            });
    }
    keepAliveTimers[recInfo.playerID] = std::chrono::steady_clock::now();
}

void Server::StartGame()
{
    std::cout << "Starting Game" << std::endl;
    //todo: run gameloop here
    gameStartTime = std::chrono::steady_clock::now();
    keepAliveTimers.resize(_net.nbClients);
    std::fill(keepAliveTimers.begin(), keepAliveTimers.end(), gameStartTime);
    state.players.resize(_net.nbClients);
    for (int i = 0; i < _net.nbClients; i++) {
        state.players[i].playerID = i;
        state.players[i].playerPos = {0, i * 50};
    }
    /*state.monsters.resize(1);
    state.monsters[0].monsterID = 0;
    state.monsters[0].monsterPos = {100, 100};*/

    _net.broadcastPacket(BinaryPacket(BinaryPacket::GameStart));
}

void Server::update(
    std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::duration<double>> timeNow,
    std::chrono::duration<double> elapsedTime
)
{
    //update server managed enTITYS
    //broadcast gamestate to all clients
    if (inGame) {
        gameLogic(timeNow, elapsedTime);
        std::vector<char> encodedState = state.encode();
        _net.broadcastPacket(
            BinaryPacket(
                BinaryPacket::GameStateUpdate, encodedState.size(),
                encodedState.data()));
    }
}

void Server::gameLogic(
    std::chrono::time_point<std::chrono::_V2::steady_clock,
        std::chrono::duration<double>> timeNow,
    std::chrono::duration<double> elapsedTime
)
{
    static bool hasSpawnedFirstMonster = false;
    for (int i = 0; i < keepAliveTimers.size(); ++i) {
        if (std::chrono::duration<double>(
            timeNow - keepAliveTimers[i]).count() >
            double(3) && state.players[i].alive) {
            std::cout << "PLAYER " << i << " TIMED OUT" << std::endl;
            OnPlayerDied(i);
            bool allDead = true;
            for (int j = 0; j < state.players.size(); ++j)
                if (state.players[j].alive) allDead = false;
            if (allDead) {
                std::cout << "All players are dead or timed out. Exiting."
                    << std::endl;
                exit(0);
            }
            //todo: kill player and notify others
        }
    }
    if (std::chrono::duration<double>(timeNow - gameStartTime).count() <
        double(3)) { //wait for 3 seconds after game start
        return;
    }
    monsters.Update(*this, elapsedTime.count());
    UpdateMissiles(elapsedTime.count());
    col.Update(*this);
}

void Server::OnPlayerDied(unsigned int playerIndex)
{
    std::cout << "PLAYER IS DEAD " << playerIndex << std::endl;
    //set player not alive
    if (!state.players[playerIndex].alive) {return;}
    state.players[playerIndex].alive = false;
    _net.broadcastPacket(
        BinaryPacket(BinaryPacket::PlayerDied, 1,
            std::to_string(playerIndex).data()));
    //todo: if all players are dead send gameover packet
    bool gameOver = true;
    for (const auto &player: state.players)
        if (player.alive) gameOver = false;
    if (gameOver)
        _net.broadcastPacket(BinaryPacket(BinaryPacket::GameOver));
}

void Server::OnMonsterDied(unsigned int monsterIndex)
{
    if (!state.monsters[monsterIndex].alive) return;
    std::cout << "MONSTER IS DEAD " << monsterIndex << std::endl;
    state.monsters[monsterIndex].alive = false;
    state.monsters.erase(state.monsters.begin() + monsterIndex);
    std::string pktdata = std::to_string(monsterIndex);
    _net.broadcastPacket(
        BinaryPacket(BinaryPacket::MonsterDied, pktdata.length(),
            pktdata.data())
    );
}

void Server::UpdateMissiles(double dt)
{
    return;
    for (auto &missile: PlayersMissiles) {
        std::cout << "Updating Missile of " << missile.shotBy << " pos: "
            << std::get<0>(missile.position) << ":"
            << std::get<1>(missile.position) << std::endl;

        std::get<0>(missile.position) +=
            std::get<0>(missile.direction) * missile.speed * dt;
        std::get<1>(missile.position) +=
            std::get<1>(missile.direction) * missile.speed * dt;
        std::remove_if(PlayersMissiles.begin(), PlayersMissiles.end(),
            [this](MissileInfo &missile_info) {
                bool res = std::get<0>(missile_info.position) > windowX;
                if (res) std::cout << "DELETING MISSILE !!" << std::endl;
                return res;
            });
    }
    for (auto &missile: MonstersMissiles) {
        std::get<0>(missile.position) +=
            std::get<0>(missile.direction) * missile.speed * dt;
        std::get<1>(missile.position) +=
            std::get<1>(missile.direction) * missile.speed * dt;
    }
}

void Server::NotifyMonsterSpawned(MonsterInfo &info)
{
    std::string pktdata(
        std::to_string(info.monsterID) + ";" +
            std::to_string(info.monsterType) + ";" +
            std::to_string(std::get<0>(info.monsterPos)) + ";" +
            std::to_string(std::get<0>(info.monsterPos))
    );
    auto pkt = BinaryPacket(BinaryPacket::MonsterSpawned, pktdata.size(),
        pktdata.data());
    _net.broadcastPacket(pkt);
}

void Server::OnReceivedMonsterDied(const BinaryPacket &packet)
{
    int deadId = std::stoi(packet.data.data());
    OnMonsterDied(deadId);
}
