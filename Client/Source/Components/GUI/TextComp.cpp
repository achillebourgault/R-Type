/*
** EPITECH PROJECT, 2024
** TextComp.cpp
** File description:
** Created by Leo Fabre
*/

#include "Components/GUI/TextComp.hpp"
#include "TransformComp.hpp"

TextComp::TextComp(std::string str, int size, sf::Color color)
    : text(), font()
{
    font.loadFromFile("./Client/Assets/Cinzel-Regular.ttf");
    text = sf::Text(str, font, size);
    text.setFillColor(color);
}

void TextComp::draw()
{
    entity->_mgr.mainWindow.draw(text);
}

void TextComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    text.setPosition(entity->getComponent<TransformComp>().position);
}
void TextComp::init()
{
    Component::init();

    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    }
    transform = &entity->getComponent<TransformComp>();
}

void TextComp::centerHorizontally()
{
    auto txtWidth = text.getLocalBounds().width;
    auto screenWidth = entity->_mgr.mainWindow.getSize().x;
    transform->position.x = (screenWidth / 2) - (txtWidth / 2);
}
