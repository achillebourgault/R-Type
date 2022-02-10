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
#include <GUI/SubPanelComp.hpp>

class BackgroundComponent : public Component {
    public:
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    void draw() override;
    private:
    float scrollA;
    float scrollB;
    float scrollC;

    int rotationA = 0;
    int rotationB = 0;
    int rotationC = 0;
    int rotationD = 0;
    int rotationE = 0;
    int rotationF = 0;
    int rotationG = 0;

    float scrollAsteroidA;
    float scrollAsteroidB;
    float scrollAsteroidC;
    float scrollAsteroidD;
    float scrollAsteroidE;
    float scrollAsteroidF;
    float scrollAsteroidG;

    int planetAHeight;

    int asteroidAHeight;
    int asteroidBHeight;
    int asteroidCHeight;
    int asteroidDHeight;
    int asteroidEHeight;
    int asteroidFHeight;
    int asteroidGHeight;

    float scale = 3.25f;
    Entity *bgAEnt;
    Entity *bgBEnt;
    Entity *bgCEnt;

    Entity *bgAsteroidAEnt;
    Entity *bgAsteroidBEnt;
    Entity *bgAsteroidCEnt;
    Entity *bgAsteroidDEnt;
    Entity *bgAsteroidEEnt;
    Entity *bgAsteroidFEnt;
    Entity *bgAsteroidGEnt;
    SubPanelComp *universe;
    void initEntities();
};

#endif //BACKGROUNDCOMP_HPP
