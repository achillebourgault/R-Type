/*
** EPITECH PROJECT, 2024
** PlayerShootComp.cpp
** File description:
** Created by Leo Fabre
*/
#include "Components/Player/PlayerShootComp.hpp"
#include "Components/Player/PlayerComp.hpp"
#include "ProjectileComp.hpp"
#include <ECS/Entity.hpp>
#include <ECS/Manager.hpp>
#include <AssetLoader.hpp>
#include "Client.hpp"

PlayerShootComp::PlayerShootComp(
    const std::string &player_name, bool isLocallyControlled,
    sf::Sound action
)
    : _playerName(player_name),
      shootForce(0),
      forceSpeed(80),
      isLocallyControlled(isLocallyControlled),
      shoot(action)
{
}

void PlayerShootComp::init()
{
    Component::init();
    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    } else {
        transform = &entity->getComponent<TransformComp>();
    }
}

void PlayerShootComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    if (!active || !isLocallyControlled || !entity->_mgr.mainWindow.hasFocus()) return;
    UpdateShootForce(dt, inputs);
    if (inputs.shootReleased) {
        ShootProjectile();
        shootForce = 0;
    }
}

void PlayerShootComp::UpdateShootForce(double dt, Manager::PlayerInputs inputs)
{
    if (!isLocallyControlled || !entity->_mgr.mainWindow.hasFocus()) return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        shootForce += (dt * forceSpeed);
    if (shootForce >= 100)
        shootForce = 100;
}

void PlayerShootComp::ShootProjectile()
{
    //projectile setup
    std::string entName
        ("proj" + entity->getComponent<PlayerComp>().getPlayerName() +
            std::to_string(static_cast<unsigned int>(std::time(nullptr))));
    auto &projectileSprite = getProjectileTexture(shootForce);
    auto spawnPos = transform->position;
    spawnPos.x += 70;
    spawnPos.y += 17;
    auto direction = sf::Vector2i {1,0};
    float speed = 15;
    //entity spawning
    auto &projectileEnt = entity->_mgr.addEntity(entName);
    projectileEnt.addGroup(GroupLabel::MyProjectiles);
    projectileEnt.addComponent<ProjectileComp>(
        projectileSprite,
        direction,
        speed,
        sf::Vector2u {1,1},
        0.f,
        2,
        0,
        entity->_mgr._client.mediator.getLocalPlayerId()
        );
    projectileEnt.getComponent<TransformComp>().position = spawnPos;
    shoot.play();
    std::cout << "PEW" << std::endl;
    entity->_mgr._client.mediator.shotMissile = true;
    entity->_mgr._client.mediator.missileSize = shootForce;//TODO: refactor so missiles can be created easier with networking
    //
}

void PlayerShootComp::SpawnProjectileProxy(double shootforce)
{
    //projectile setup
    std::string entName
        ("proj" + entity->getComponent<PlayerComp>().getPlayerName() +
            std::to_string(static_cast<unsigned int>(std::time(nullptr))));
    auto &projectileSprite = getProjectileTexture(shootforce);
    auto spawnPos = transform->position;
    spawnPos.x += 70;
    spawnPos.y += 17;
    auto direction = sf::Vector2i {1,0};
    float speed = 15;
    //entity spawning
    auto &projectileEnt = entity->_mgr.addEntity(entName);
    projectileEnt.addGroup(GroupLabel::AlliesProjectiles);
    projectileEnt.addComponent<ProjectileComp>(
        projectileSprite,
        direction,
        speed,
        sf::Vector2u {1,1},
        0.f,
        2
        );
    projectileEnt.getComponent<TransformComp>().position = spawnPos;
    std::cout << "PEW" << std::endl;
}

sf::Texture & PlayerShootComp::getProjectileTexture(double force)
{
    if (force >= (100 / 6) * 6) {
        return entity->assets()->PlayerProjectileForce5;
    } else if (force >= (100 / 6) * 5) {
        return entity->assets()->PlayerProjectileForce4;
    } else if (force >= (100 / 6) * 4) {
        return entity->assets()->PlayerProjectileForce3;
    } else if (force >= (100 / 6) * 3) {
        return entity->assets()->PlayerProjectileForce2;
    } else if (force >= (100 / 6) * 2) {
        return entity->assets()->PlayerProjectileForce1;
    } else {
        return entity->assets()->PlayerProjectileBasic;
    }
}

double PlayerShootComp::getShootForce() const
{
    //there are 6 types of projectiles including basic
    return shootForce;
}
