/*
** EPITECH PROJECT, 2024
** Entity.cpp
** File description:
** Created by Leo Fabre
*/
#include "ECS/Entity.hpp"
#include "ECS/Manager.hpp"
#include "Components/AssetLoader.hpp"
#include <utility>

void Entity::update(double t, double dt, Manager::PlayerInputs inputs)
{
    for (auto &c: components) {
        c->update(t, dt, inputs);
    }
}

void Entity::destroy()
{
    _active = false;
}

void Entity::draw()
{
    for (auto &c: components) c->draw();
}

Entity::Entity(std::string name, Manager &mgr)
    : _name(std::move(name)),
      _mgr(mgr)
{
}

const std::string &Entity::getName() const
{
    return _name;
}

void Entity::addGroup(Group grp)
{
    groupBitSet[grp] = true;
    _mgr.addEntityToGroup(this, grp);
}

void Entity::delGroup(Group grp)
{
    groupBitSet[grp] = false;
}

bool Entity::hasGroup(Group grp)
{
    return groupBitSet[grp];
}

void Entity::SetDontDestroyOnLoad(bool state)
{
    _dontDesOnLoad = state;
}

bool Entity::GetDontDestroyOnLoad() const
{
    return _dontDesOnLoad;
}

bool Entity::isActive() const
{
    return _active;
}

AssetLoader *Entity::assets()
{
    if (!_mgr._onRefresh) return nullptr;
    return &_mgr.getEntByName("AssetLoader")
        ->getComponent<AssetLoader>();
}
