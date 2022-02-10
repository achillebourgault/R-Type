/*
** EPITECH PROJECT, 2024
** GameScene.cpp
** File description:
** Created by Leo Fabre
*/

#include <Components/Player/PlayerComp.hpp>
#include <GUI/BackgroundComponent.hpp>
#include "Scenes/GameScene.hpp"
#include "AssetLoader.hpp"
#include "MonsterManager.hpp"
#include <Mediator.hpp>
#include <Client.hpp>
#include <Player/PlayerHUDComp.hpp>

void GameScene::load()
{
    int id = _mgr._client.mediator.getLocalPlayerId();

    for (int i = 0; i < _mgr._client.mediator.nb_connected; ++i) {
        std::cout << "Making player index = "<< i << ", local player id == " << id << std::endl;
        if (i == id) {
            std::cout << "Local player" << std::endl;
            auto &playerEnt = _mgr.addEntity("Player");
            playerEnt._mgr._client.mediator.PlayerEnts.emplace_back(&playerEnt);
            playerEnt.addGroup(Players);
            auto &playerComp =
                playerEnt.addComponent<PlayerComp>(playerEnt.getName(),
                    playerEnt.assets()->getPlayerTexture(i), true);
            playerEnt.getComponent<TransformComp>().position.y += i*50;
        } else {
            std::cout << "Proxy player" << std::endl;
            auto &playerEnt = _mgr.addEntity(
                "Player" + std::to_string(i));
            playerEnt._mgr._client.mediator.PlayerEnts.emplace_back(&playerEnt);
            playerEnt.addGroup(Players);
            auto &playerComp =
                playerEnt.addComponent<PlayerComp>(playerEnt.getName(),
                    playerEnt.assets()->getPlayerTexture(i), false);
            playerEnt.getComponent<TransformComp>().position.y += i*50;
        }
    }

    auto &forceBar = _mgr.addEntity("ForceBar");
    auto &forceBarComp = forceBar.addComponent<PlayerForceBar>();
    forceBar.addGroup(GUI);

    auto &hudLeft = _mgr.addEntity("hud");
    auto &hudLeftComp = hudLeft.addComponent<PlayerHUDComp>();
    hudLeft.addGroup(GUI_TOP);

    auto &MonsterMgr = _mgr.addEntity("monsterMgr");
    _mgr._client.mediator.monster_manager = &MonsterMgr.addComponent<MonsterManager>();

    _mgr._client.isInGame = true;
}
