/*
** EPITECH PROJECT, 2024
** OptionsScene.cpp
** File description:
** Created by Achille Bourgault
*/
#include "Scenes/OptionsScene.hpp"
#include <ECS/Manager.hpp>
#include <Components/GUI/TextComp.hpp>
#include <Components/GUI/TextButton.hpp>
#include <Components/GUI/SubPanelComp.hpp>
#include <Components/GUI/ListSelectorComp.hpp>
#include <Scenes/ScoresScene.hpp>
#include <Scenes/MenuScene.hpp>
#include <Scenes/ConnectScene.hpp>
#include <AssetLoader.hpp>

void OptionsScene::load()
{
    loadDefaults();
    loadSidebar();
    loadOptionFields();
    loadSoundFXOptions();
    loadMusicOptions();
}

void OptionsScene::loadOptionFields()
{
    auto &optionSection = _mgr.addEntity("optionSection");
    auto &optionSectionComp = optionSection.addComponent<SubPanelComp>(
        _mgr.mainWindow.getSize().x / 2, _mgr.mainWindow.getSize().y,
        sf::Color(69, 36, 138, 150));
    optionSection.addGroup(GUI);

    optionSection.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.2;
    optionSection.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.43;

    loadLanguageSelector();
}

void OptionsScene::loadLanguageSelector()
{
    _mgr.mainWindow.clear(sf::Color(18, 78, 176));
    auto &titleEnt = _mgr.addEntity("LanguageFieldLabel");
    auto &textComp = titleEnt.addComponent<TextComp>(
        _mgr.getTrad().get(Traductions::optionFieldLanguage).append(":"), 30);
    titleEnt.addGroup(GUI_TOP);
    textComp.centerHorizontally();
    titleEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.25;
    titleEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.47;

    auto &btnFieldLanguageFR = _mgr.addEntity("optionFieldFR");
    auto &btnFieldLanguageFRComp = btnFieldLanguageFR.addComponent<TextButton>(
        "FR", [&btnFieldLanguageFR]() {
            btnFieldLanguageFR._mgr.getTrad().setLanguage(1);
            btnFieldLanguageFR._mgr.refresh();
        }, btnFieldLanguageFR.assets()->click, sf::Vector2u{120, 35});
    btnFieldLanguageFR.addGroup(GUI);
    btnFieldLanguageFR.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.255;
    btnFieldLanguageFR.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.67;

    auto &btnFieldLanguageEN = _mgr.addEntity("optionFieldEN");
    auto &btnFieldLanguageENComp = btnFieldLanguageEN.addComponent<TextButton>(
        "EN", [&btnFieldLanguageEN]() {
            btnFieldLanguageEN._mgr.getTrad().setLanguage(0);
        }, btnFieldLanguageEN.assets()->click, sf::Vector2u{120, 35});
    btnFieldLanguageEN.addGroup(GUI);
    btnFieldLanguageEN.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.255;
    btnFieldLanguageEN.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.8;
}

void OptionsScene::loadSoundFXOptions()
{
    _mgr.mainWindow.clear(sf::Color(18, 78, 176));
    auto &titleEnt = _mgr.addEntity("sfxLabel");
    auto &textComp = titleEnt.addComponent<TextComp>(
        "Sound Effects:", 30);
    titleEnt.addGroup(GUI_TOP);
    textComp.centerHorizontally();
    titleEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.4;
    titleEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.47;

    auto &btnON = _mgr.addEntity("sfxON");
    auto &btnFieldLanguageFRComp = btnON.addComponent<TextButton>(
        "ON", [&btnON]() {
            btnON.assets()->click.setVolume(100);
            btnON.assets()->shoot.setVolume(100);
        }, btnON.assets()->click, sf::Vector2u{120, 35});
    btnON.addGroup(GUI);
    btnON.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.4;
    btnON.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.67;

    auto &btnOFF = _mgr.addEntity("sfxOFF");
    auto &btnFieldLanguageENComp = btnOFF.addComponent<TextButton>(
        "OFF", [&btnOFF]() {
            btnOFF.assets()->click.setVolume(0);
            btnOFF.assets()->shoot.setVolume(0);
        }, btnOFF.assets()->click, sf::Vector2u{120, 35});
    btnOFF.addGroup(GUI);
    btnOFF.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.4;
    btnOFF.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.8;
}

