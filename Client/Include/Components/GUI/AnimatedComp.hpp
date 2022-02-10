/*
** EPITECH PROJECT, 2024
** AnimatedComp.hpp
** File description:
** Created by Achille Bourgault
*/

#ifndef AnimatedComp_HPP
#define AnimatedComp_HPP
#include "SFML/Graphics.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Manager.hpp"
#include "TransformComp.hpp"

class AnimatedComp : public Component {
public:
    explicit AnimatedComp(Component *component);
    void draw() override;
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;

    bool isAnimated = false;
    private:
    Component *component;
    TransformComp *transform;
    float yStart;
    float yTarget;
    float elapsedTime = 0.0f;
    float duration = 3.5f;
    int direction = 0;
    clock_t begin = clock();
};

#endif //AnimatedComp_HPP
