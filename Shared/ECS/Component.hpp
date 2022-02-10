/*
** EPITECH PROJECT, 2024
** Component.hpp
** File description:
** Created by Leo Fabre
*/
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ECS.hpp"
#include "Manager.hpp"

class AssetLoader;
class Component {
public:
    Entity *entity = nullptr;
    virtual void init() {}
    virtual void update(double t, double dt, Manager::PlayerInputs inputs)
    {
    }
    virtual void draw() {}
    virtual ~Component() {}
};

ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

#endif //COMPONENT_HPP