/*
** EPITECH PROJECT, 2024
** PlayerMovementComp.c
** File description:
** Created by Leo Fabre
*/
#include <Components/Player/PlayerMovementComp.hpp>
#include <Components/GUI/SpriteComp.hpp>

void PlayerMovementComp::init()
{
    Component::init();
    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    } else {
        transform = &entity->getComponent<TransformComp>();
    }
}

void PlayerMovementComp::update(
    double t, double dt, Manager::PlayerInputs inputs
)
{
    Component::update(t, dt, inputs);
    if (!_active) return;
    entity->getComponent<SpriteComp>().setSpriteFrame(2);
    if (!_isLocallyControlled || !entity->_mgr.mainWindow.hasFocus()) return;
    //horizontal movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        transform->position.x -= speed * dt;
        if (transform->position.x < 0)
            transform->position.x = 0;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        transform->position.x += speed * dt;
        if (transform->position.x > 1125)
            transform->position.x = 1125;
    }
    //vertical movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        transform->position.y += speed * dt;
        resettingAnim = false;
        anim_state = down;
        if (transform->position.y > 550)
            transform->position.y = 550;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        transform->position.y -= speed * dt;
        resettingAnim = false;
        anim_state = up;
        if (transform->position.y < 0)
            transform->position.y = 0;
    } else {
        resettingAnim = true;
    }
    updateAnimState();
    if (last_state != anim_state) last_state = anim_state;
}

void PlayerMovementComp::updateAsProxy(
    sf::Vector2f position, Manager::PlayerInputs inputs
)
{
    //position update
    transform->position = position;
    //anim update
    if (inputs.downKeyDown) {
        resettingAnim = false;
        anim_state = down;
    } else if (inputs.upKeyDown) {
        resettingAnim = false;
        anim_state = up;
    } else {
        resettingAnim = true;
    }
    updateAnimState();
    if (last_state != anim_state) last_state = anim_state;
}

int PlayerMovementComp::updateAnimState()
{
    //if player begins to move from straight state
    if (anim_state != straight && last_state == straight) animTimer.restart();

    if (animTimer.getElapsedTime().asSeconds() >= 0.1) {
        if (!resettingAnim) {
            if (anim_state == up) anim_state = upMax;
            else if (anim_state == down) anim_state = downMax;
        } else {
            if (anim_state == downMax) {
                anim_state = down;
            } else if (anim_state == upMax) {
                anim_state = up;
            } else if (anim_state == up || anim_state == down) {
                anim_state = straight;
                resettingAnim = false;
            }
            animTimer.restart();
        }
    }
    entity->getComponent<SpriteComp>().setSpriteFrame(anim_state);
    return 0;
}

void PlayerMovementComp::blockInputs()
{
    _active = false;
}
