/*
** EPITECH PROJECT, 2024
** ScoresScene.cpp
** File description:
** Created by Achille Bourgault
*/
#include "Scenes/ScoresScene.hpp"
#include "Scenes/GameScene.hpp"
#include <ECS/Entity.hpp>
#include <ECS/Manager.hpp>
#include <Components/GUI/TextComp.hpp>
#include <Components/GUI/TextButton.hpp>
#include <Scenes/MenuScene.hpp>
#include <Components/GUI/SubPanelComp.hpp>
#include <Scenes/OptionsScene.hpp>
#include <Scenes/ConnectScene.hpp>
#include <BackgroundComponent.hpp>
#include <AssetLoader.hpp>

void ScoresScene::load()
{
    std::cout << "ScoresScene : Loading Scores scene" << std::endl;

    loadDefaultsScores();
    loadSidebarScores();
    loadOptionFields();
}

void ScoresScene::loadOptionFields()
{
    auto &optionSection = _mgr.addEntity("optionSection");
    auto &optionSectionComp = optionSection.addComponent<SubPanelComp>(_mgr.mainWindow.getSize().x / 2, _mgr.mainWindow.getSize().y, sf::Color(69, 36, 138, 150));
    optionSection.addGroup(GUI);

    optionSection.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * -0.2;
    optionSection.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.43;
}

std::vector<std::string> ScoresScene::scoreService()
{
    std::vector<std::string> res;

    res.push_back("0");
    return res;
}

void ScoresScene::loadDefaultsScores()
{

    auto &titleEnt = _mgr.addEntity("OptionsTitle");
    auto &textComp = titleEnt.addComponent<TextComp>(_mgr.getTrad().get(Traductions::highscoresLabel), 50, sf::Color(18, 78, 176));
    titleEnt.addGroup(GUI_TOP);
    textComp.centerHorizontally();
    titleEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.85;
    titleEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.7;

    std::vector<std::string> scores = scoreService();

    if (scores.size() == 1 && scores.at(0) == "0") {
        auto &scoresNotFoundEnt = _mgr.addEntity("scoresNotFound");
        auto &scoresNotFoundComp = scoresNotFoundEnt.addComponent<TextComp>(_mgr.getTrad().get(Traductions::scoresNotFound), 32, sf::Color(181, 181, 181));
        scoresNotFoundEnt.addGroup(GUI_TOP);
        scoresNotFoundEnt.getComponent<TransformComp>().position.y =
            _mgr.mainWindow.getSize().y * 0.1;
        scoresNotFoundEnt.getComponent<TransformComp>().position.x =
            _mgr.mainWindow.getSize().x * 0.48;
    }
}

void ScoresScene::loadSidebarScores()
{
    auto &titleEnt = _mgr.addEntity("gameTitle");
    auto &textComp = titleEnt.addComponent<TextComp>("R-Type", 75, sf::Color(99, 82, 199));
    titleEnt.addGroup(GUI_TOP);
    titleEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.07;
    titleEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.07;

    //    auto &bgParrallax = _mgr.addEntity("bgParralax");
    //    auto &bgParrallaxComp = bgParrallax.addComponent<BackgroundComponent>();
    //    bgParrallax.addGroup(Background);

    auto &bgHeaderSub = _mgr.addEntity("bgHeaderSub");
    auto &bgHeaderSubComp = bgHeaderSub.addComponent<SubPanelComp>(_mgr.mainWindow.getSize().x / 3, _mgr.mainWindow.getSize().y,
        sf::Color(69, 36, 138, 150));
    bgHeaderSub.addGroup(GUI);


    auto &btnPlayEnt = _mgr.addEntity("playBtn");
    auto &btnPlayComp = btnPlayEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::playBtnLabel), [&btnPlayEnt]() {
            btnPlayEnt._mgr.LoadScene<ConnectScene>();
        }, btnPlayEnt.assets()->click, sf::Vector2u{240, 55});
    btnPlayEnt.addGroup(GUI);
    btnPlayEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.3;
    btnPlayEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.08;

    auto &btnScoresEnt = _mgr.addEntity("scoresBtn");
    auto &btnScoresComp = btnScoresEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::highscoresLabel).append(" < "), [&btnScoresEnt]() {
            btnScoresEnt._mgr.LoadScene<MenuScene>();
        }, btnScoresEnt.assets()->click, sf::Vector2u{240, 55});
    btnScoresEnt.addGroup(GUI);
    btnScoresEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.42;
    btnScoresEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.08;

    auto &btnOptionsEnt = _mgr.addEntity("optionsBtn");
    auto &btnOptionsComp = btnOptionsEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::optionsBtnLabel), [&btnOptionsEnt]() {
            btnOptionsEnt._mgr.LoadScene<OptionsScene>();
        }, btnOptionsEnt.assets()->click, sf::Vector2u{240, 55});
    btnOptionsEnt.addGroup(GUI);
    btnOptionsEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.54;
    btnOptionsEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.08;

    auto &btnLeaveEnt = _mgr.addEntity("leaveBtn");
    auto &btnLeaveComp = btnLeaveEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::leaveBtnLabel), [&btnLeaveEnt]() {
            btnLeaveEnt._mgr.setSceneAlive(false);
        }, btnLeaveEnt.assets()->click, sf::Vector2u{240, 55});
    btnLeaveEnt.addGroup(GUI);
    btnLeaveEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.8;
    btnLeaveEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.08;
}
