/*
** EPITECH PROJECT, 2024
** PlayerMovementComp.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef PLAYERMOVEMENTCOMP_HPP
#define PLAYERMOVEMENTCOMP_HPP
#include <ECS/Component.hpp>
#include <TransformComp.hpp>
#include <ECS/Entity.hpp>

class PlayerMovementComp : public Component {
public:
    PlayerMovementComp(bool isLocallyControlled = true)
        : transform(nullptr),
          _isLocallyControlled(isLocallyControlled)
    {
    }
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    //mediator will call this one instead
    void updateAsProxy(sf::Vector2f position, Manager::PlayerInputs inputs);
    float speed = 500.f;

    void blockInputs();
private:
    bool _isLocallyControlled;
    sf::Clock animTimer;
    TransformComp *transform;
    enum AnimState {
        downMax = 0,
        down = 1,
        straight = 2,
        up = 3,
        upMax = 4
    } anim_state, last_state;
    bool resettingAnim = false;
    int updateAnimState();
    bool _active = true;
};

#endif //PLAYERMOVEMENTCOMP_HPP
