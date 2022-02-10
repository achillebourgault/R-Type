/*
** EPITECH PROJECT, 2024
** GameOverScene.cpp
** File description:
** Created by Achille Bourgault
*/
#include "Scenes/GameOverScene.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/LobbyScene.hpp"
#include <ECS/Entity.hpp>
#include <ECS/Manager.hpp>
#include <Components/GUI/TextComp.hpp>
#include <Components/GUI/TextButton.hpp>
#include <Scenes/MenuScene.hpp>
#include <Components/GUI/SubPanelComp.hpp>
#include <Scenes/OptionsScene.hpp>
#include <GUI/InputTextComp.hpp>
#include <BackgroundComponent.hpp>
#include <fstream>

#include <Client.hpp>
#include <Scenes/ConnectScene.hpp>
#include <AssetLoader.hpp>

void GameOverScene::load()
{
    std::cout << "GameOverScene : Loading GameOver scene" << std::endl;

    auto &titleEnt = _mgr.addEntity("mainLabel");
    auto &textComp = titleEnt.addComponent<TextComp>("Game Over !", 72, sf::Color(99, 82, 199));
    titleEnt.addGroup(GUI_TOP);
    textComp.centerHorizontally();
    titleEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.12;

    //TODO: replace with real score
    auto &scoreEnt = _mgr.addEntity("mainLabel");
    auto &scoreComp = scoreEnt.addComponent<TextComp>("Your score: 0", 36, sf::Color(212, 212, 212));
    scoreEnt.addGroup(GUI_TOP);
    scoreComp.centerHorizontally();
    scoreEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.32;

    auto &btnLeavePartyEnt = _mgr.addEntity("btnLeaveParty");
    auto &btnLeavePartyComp = btnLeavePartyEnt.addComponent<TextButton>(
        "Restart", [&btnLeavePartyEnt]() {
            btnLeavePartyEnt._mgr.LoadScene<ConnectScene>();
        }, btnLeavePartyEnt.assets()->click,
        sf::Vector2u{240, 55});
    btnLeavePartyEnt.addGroup(GUI);
    btnLeavePartyEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.66;
    btnLeavePartyEnt.getComponent<TransformComp>().position.x =
        (_mgr.mainWindow.getSize().x / 2) - (btnLeavePartyComp.btnRect.getSize().x / 2);
}


