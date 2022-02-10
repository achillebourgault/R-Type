/*
** EPITECH PROJECT, 2024
** bomberman
** File description:
** Created by Achille Bourgault
*/

#ifndef BACKGROUNDCOMP_HPP
#define BACKGROUNDCOMP_HPP

#include <ECS/Component.hpp>
#include <ECS/Manager.hpp>

class BackgroundComponent : public Component {
    public:
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    void draw() override;
    private:
    float scrollA;
    float scrollB;
    float scrollC;
    float scrollD;
    float scrollE;
    float scale = 3.25f;
    Entity *bgAEnt;
    Entity *bgBEnt;
    Entity *bgCEnt;
};

#endif //BACKGROUNDCOMP_HPP
