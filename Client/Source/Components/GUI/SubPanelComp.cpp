/*
** EPITECH PROJECT, 2024
** SubPanelComp.cpp
** File description:
** Created by Leo Fabre
*/

#include "Components/GUI/SubPanelComp.hpp"
#include "TransformComp.hpp"

SubPanelComp::SubPanelComp(int width, int height, sf::Color color)
    :
    shape()
{
    shape.setFillColor(color);
    shape.setSize(sf::Vector2f{(float) width, (float) height});

    //    font.loadFromFile("./Client/Assets/Cinzel-Regular.ttf");
    //    text = sf::Text(str, font, size);
}

void SubPanelComp::draw()
{
    //    entity->_mgr.mainWindow.draw(text);
    entity->_mgr.mainWindow.draw(shape);
}

void SubPanelComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    //    text.setPosition(entity->getComponent<TransformComp>().spawnPos);
    shape.setPosition(entity->getComponent<TransformComp>().position);
}

void SubPanelComp::init()
{
    Component::init();

    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    }
}