/*
** EPITECH PROJECT, 2024
** bomberman
** File description:
** Created by Achille Bourgault
*/

#include <BackgroundComponent.hpp>
#include <Components/AssetLoader.hpp>
#include <ECS/Component.hpp>
#include <ECS/Manager.hpp>
#include <Components/TransformComp.hpp>
#include <Components/GUI/SpriteComp.hpp>

void BackgroundComponent::init()
{
    Component::init();
    scrollA = 0;
    scrollB = entity->_mgr.mainWindow.getSize().x;
    scrollC = entity->_mgr.mainWindow.getSize().x * 0.06;

    scrollAsteroidA = (float) (rand()%((entity->_mgr.mainWindow.getSize().x + 400)-0 + 1) + 0);
    scrollAsteroidB = (float) (rand()%((entity->_mgr.mainWindow.getSize().x + 400)-0 + 1) + 0);
    scrollAsteroidC = (float) (rand()%((entity->_mgr.mainWindow.getSize().x + 400)-0 + 1) + 0);
    scrollAsteroidD = (float) (rand()%((entity->_mgr.mainWindow.getSize().x + 400)-0 + 1) + 0);
    scrollAsteroidE = (float) (rand()%((entity->_mgr.mainWindow.getSize().x + 400)-0 + 1) + 0);
    scrollAsteroidF = (float) (rand()%((entity->_mgr.mainWindow.getSize().x + 400)-0 + 1) + 0);
    scrollAsteroidG = (float) (rand()%((entity->_mgr.mainWindow.getSize().x + 400)-0 + 1) + 0);
    initEntities();

    auto &universeEnt = entity->_mgr.addEntity("universe");
    auto &universeComp = universeEnt.addComponent<SubPanelComp>(entity->_mgr.mainWindow.getSize().x, entity->_mgr.mainWindow.getSize().y,
    sf::Color(56, 33, 191, 32));
    universeEnt.addGroup(GUI);
    universeEnt.getComponent<TransformComp>().position.y = 0;
    universeEnt.SetDontDestroyOnLoad(true);
}

void BackgroundComponent::update( double t, double dt,
    Manager::PlayerInputs inputs) {
    Component::update(t, dt, inputs);
    scrollA -= 0.32f;
    scrollB -= 0.32f;
    scrollC -= 0.86f;

    scrollAsteroidA -= 2.1f;
    scrollAsteroidB -= 2.2f;
    scrollAsteroidC -= 1.6f;
    scrollAsteroidD -= 2.7f;
    scrollAsteroidE -= 2.2f;
    scrollAsteroidF -= 2.55f;
    scrollAsteroidG -= 2.00f;

    rotationA += 1;
    rotationB -= 1;
    rotationC += 1;
    rotationD -= 1;
    rotationE -= 1;
    rotationF += 1;
    rotationG += 1;

    bgAsteroidAEnt->getComponent<SpriteComp>().sprite.setRotation(rotationA);
    bgAsteroidBEnt->getComponent<SpriteComp>().sprite.setRotation(rotationB);
    bgAsteroidCEnt->getComponent<SpriteComp>().sprite.setRotation(rotationC);
    bgAsteroidDEnt->getComponent<SpriteComp>().sprite.setRotation(rotationD);
    bgAsteroidEEnt->getComponent<SpriteComp>().sprite.setRotation(rotationE);
    bgAsteroidFEnt->getComponent<SpriteComp>().sprite.setRotation(rotationF);
    bgAsteroidGEnt->getComponent<SpriteComp>().sprite.setRotation(rotationG);

    if (scrollA <= (-(entity->_mgr.mainWindow.getViewport(entity->_mgr.mainWindow.getDefaultView()).width))) scrollA = 0;
    if (scrollB <= 0) scrollB = entity->_mgr.mainWindow.getSize().x;
    if (scrollC <= -(entity->_mgr.mainWindow.getViewport(entity->_mgr.mainWindow.getDefaultView()).width * 1.25)) {
        scrollC = entity->_mgr.mainWindow.getSize().x;
        int max = entity->_mgr.mainWindow.getSize().y * 0.90;
        int min = entity->_mgr.mainWindow.getSize().y * 0.15;
        planetAHeight = rand()%((max)-min + 1) + min;
    }
    if (scrollAsteroidA <= -(rand()%((280)-150 + 1) + 150)) scrollAsteroidA = entity->_mgr.mainWindow.getSize().x + rand()%((450)-20 + 1) + 20;
    if (scrollAsteroidB <= -(rand()%((280)-150 + 1) + 150)) scrollAsteroidB = entity->_mgr.mainWindow.getSize().x + rand()%((450)-20 + 1) + 20;
    if (scrollAsteroidC <= -(rand()%((280)-150 + 1) + 150)) scrollAsteroidC = entity->_mgr.mainWindow.getSize().x + rand()%((450)-20 + 1) + 20;
    if (scrollAsteroidD <= -(rand()%((280)-150 + 1) + 150)) scrollAsteroidD = entity->_mgr.mainWindow.getSize().x + rand()%((450)-20 + 1) + 20;
    if (scrollAsteroidE <= -(rand()%((280)-150 + 1) + 150)) scrollAsteroidE = entity->_mgr.mainWindow.getSize().x + rand()%((450)-20 + 1) + 20;
    if (scrollAsteroidF <= -(rand()%((280)-150 + 1) + 150)) scrollAsteroidF = entity->_mgr.mainWindow.getSize().x + rand()%((450)-20 + 1) + 20;
    if (scrollAsteroidG <= -(rand()%((280)-150 + 1) + 150)) scrollAsteroidG = entity->_mgr.mainWindow.getSize().x + rand()%((450)-20 + 1) + 20;
}

