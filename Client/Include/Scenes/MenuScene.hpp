/*
** EPITECH PROJECT, 2024
** MenuScene.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include <ECS/Scene.hpp>
#include <iostream>

class MenuScene : public Scene {
public:
    void load() override;
    explicit MenuScene(Manager &mgr) : _mgr(mgr) {}
    ~MenuScene(){std::cout << "~menu" << std::endl;}
private:
    Manager &_mgr;
    void loadSidebar();
};

#endif //MENUSCENE_HPP
