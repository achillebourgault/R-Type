/*
** EPITECH PROJECT, 2024
** ProjectileComp.cpp
** File description:
** Created by Leo Fabre
*/

#include "ProjectileComp.hpp"
#include "MonsterComp.hpp"
#include "ExplosionFxComp.hpp"
#include <ECS/Manager.hpp>
#include <ECS/Entity.hpp>

ProjectileComp::ProjectileComp(
    sf::Texture &sprite, sf::Vector2i direction,
    float speed, sf::Vector2u nb_reps, float update_freq, float scale,
    unsigned int type, int shotby
)
    : projectileSprite(nullptr),
      direction(direction),
      _texture(sprite),
      speed(speed),
      nbReps(nb_reps),
      updateFreq(update_freq),
      scale(scale),
      type(type),
      shotBy(shotby)
{
}

void ProjectileComp::init()
{
    Component::init();
    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    } else {
        transform = &entity->getComponent<TransformComp>();
    }
    transform->position = spawnPos;
    projectileSprite =
        &entity->addComponent<SpriteComp>(_texture, nbReps, updateFreq, scale);
}

void ProjectileComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    transform->position +=
        sf::Vector2f{(float) direction.x * speed, (float) direction.y * speed};
    //return;

    //check monsters
    CheckMonsters();

    //destroy proj if out of window
    if (transform->position.x >
        (float) (entity->_mgr.mainWindow.getSize().x + 30)) {
        std::cout << "destroy proj" << std::endl;
        entity->destroy();
    }
}

void ProjectileComp::draw()
{
    Component::draw();
}

#include <Client.hpp>

void ProjectileComp::CheckMonsters()
{
    std::cout << "shotby " << shotBy << std::endl;
    if (shotBy == -1 ||
        shotBy != entity->_mgr._client.mediator.getLocalPlayerId())
        return;
    auto projRect = entity->getComponent<SpriteComp>().sprite.getGlobalBounds();
    for (auto &monster: entity->_mgr.getEntitiesInGroup(Monsters)) {
        auto monsterRect = monster->getComponent<SpriteComp>().sprite.getGlobalBounds();
        if (projRect.intersects(monsterRect)) {
            auto& booment = entity->_mgr.addEntity("boom");
            booment.addComponent<ExplosionFXComp>(
                monster->getComponent<TransformComp>().position);
            entity->_mgr._client.mediator.set_player_score(entity->_mgr._client.mediator.get_player_score() + 100);
            std::cout << entity->_mgr._client.mediator.get_player_score() << std::endl;
            std::cout << "HEADSHOT <3" << std::endl;
            monster->getComponent<SpriteComp>().sprite.setScale(0, 0);
            monster->destroy();//todo : add killer id to packet and add score to player
            entity->_mgr._client.
                onKilledMonster(monster->getComponent<MonsterComp>().id);
        }
    }
}