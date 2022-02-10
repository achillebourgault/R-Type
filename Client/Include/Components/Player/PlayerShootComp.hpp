/*
** EPITECH PROJECT, 2024
** PlayerShootComp.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef PLAYERSHOOTCOMP_HPP
#define PLAYERSHOOTCOMP_HPP
#include <ECS/Component.hpp>
#include "TransformComp.hpp"
#include <functional>
#include <ECS/Manager.hpp>
#include <SFML/Audio.hpp>

class PlayerShootComp : public Component {
public:
    explicit PlayerShootComp(
        const std::string &player_name, bool isLocallyControlled,
        sf::Sound action
    );
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    //todo : net: this is called when a projectile was shot, notify server !
    std::function<void(std::string playerName)> OnProjectileShoot;
private:
    sf::Sound shoot;
    bool isLocallyControlled;
    std::string _playerName;
    bool isShootKeyDown = false;
    bool isShootKeyReleased = false;
    TransformComp *transform;
    void ShootProjectile();
    double shootForce;
    int projCount;
public:
    bool active = true;
    [[nodiscard]] double getShootForce() const;
    double forceSpeed;
    void UpdateShootForce(double dt, Manager::PlayerInputs inputs);
    sf::Texture & getProjectileTexture(double force);
    void SpawnProjectileProxy(double shootforce);
};

#endif //PLAYERSHOOTCOMP_HPP
