/*
** EPITECH PROJECT, 2024
** PlayerHUDComp.cpp
** File description:
** Created by Achille Bourgault
*/

#include <GUI/SubPanelComp.hpp>
#include "Components/Player/PlayerHUDComp.hpp"
#include <ECS/Manager.hpp>
#include <Mediator.hpp>
#include <Client.hpp>
#include "AssetLoader.hpp"
#include "TransformComp.hpp"

void PlayerHUDComp::init()
{
    Component::init();

    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    }

    playerIcon =
        &entity->addComponent<SpriteComp>(
            entity->assets()->getPlayerTexture(entity->_mgr._client.mediator.getLocalPlayerId()),
            sf::Vector2u{5, 1}, 0, 2
        );

    playerIcon->entity->getComponent<TransformComp>().position.x = entity->_mgr.mainWindow.getSize().x * 0.02;
    playerIcon->entity->getComponent<TransformComp>().position.y = entity->_mgr.mainWindow.getSize().y * 0.91;
    playerIcon->entity->addGroup(GUI);

    int height = 70;

    auto &hudLeft = entity->_mgr.addEntity("hudLeft");
    hud = &hudLeft.addComponent<SubPanelComp>(entity->_mgr.mainWindow.getSize().x, height, sf::Color(69, 36, 138, 100));
    hudLeft.getComponent<TransformComp>().position.x = 0;
    hudLeft.getComponent<TransformComp>().position.y = entity->_mgr.mainWindow.getSize().y - height;
    hudLeft.addGroup(Background);


    auto &healthTextValueEnt = entity->_mgr.addEntity("hudHealthValueText");
    healthTextValue = &healthTextValueEnt.addComponent<TextComp>(std::to_string(1), 42);
    healthTextValueEnt.getComponent<TransformComp>().position.x = entity->_mgr.mainWindow.getSize().x * 0.1;
    healthTextValueEnt.getComponent<TransformComp>().position.y = entity->_mgr.mainWindow.getSize().y * 0.895;
    healthTextValueEnt.addGroup(GUI);

    auto &scoreTextLabelEnt = entity->_mgr.addEntity("hudScoreLabelText");
    scoreTextLabel = &scoreTextLabelEnt.addComponent<TextComp>("SCORE", 35);
    scoreTextLabelEnt.getComponent<TransformComp>().position.x = entity->_mgr.mainWindow.getSize().x * 0.76;
    scoreTextLabelEnt.getComponent<TransformComp>().position.y = entity->_mgr.mainWindow.getSize().y * 0.9;
    scoreTextLabelEnt.addGroup(GUI);

    auto &scoreTextValueEnt = entity->_mgr.addEntity("hudScoreValueText");
    scoreTextValue = &scoreTextValueEnt.addComponent<TextComp>(std::to_string(entity->_mgr._client.mediator.get_player_score()), 42, sf::Color(242, 234, 138));
    scoreTextValueEnt.getComponent<TransformComp>().position.x = entity->_mgr.mainWindow.getSize().x * 0.88;
    scoreTextValueEnt.getComponent<TransformComp>().position.y = entity->_mgr.mainWindow.getSize().y * 0.895;
    scoreTextValueEnt.addGroup(GUI);


}

void PlayerHUDComp::draw()
{
    hud->draw();
    scoreTextLabel->draw();
    scoreTextValue->draw();
    healthTextValue->draw();
}

void PlayerHUDComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    std::string obj = scoreTextValue->text.getString();
    if (std::to_string(entity->_mgr._client.mediator.get_player_score()) != obj) {
        entity->assets()->explosion.play();
        scoreTextValue->text.setString(std::to_string(entity->_mgr._client.mediator.get_player_score()));
    }
    Component::update(t, dt, inputs);
    //    text.setPosition(entity->getComponent<TransformComp>().spawnPos);
}

PlayerHUDComp::PlayerHUDComp()
{
}
