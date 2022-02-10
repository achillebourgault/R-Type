/*
** EPITECH PROJECT, 2024
** AnimatedComp.cpp
** File description:
** Created by Achille Bourgault
*/

#include "Components/GUI/AnimatedComp.hpp"
#include <ECS/Manager.hpp>
#include <thread>
#include <Client.hpp>
#include <cmath>
#include <GUI/TextButton.hpp>
#include <Scenes/MenuScene.hpp>
#include "TransformComp.hpp"

#define PI 3.14

AnimatedComp::AnimatedComp(Component *component) :
    component(component) {
    yStart = (float)(component->entity->_mgr.mainWindow.getSize().y * 0.53);
    yTarget = (float)(component->entity->_mgr.mainWindow.getSize().y * 0.58);
}

void AnimatedComp::draw()
{
    component->draw();
}

float EaseIn(float x)
{
    return 1 - cos((x * PI) / 2);
}

float animationEase(double t, double dt, Manager::PlayerInputs inputs,
    float yStart, float yTarget, float elapsedTime, float duration,
    Component *component, AnimatedComp *obj, sf::Thread *me)
{
    float speed = 5;

    if (!component->entity->_mgr.mainWindow.isOpen() ||
        obj->isAnimated) {
        return 0;
    }
    obj->isAnimated = true;
    while (elapsedTime <= duration) {
        clock_t begin = clock();
        float lerp = std::lerp(yStart, yTarget, EaseIn(elapsedTime / duration));
        sf::sleep(sf::milliseconds(speed));
        component->entity->getComponent<TransformComp>().position.y = lerp;
//        std::cout << "Animation > lerp= " << lerp << std::endl;
        component->update(t, dt, inputs);
        component->entity->_mgr.draw();
        component->entity->_mgr.update(t, dt, inputs);
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        elapsedTime += 0.1;
//        std::cout << elapsedTime << std::endl;
    }
    std::cout << "anim finished" << std::endl;
//    float tmp = (float) yStart;
//    yStart = yTarget;
//    yTarget = tmp;
//    sf::sleep(sf::milliseconds(2800));
    obj->isAnimated = false;
}

void AnimatedComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        component->entity->_mgr.LoadScene<MenuScene>();
    }
    float lerp = std::lerp(yStart, yTarget, EaseIn(elapsedTime / duration));
    elapsedTime += 0.1;
    component->entity->getComponent<TransformComp>().position.y = lerp;
}

void AnimatedComp::init()
{
    Component::init();
}