void BackgroundComponent::draw()
{
    Component::draw();

    bgAEnt->getComponent<TransformComp>().position.x = scrollA;
    bgAEnt->getComponent<TransformComp>().position.y = 0;
    bgBEnt->getComponent<TransformComp>().position.x = scrollB;
    bgBEnt->getComponent<TransformComp>().position.y = 0;
    bgCEnt->getComponent<TransformComp>().position.x = scrollC;
    bgCEnt->getComponent<TransformComp>().position.y = (float)planetAHeight;

    bgAsteroidAEnt->getComponent<TransformComp>().position.x = scrollAsteroidA;
    bgAsteroidAEnt->getComponent<TransformComp>().position.y = (float)asteroidAHeight;
    bgAsteroidBEnt->getComponent<TransformComp>().position.x = scrollAsteroidB;
    bgAsteroidBEnt->getComponent<TransformComp>().position.y = (float)asteroidBHeight;
    bgAsteroidCEnt->getComponent<TransformComp>().position.x = scrollAsteroidC;
    bgAsteroidCEnt->getComponent<TransformComp>().position.y = (float)asteroidCHeight;
    bgAsteroidDEnt->getComponent<TransformComp>().position.x = scrollAsteroidD;
    bgAsteroidDEnt->getComponent<TransformComp>().position.y = (float)asteroidDHeight;
    bgAsteroidEEnt->getComponent<TransformComp>().position.x = scrollAsteroidE;
    bgAsteroidEEnt->getComponent<TransformComp>().position.y = (float)asteroidEHeight;
    bgAsteroidFEnt->getComponent<TransformComp>().position.x = scrollAsteroidF;
    bgAsteroidFEnt->getComponent<TransformComp>().position.y = (float)asteroidFHeight;
    bgAsteroidGEnt->getComponent<TransformComp>().position.x = scrollAsteroidG;
    bgAsteroidGEnt->getComponent<TransformComp>().position.y = (float)asteroidGHeight;
    bgAsteroidAEnt->getComponent<TransformComp>().position.x = scrollAsteroidA;
    bgAsteroidAEnt->getComponent<TransformComp>().position.y = (float)asteroidAHeight;
}

