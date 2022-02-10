/*
** EPITECH PROJECT, 2024
** MonsterComp.cpp
** File description:
** Created by Leo Fabre
*/
#include "MonsterComp.hpp"
#include "GUI/SpriteComp.hpp"
#include "ProjectileComp.hpp"
#include <ECS/Entity.hpp>
#include <AssetLoader.hpp>

MonsterComp::MonsterComp(unsigned int type, unsigned int id)
    : type(type),
      id(id)
{
}

void MonsterComp::init()
{
    Component::init();
    entity->addGroup(Monsters);
    //tc
    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    } else {
        transform = &entity->getComponent<TransformComp>();
    }

    if (!entity->hasComponent<SpriteComp>()) {
        spriteComp = &entity->addComponent<SpriteComp>(
            getMonsterTexture(
                type), //todo: change sprite depending on monsterType
            getNbReps(type),
            0.5,
            3
        );
    } else {
        spriteComp = &entity->getComponent<SpriteComp>();
    }

    auto playerBounds =
        entity->getComponent<SpriteComp>().sprite.getLocalBounds();
}

sf::Vector2u MonsterComp::getNbReps(unsigned int type) const
{
    return sf::Vector2u{8, 1};
}

sf::Texture &MonsterComp::getMonsterTexture(unsigned int type)
{
    return entity->assets()->Monster1Sprite;
}

void MonsterComp::ShootMonsterMissile(MonsterInfo &info)
{
    std::cout << "Preparing monster projectile" << std::endl;
    //projectile setup
    std::string entName
        ("enemyProj" + std::to_string(
            entity->_mgr.getEntitiesInGroup(EnemiesProjectiles).size() + 1));
    auto &projectileSprite = entity->assets()->MonsterProjSprite;
    auto spawnPos = sf::Vector2f{
        std::get<0>(info.monsterPos),
        std::get<1>(info.monsterPos)
    };
    spawnPos.x += 50;
    spawnPos.y += 50;
    auto direction = sf::Vector2i{
        std::get<0>(info.missileDirection),
        std::get<1>(info.missileDirection)
    };
    float speed = 10;
    //entity spawning
    auto &projectileEnt = entity->_mgr.addEntity(entName);
    projectileEnt.addGroup(GroupLabel::EnemiesProjectiles);
    projectileEnt.addComponent<ProjectileComp>(
        projectileSprite,
        direction,
        speed,
        sf::Vector2u{4, 1},
        0.2f,
        1
    );
    projectileEnt.getComponent<TransformComp>().position = spawnPos;
    std::cout << "ENEMY PROJECTILE FIRED" << std::endl;
}
