/*
** EPITECH PROJECT, 2024
** GameOverScene.hpp
** File description:
** Created by Achille Bourgault
*/

#ifndef GameOverScene_HPP
#define GameOverScene_HPP

#include <ECS/Scene.hpp>

class GameOverScene : public Scene {
public:
    void load() override;
    explicit GameOverScene(Manager &mgr) : _mgr(mgr) {}
private:
    Manager &_mgr;
};

#endif
