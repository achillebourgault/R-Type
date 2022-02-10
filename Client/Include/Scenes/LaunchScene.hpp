/*
** EPITECH PROJECT, 2024
** LaunchScene.hpp
** File description:
** Created by Achille Bourgault
*/

#ifndef LaunchScene_HPP
#define LaunchScene_HPP

#include <ECS/Scene.hpp>
#include <iostream>

class LaunchScene : public Scene {
public:
    void load() override;
    explicit LaunchScene(Manager &mgr) : _mgr(mgr) {}
    ~LaunchScene(){std::cout << "~menu" << std::endl;}
private:
    Manager &_mgr;
    void loadPressToPlay();
};

#endif //LaunchScene_HPP