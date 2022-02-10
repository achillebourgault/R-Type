/*
** EPITECH PROJECT, 2024
** MonsterComp.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef MONSTERCOMP_HPP
#define MONSTERCOMP_HPP
#include "ECS/Component.hpp"
#include "TransformComp.hpp"
#include "GUI/SpriteComp.hpp"
#include "GameState.h"

class MonsterComp : public Component {
public:
    MonsterComp(unsigned int type, unsigned int id);

    void init() override;

    sf::Texture &getMonsterTexture(unsigned int i);
    sf::Vector2u getNbReps(unsigned int i) const;

    unsigned int type;
    unsigned int id;

    TransformComp *transform;
    SpriteComp *spriteComp;
    void ShootMonsterMissile(MonsterInfo &info);
};

#endif //MONSTERCOMP_HPP
