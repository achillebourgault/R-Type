/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** Created by Leo Fabre
*/
#include "Include/ServerNetworking.hpp"
#include "Server.hpp"
#include <functional>
#include <iostream>
#include <thread>
#include <MonsterHandler.hpp>

int main(int argc, char **argv)
{
    size_t nbServers = 1;
    size_t firstPort = 7777;
    std::vector<std::thread> runningThreads;
    if (argc == 1) {
        try {
            //MonsterHandler handler;
            //TODO: ENABLE MONSTER HANDLER
            Server server(firstPort);
            server.run();
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            exit(84);
        }
    } else if (argc == 3) {
        if (std::strcmp(argv[1], "-n") != 0) {
            std::cerr << " Wrong usage consult Readme.MD" << std::endl;
            exit(84);
        }
        try {
            nbServers = std::atoi(argv[2]);
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            exit(84);
        }
       // runningThreads.resize(nbServers);
        for (size_t i = 0; i < nbServers; i++) {
            std::function<void()> func = [firstPort, i]() {
                Server server(firstPort + i);
                server.run();
            };
            runningThreads.emplace_back(func);
            std::cout << "running server number " << i << " on port " << firstPort + i << std::endl;
        }
        for (auto &i: runningThreads) {
            if (i.joinable())
                i.join();
        }
    }
    return 0;
}


