/*
** EPITECH PROJECT, 2024
** ConnectScene.hpp
** File description:
** Created by Achille Bourgault
*/

#ifndef ConnectScene_HPP
#define ConnectScene_HPP

#include <ECS/Scene.hpp>
#include <GUI/InputTextComp.hpp>

class ConnectScene : public Scene {
public:
    void load() override;
    explicit ConnectScene(Manager &mgr) : _mgr(mgr) {}
    Entity *inputServerEnt;
    private:
    Manager &_mgr;
    void loadServersList();
    void loadRecentsServers();
};

#endif //OptionsScene_HPP
