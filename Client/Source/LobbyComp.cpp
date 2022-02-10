/*
** EPITECH PROJECT, 2024
** LobbyComp.cpp
** File description:
** Created by Leo Fabre
*/

#include "LobbyComp.hpp"
#include "ECS/Manager.hpp"
#include "ECS/Entity.hpp"
#include <Client.hpp>

void LobbyComp::init()
{
    Component::init();
    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    }
    transform = &entity->getComponent<TransformComp>();
    auto &subPanPlayersEnt = entity->_mgr.addEntity("subPanPlayers");
    subPanPlayersEnt.addGroup(GUI);
    panPlayers = &subPanPlayersEnt.addComponent<SubPanelComp>(400,
        entity->_mgr.mainWindow.getSize().y,
        sf::Color(69, 36, 138, 150));
    subPanPlayersEnt.getComponent<TransformComp>().position =
        transform->position;
    subPanPlayersEnt.getComponent<TransformComp>().position.y = 0;

    auto &labelPlayersEnt = entity->_mgr.addEntity("labelPlayers");
    labelPlayersEnt.addGroup(GUI_TOP);
    labelPlayers = &labelPlayersEnt.addComponent<TextComp>("Players :", 45);
    labelPlayersEnt.getComponent<TransformComp>().position =
        transform->position + sf::Vector2f{60, 25};


    //add player names
    auto &p1nameEnt = entity->_mgr.addEntity("p1Name");
    p1nameEnt.addGroup(GUI_TOP);
    auto &p2nameEnt = entity->_mgr.addEntity("p2Name");
    p2nameEnt.addGroup(GUI_TOP);
    auto &p3nameEnt = entity->_mgr.addEntity("p3Name");
    p3nameEnt.addGroup(GUI_TOP);
    auto &p4nameEnt = entity->_mgr.addEntity("p4Name");
    p4nameEnt.addGroup(GUI_TOP);
    player1 = &p1nameEnt.addComponent<TextComp>(
        entity->_mgr._client.mediator.playernames[0], 23);
    player2 = &p2nameEnt.addComponent<TextComp>(
        entity->_mgr._client.mediator.playernames[1], 23);
    player3 = &p3nameEnt.addComponent<TextComp>(
        entity->_mgr._client.mediator.playernames[2], 23);
    player4 = &p4nameEnt.addComponent<TextComp>(
        entity->_mgr._client.mediator.playernames[3], 23);
    p1nameEnt.getComponent<TransformComp>().position =
        transform->position + sf::Vector2f{75, 80 + 70};
    p2nameEnt.getComponent<TransformComp>().position =
        transform->position + sf::Vector2f{75, 140 + 70};
    p3nameEnt.getComponent<TransformComp>().position =
        transform->position + sf::Vector2f{75, 200 + 70};
    p4nameEnt.getComponent<TransformComp>().position =
        transform->position + sf::Vector2f{75, 260 + 70};
}

void LobbyComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    //update player names from mediator
    player1->text.setString(entity->_mgr._client.mediator.playernames[0]);
    player2->text.setString(entity->_mgr._client.mediator.playernames[1]);
    player3->text.setString(entity->_mgr._client.mediator.playernames[2]);
    player4->text.setString(entity->_mgr._client.mediator.playernames[3]);
    //Set ready text color
    player1->text.setFillColor(
        entity->_mgr._client.mediator.readiness[0] ? sf::Color::Green : sf::Color::White);
    player2->text.setFillColor(
        entity->_mgr._client.mediator.readiness[1] ? sf::Color::Green : sf::Color::White);
    player3->text.setFillColor(
        entity->_mgr._client.mediator.readiness[2] ? sf::Color::Green : sf::Color::White);
    player4->text.setFillColor(
        entity->_mgr._client.mediator.readiness[3] ? sf::Color::Green : sf::Color::White);
}

void LobbyComp::draw()
{
    Component::draw();
}
