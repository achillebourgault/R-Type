/*
** EPITECH PROJECT, 2024
** LobbyScene.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef LOBBYSCENE_HPP
#define LOBBYSCENE_HPP

#include <ECS/Scene.hpp>

class LobbyScene : public Scene {
public:
    LobbyScene(Manager &mgr) : _mgr(mgr){}
    void load() override;

private:
    Manager &_mgr;
};

#endif //LOBBYSCENE_HPP
