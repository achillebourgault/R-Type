/*
** EPITECH PROJECT, 2024
** LobbyScene.cpp
** File description:
** Created by Leo Fabre
*/
#include "Scenes/LobbyScene.hpp"
#include "LobbyComp.hpp"
#include <ECS/Manager.hpp>
#include <GUI/TextButton.hpp>
#include <Scenes/GameScene.hpp>
#include <BackgroundComponent.hpp>
#include <GUI/ChatComp.hpp>
#include <Client.hpp>
#include <AssetLoader.hpp>

void LobbyScene::load()
{
    Scene::load();

    auto &PlayBtnEnt = _mgr.addEntity("ReadyBtn");
    std::function<void()> onClick = [&PlayBtnEnt](){
//        PlayBtnEnt._mgr.LoadScene<GameScene>();
        PlayBtnEnt._mgr._client.OnClickedReadyToPlay();
        PlayBtnEnt.destroy();
    };
    auto &PlayBtnComp = PlayBtnEnt.addComponent<TextButton>("Ready", onClick, PlayBtnEnt.assets()->click, sf::Vector2u{350,50});
    PlayBtnEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.85;
    PlayBtnEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.025;
    PlayBtnEnt.addGroup(GUI_TOP);

    auto &lobbyEnt = _mgr.addEntity("lobby");
    auto &lobbyComp = lobbyEnt.addComponent<LobbyComp>();
    lobbyEnt.addGroup(GUI);

    auto &ChatEnt = _mgr.addEntity("chat");
    auto &ChatSideComp = ChatEnt.addComponent<ChatComp>(_mgr.mainWindow.getSize().x - 400, _mgr.mainWindow.getSize().y, sf::Color(69, 36, 138, 150));
    lobbyEnt.addGroup(GUI_TOP);
}
