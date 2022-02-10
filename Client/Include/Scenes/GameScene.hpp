/*
** EPITECH PROJECT, 2024
** GameScene.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "ECS/Manager.hpp"
#include "ECS/Scene.hpp"

class GameScene : public Scene {
public:
    void load() override;

    explicit GameScene(Manager &mgr)
        : _mgr(mgr)
    {
    }

private:
    Manager &_mgr;
};

#endif //GAMESCENE_HPP
