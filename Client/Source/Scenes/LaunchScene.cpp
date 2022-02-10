/*
** EPITECH PROJECT, 2024
** LaunchScene.cpp
** File description:
** Created by Achille Bourgault
*/
#include "Scenes/LaunchScene.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/ScoresScene.hpp"
#include "Scenes/OptionsScene.hpp"
#include <ECS/Entity.hpp>
#include <ECS/Manager.hpp>
#include <AssetLoader.hpp>
#include <Components/GUI/TextComp.hpp>
#include <Components/GUI/TextButton.hpp>
#include <BackgroundComponent.hpp>
#include <Components/GUI/SubPanelComp.hpp>
#include <Scenes/ConnectScene.hpp>
#include <AudioComp.hpp>
#include <cmath>
#include <thread>
#include <GUI/AnimatedComp.hpp>

#define PI 3.14

void LaunchScene::load()
{
    loadPressToPlay();

    auto &musicEnt = _mgr.addEntity("mainMusic");
    auto &musicComp = musicEnt.addComponent<AudioComp>(musicEnt.assets()->mainMusic, true);
    musicEnt.addGroup(Background);
    musicComp.audioFile.setVolume(10);
    musicEnt.SetDontDestroyOnLoad(true);
}

void LaunchScene::loadPressToPlay()
{
    float logoSize = 95;
    auto &titleEnt = _mgr.addEntity("gameTitle");
    auto &textComp = titleEnt.addComponent<TextComp>("R-Type", logoSize, sf::Color(99, 82, 199));
    titleEnt.addGroup(GUI_TOP);


    titleEnt.getComponent<TransformComp>().position.x =
        (_mgr.mainWindow.getSize().x / 2) - (logoSize * 1.5);
    titleEnt.getComponent<TransformComp>().position.y =
        (_mgr.mainWindow.getSize().y) * 0.2;

    auto &PressToPlayEnt = _mgr.addEntity("PressToPlay");
    auto &PressToPlayComp = PressToPlayEnt.addComponent<TextComp>("PRESS SPACE TO PLAY", 55, sf::Color(232, 232, 232));
    PressToPlayEnt.addGroup(GUI_TOP);

    auto &animatedLogo = _mgr.addEntity("logo");
    auto &animatedLogoComp = animatedLogo.addComponent<AnimatedComp>(&PressToPlayComp);
    animatedLogo.addGroup(GUI_TOP);

    PressToPlayEnt.getComponent<TransformComp>().position.x =
        (_mgr.mainWindow.getSize().x / 2) - (PressToPlayComp.text.getLocalBounds().width / 2);
    PressToPlayEnt.getComponent<TransformComp>().position.y =
        (_mgr.mainWindow.getSize().y) * 0.65;

    auto &bgParralax = _mgr.addEntity("bgParralax");
    auto &bgParralaxComp = bgParralax.addComponent<BackgroundComponent>();
    bgParralax.addGroup(GUI);
    bgParralax.SetDontDestroyOnLoad(true);
}