void BackgroundComponent::initEntities()
{
    bgAEnt = &entity->_mgr.addEntity("bgA"); bgAEnt->addGroup(Background);
    bgBEnt = &entity->_mgr.addEntity("bgB"); bgBEnt->addGroup(Background);
    bgCEnt = &entity->_mgr.addEntity("bgC"); bgCEnt->addGroup(Background);

    bgAsteroidAEnt = &entity->_mgr.addEntity("bgAsteroidA"); bgAsteroidAEnt->addGroup(Background);
    bgAsteroidBEnt = &entity->_mgr.addEntity("bgAsteroidB"); bgAsteroidBEnt->addGroup(Background);
    bgAsteroidCEnt = &entity->_mgr.addEntity("bgAsteroidC"); bgAsteroidCEnt->addGroup(Background);
    bgAsteroidDEnt = &entity->_mgr.addEntity("bgAsteroidD"); bgAsteroidDEnt->addGroup(Background);
    bgAsteroidEEnt = &entity->_mgr.addEntity("bgAsteroidE"); bgAsteroidEEnt->addGroup(Background);
    bgAsteroidFEnt = &entity->_mgr.addEntity("bgAsteroidF"); bgAsteroidFEnt->addGroup(Background);
    bgAsteroidGEnt = &entity->_mgr.addEntity("bgAsteroidG"); bgAsteroidGEnt->addGroup(Background);

    bgAEnt->SetDontDestroyOnLoad(true);
    bgBEnt->SetDontDestroyOnLoad(true);
    bgCEnt->SetDontDestroyOnLoad(true);
    bgAsteroidAEnt->SetDontDestroyOnLoad(true);
    bgAsteroidBEnt->SetDontDestroyOnLoad(true);
    bgAsteroidCEnt->SetDontDestroyOnLoad(true);
    bgAsteroidDEnt->SetDontDestroyOnLoad(true);
    bgAsteroidEEnt->SetDontDestroyOnLoad(true);
    bgAsteroidFEnt->SetDontDestroyOnLoad(true);
    bgAsteroidGEnt->SetDontDestroyOnLoad(true);


    auto &bgAComp = bgAEnt->addComponent<SpriteComp>(
        bgAEnt->assets()->MenuASprite, sf::Vector2u{1,1}, 5, 1.5);
    auto &bgBComp = bgBEnt->addComponent<SpriteComp>(
        bgBEnt->assets()->MenuBSprite, sf::Vector2u{1,1}, 5, 1.5);
    auto &bgCComp = bgCEnt->addComponent<SpriteComp>(
        bgCEnt->assets()->MenuCSprite, sf::Vector2u{1,1}, 5, 0.52);

    //Asteroids
    auto &bgAsteroidAComp= bgAsteroidAEnt->addComponent<SpriteComp>(
        bgAsteroidAEnt->assets()->MenuAsteroid, sf::Vector2u{1,1},
        5, 0.00 + (float)(rand()) / ((float)(RAND_MAX/(0.32 - 0.00))));
    auto &bgAsteroidBComp= bgAsteroidBEnt->addComponent<SpriteComp>(
        bgAsteroidBEnt->assets()->MenuAsteroid, sf::Vector2u{1,1},
        5, 0.00 + (float)(rand()) / ((float)(RAND_MAX/(0.32 - 0.00))));
    auto &bgAsteroidCComp= bgAsteroidCEnt->addComponent<SpriteComp>(
        bgAsteroidCEnt->assets()->MenuAsteroid, sf::Vector2u{1,1},
        5, 0.00 + (float)(rand()) / ((float)(RAND_MAX/(0.32 - 0.00))));
    auto &bgAsteroidDComp= bgAsteroidDEnt->addComponent<SpriteComp>(
        bgAsteroidDEnt->assets()->MenuAsteroid, sf::Vector2u{1,1},
        5, 0.00 + (float)(rand()) / ((float)(RAND_MAX/(0.32 - 0.00))));
    auto &bgAsteroidEComp= bgAsteroidEEnt->addComponent<SpriteComp>(
        bgAsteroidEEnt->assets()->MenuAsteroid, sf::Vector2u{1,1},
        5, 0.00 + (float)(rand()) / ((float)(RAND_MAX/(0.32 - 0.00))));
    auto &bgAsteroidFComp= bgAsteroidFEnt->addComponent<SpriteComp>(
        bgAsteroidFEnt->assets()->MenuAsteroid, sf::Vector2u{1,1},
        5, 0.00 + (float)(rand()) / ((float)(RAND_MAX/(0.32 - 0.00))));
    auto &bgAsteroidGComp= bgAsteroidGEnt->addComponent<SpriteComp>(
        bgAsteroidGEnt->assets()->MenuAsteroid, sf::Vector2u{1,1},
        5, 0.00 + (float)(rand()) / ((float)(RAND_MAX/(0.32 - 0.00))));

    int max = entity->_mgr.mainWindow.getSize().y * 0.75;
    int min = entity->_mgr.mainWindow.getSize().y * 0.15;
    planetAHeight = rand()%(max-min + 1) + min;
    bgCEnt->getComponent<TransformComp>().position.y = planetAHeight;

    asteroidAHeight = rand()%(max-min + 1) + min;
    asteroidBHeight = rand()%(max-min + 1) + min;
    asteroidCHeight = rand()%(max-min + 1) + min;
    asteroidDHeight = rand()%(max-min + 1) + min;
    asteroidEHeight = rand()%(max-min + 1) + min;
    asteroidFHeight = rand()%(max-min + 1) + min;
    asteroidGHeight = rand()%(max-min + 1) + min;

    bgAsteroidAEnt->getComponent<TransformComp>().position.y = (float)asteroidAHeight;
    bgAsteroidAEnt->getComponent<TransformComp>().position.x = scrollAsteroidA;
    bgAsteroidBEnt->getComponent<TransformComp>().position.y = (float)asteroidBHeight;
    bgAsteroidBEnt->getComponent<TransformComp>().position.x = scrollAsteroidB;
    bgAsteroidCEnt->getComponent<TransformComp>().position.y = (float)asteroidCHeight;
    bgAsteroidCEnt->getComponent<TransformComp>().position.x = scrollAsteroidC;
    bgAsteroidDEnt->getComponent<TransformComp>().position.y = (float)asteroidDHeight;
    bgAsteroidDEnt->getComponent<TransformComp>().position.x = scrollAsteroidD;
    bgAsteroidEEnt->getComponent<TransformComp>().position.y = (float)asteroidEHeight;
    bgAsteroidEEnt->getComponent<TransformComp>().position.x = scrollAsteroidE;
    bgAsteroidFEnt->getComponent<TransformComp>().position.y = (float)asteroidFHeight;
    bgAsteroidFEnt->getComponent<TransformComp>().position.x = scrollAsteroidF;
    bgAsteroidGEnt->getComponent<TransformComp>().position.y = (float)asteroidGHeight;
    bgAsteroidGEnt->getComponent<TransformComp>().position.x = scrollAsteroidG;
}
#pragma clang diagnostic pop