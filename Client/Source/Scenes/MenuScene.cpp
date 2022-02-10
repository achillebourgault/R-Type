/*
** EPITECH PROJECT, 2024
** MenuScene.cpp
** File description:
** Created by Leo Fabre
*/
#include "Scenes/MenuScene.hpp"
#include "Scenes/ScoresScene.hpp"
#include "Scenes/OptionsScene.hpp"
#include <ECS/Manager.hpp>
#include <AssetLoader.hpp>
#include <Components/GUI/TextComp.hpp>
#include <Components/GUI/TextButton.hpp>
#include <Components/GUI/SubPanelComp.hpp>
#include <Scenes/ConnectScene.hpp>

void MenuScene::load()
{
    loadSidebar();
}

void MenuScene::loadSidebar()
{
    auto &titleEnt = _mgr.addEntity("gameTitle");
    auto &textComp = titleEnt.addComponent<TextComp>("R-Type", 75, sf::Color(99, 82, 199));
    titleEnt.addGroup(GUI_TOP);
    titleEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.07;
    titleEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.07;

    auto &bgHeaderSub = _mgr.addEntity("bgHeaderSub");
    auto &bgHeaderSubComp =
        bgHeaderSub.addComponent<SubPanelComp>(_mgr.mainWindow.getSize().x / 3,
            _mgr.mainWindow.getSize().y,
            sf::Color(69, 36, 138, 150));
    bgHeaderSub.addGroup(GUI);

    auto &btnPlayEnt = _mgr.addEntity("playBtn");
    auto &btnPlayComp = btnPlayEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::playBtnLabel), [&btnPlayEnt]() {
            btnPlayEnt._mgr.LoadScene<ConnectScene>();
            }, btnPlayEnt.assets()->click, sf::Vector2u{240, 55}
        );
    btnPlayEnt.addGroup(GUI);
    btnPlayEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.3;
    btnPlayEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.08;

    auto &btnScoresEnt = _mgr.addEntity("scoresBtn");
    auto &btnScoresComp = btnScoresEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::highscoresLabel), [&btnScoresEnt]() {
            btnScoresEnt._mgr.LoadScene<ScoresScene>();
        }, btnScoresEnt.assets()->click,
        sf::Vector2u{240, 55});
    btnScoresEnt.addGroup(GUI);
    btnScoresEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.42;
    btnScoresEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.08;

    auto &btnOptionsEnt = _mgr.addEntity("optionsBtn");
    auto &btnOptionsComp = btnOptionsEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::optionsBtnLabel), [&btnOptionsEnt]() {
            btnOptionsEnt._mgr.LoadScene<OptionsScene>();
        }, btnOptionsEnt.assets()->click,
        sf::Vector2u{240, 55});
    btnOptionsEnt.addGroup(GUI);
    btnOptionsEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.54;
    btnOptionsEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.08;

    auto &btnLeaveEnt = _mgr.addEntity("leaveBtn");
    auto &btnLeaveComp = btnLeaveEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::leaveBtnLabel), [&btnLeaveEnt]() {
            btnLeaveEnt._mgr.setSceneAlive(false);
        }, btnLeaveEnt.assets()->click,
        sf::Vector2u{240, 55});
    btnLeaveEnt.addGroup(GUI);
    btnLeaveEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.8;
    btnLeaveEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.08;
}