void OptionsScene::loadMusicOptions()
{
    _mgr.mainWindow.clear(sf::Color(18, 78, 176));
    auto &titleEnt = _mgr.addEntity("sfxLabel");
    auto &textComp = titleEnt.addComponent<TextComp>(
        "Music:", 30);
    titleEnt.addGroup(GUI_TOP);
    textComp.centerHorizontally();
    titleEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.54;
    titleEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.47;

    auto &btnON = _mgr.addEntity("sfxON");
    auto &btnFieldLanguageFRComp = btnON.addComponent<TextButton>(
        "ON", [&btnON]() {
            btnON.assets()->mainMusic.setVolume(100);
        }, btnON.assets()->click, sf::Vector2u{120, 35});
    btnON.addGroup(GUI);
    btnON.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.54;
    btnON.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.67;

    auto &btnOFF = _mgr.addEntity("sfxOFF");
    auto &btnFieldLanguageENComp = btnOFF.addComponent<TextButton>(
        "OFF", [&btnOFF]() {
            btnOFF.assets()->mainMusic.setVolume(0);
        }, btnOFF.assets()->click, sf::Vector2u{120, 35});
    btnOFF.addGroup(GUI);
    btnOFF.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.54;
    btnOFF.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.8;
}

void OptionsScene::loadDefaults()
{

    auto &titleEnt = _mgr.addEntity("OptionsTitle");
    auto &textComp = titleEnt.addComponent<TextComp>(
        _mgr.getTrad().get(Traductions::optionsBtnLabel), 50,
        sf::Color(18, 78, 176));
    titleEnt.addGroup(GUI_TOP);
    titleEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.05;
    titleEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.7;
}

void OptionsScene::loadSidebar()
{
    auto &titleEnt = _mgr.addEntity("gameTitle");
    auto &textComp =
        titleEnt.addComponent<TextComp>("R-Type", 75, sf::Color(99, 82, 199));
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
        btnPlayEnt._mgr.getTrad().get(Traductions::playBtnLabel),
        [&btnPlayEnt]() {
            btnPlayEnt._mgr.LoadScene<ConnectScene>();
        }, btnPlayEnt.assets()->click, sf::Vector2u{240, 55});
    btnPlayEnt.addGroup(GUI);
    btnPlayEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.3;
    btnPlayEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.08;

    auto &btnScoresEnt = _mgr.addEntity("scoresBtn");
    auto &btnScoreComp = btnScoresEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::highscoresLabel), [&btnScoresEnt]() {
            btnScoresEnt._mgr.LoadScene<ScoresScene>();
        }, btnScoresEnt.assets()->click, sf::Vector2u{240, 55});
    btnScoresEnt.addGroup(GUI);
    btnScoresEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.42;
    btnScoresEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.08;

    auto &btnOptionsEnt = _mgr.addEntity("optionsBtn");
    auto &btnOptionsComp = btnOptionsEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::optionsBtnLabel).append(" < "),
        [&btnOptionsEnt]() {
            btnOptionsEnt._mgr.LoadScene<MenuScene>();
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

void OptionsScene::updateEffectsVolume(int volume)
{
    AssetLoader *loader =
        &_mgr.getEntByName("AssetLoader")->getComponent<AssetLoader>();
    loader->click.setVolume(volume);
    loader->shoot.setVolume(volume);
}

void OptionsScene::updateMusicVolume(int volume)
{
    AssetLoader *loader =
        &_mgr.getEntByName("AssetLoader")->getComponent<AssetLoader>();
    loader->mainMusic.setVolume(volume);
}
