/*
** EPITECH PROJECT, 2024
** ConnectScene.cpp
** File description:
** Created by Achille Bourgault
*/
#include "Scenes/ConnectScene.hpp"
#include <ECS/Manager.hpp>
#include <Components/GUI/TextComp.hpp>
#include <Components/GUI/TextButton.hpp>
#include <Scenes/MenuScene.hpp>
#include <Components/GUI/SubPanelComp.hpp>
#include <Scenes/OptionsScene.hpp>
#include <GUI/InputTextComp.hpp>
#include <fstream>
#include <AssetLoader.hpp>

#include <Client.hpp>

void ConnectScene::load()
{
    std::cout << "ConnectScene : Loading Connect scene" << std::endl;

    loadServersList();
    loadRecentsServers();
}

std::vector<std::string> recentServersService()
{
    std::vector<std::string> res;
    std::ifstream data("./recent_servers.data");
    std::string tmpLine;

    if (!data.is_open()) {
        std::cout << "Data: No recent servers found." << std::endl;
    } else {
        while (getline(data, tmpLine)) {
            if (std::find(res.begin(), res.end(), tmpLine) != res.end() ||
                tmpLine == "\n" || tmpLine.length() > 22)
                continue;
            res.push_back(tmpLine);
        }
        data.close();
    }
    std::reverse(res.begin(),res.end());
    return res;
}

void ConnectScene::loadServersList()
{

    auto &optionSection = _mgr.addEntity("ConnectSection");
    auto &optionSectionComp = optionSection.addComponent<SubPanelComp>(
        _mgr.mainWindow.getSize().x / 2, _mgr.mainWindow.getSize().y,
        sf::Color(69, 36, 138, 150));
    optionSection.addGroup(GUI);

    optionSection.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * -0.2;
    optionSection.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.09;

    auto &titleEnt = _mgr.addEntity("ConnectTitle");

    auto &textComp = titleEnt.addComponent<TextComp>(
        _mgr.getTrad().get(Traductions::serversLabel), 50,
        sf::Color(18, 78, 176));
    titleEnt.addGroup(GUI_TOP);
    textComp.centerHorizontally();
    titleEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.85;
    titleEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.02;

    auto &btnBackEnt = _mgr.addEntity("backBtn");
    auto &btnBackComp = btnBackEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::backBtnLabel), [&btnBackEnt]() {
            btnBackEnt._mgr.LoadScene<MenuScene>();
        }, btnBackEnt.assets()->click,
        sf::Vector2u{240, 55});
    btnBackEnt.addGroup(GUI);
    btnBackEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.64;
    btnBackEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.12;

    auto &connectionLabelEnt = _mgr.addEntity("connectionLabel");
    auto &connectionLabelComp =
        connectionLabelEnt.addComponent<TextComp>("Server", 50,
            sf::Color(181, 181, 181));
    connectionLabelEnt.addGroup(GUI_TOP);

    connectionLabelEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.04;
    connectionLabelEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.12;

    auto &fieldLabelPlayernameEnt = _mgr.addEntity("fieldLabelPlayername");
    auto &fieldLabelPlayernameComp =
        fieldLabelPlayernameEnt.addComponent<TextComp>("Playername", 50,
            sf::Color(181, 181, 181));
    fieldLabelPlayernameEnt.addGroup(GUI_TOP);
    fieldLabelPlayernameEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.31;
    fieldLabelPlayernameEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.12;

    inputServerEnt = &_mgr.addEntity("inputServer");
    std::function<void()> onEnter = []() {return;};
    auto &inputServerComp =
        inputServerEnt->addComponent<InputTextComp>(onEnter, "127.0.0.1:7777");
    inputServerEnt->getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.18;
    inputServerEnt->getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.13;
    inputServerEnt->addGroup(GUI_TOP);

    std::vector<std::tuple<char, char>> filtersServer;
    filtersServer.push_back(std::make_tuple('0', '9'));
    filtersServer.push_back(std::make_tuple('.', '.'));
    filtersServer.push_back(std::make_tuple(':', ':'));
    inputServerComp.setFilters(filtersServer);

    auto &inputPlayerNameEnt = _mgr.addEntity("inputPlayerName");
    auto &inputPlayerNameComp =
        inputPlayerNameEnt.addComponent<InputTextComp>(onEnter, "");
    inputPlayerNameEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.45;
    inputPlayerNameEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.13;
    inputPlayerNameEnt.addGroup(GUI_TOP);

    std::vector<std::tuple<char, char>> filtersPlayerName;
    filtersPlayerName.push_back(std::make_tuple('a', 'z'));
    filtersPlayerName.push_back(std::make_tuple('A', 'Z'));
    filtersPlayerName.push_back(std::make_tuple('0', '9'));
    inputPlayerNameComp.setFilters(filtersPlayerName);

    auto &btnConnectEnt = _mgr.addEntity("connectBtn");
    std::function<void()>
        onClickedConnect = [&btnConnectEnt, &inputServerComp, &inputPlayerNameComp]() {

        std::vector<std::string> scores = recentServersService();

        if (scores.empty() || std::find(scores.begin(), scores.end(),
            inputServerComp.text.getString()) == scores.end()) {
            std::ofstream dataRecentServers;
            dataRecentServers.open("./recent_servers.data",
                std::ios_base::app);
            if (dataRecentServers.is_open()) {
                dataRecentServers
                    << std::string(inputServerComp.text.getString())
                    << "\n";
                dataRecentServers.close();
            }
        }
        btnConnectEnt._mgr._client.mediator.SetLocalPlayerName(
            inputPlayerNameComp.text.getString());
        btnConnectEnt._mgr._client.ConnectToServer(
            inputServerComp.text.getString(),
            inputPlayerNameComp.text.getString());
    };
    inputPlayerNameComp.onPressedEnter = onClickedConnect;
    auto &btnConnectComp = btnConnectEnt.addComponent<TextButton>(
        _mgr.trad.get(Traductions::playBtnLabel),
        onClickedConnect, btnConnectEnt.assets()->click,
        sf::Vector2u{240, 55});
    btnConnectEnt.addGroup(GUI);
    btnConnectEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.64;
    btnConnectEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.34;
}

void ConnectScene::loadRecentsServers()
{
    auto &optionSection = _mgr.addEntity("RecentsServersSection");
    auto &optionSectionComp = optionSection.addComponent<SubPanelComp>(
        _mgr.mainWindow.getSize().x / 3.2, _mgr.mainWindow.getSize().y,
        sf::Color(69, 36, 138, 150));
    optionSection.addGroup(GUI);

    optionSection.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * -0.2;
    optionSection.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.62;

    auto &titleEnt = _mgr.addEntity("RecentsTitle");
    auto &textComp = titleEnt.addComponent<TextComp>("Recents", 50,
        sf::Color(181, 181, 181));
    titleEnt.addGroup(GUI_TOP);
    textComp.centerHorizontally();
    titleEnt.getComponent<TransformComp>().position.y =
        _mgr.mainWindow.getSize().y * 0.04;
    titleEnt.getComponent<TransformComp>().position.x =
        _mgr.mainWindow.getSize().x * 0.65;

    std::vector<std::string> scores = recentServersService();
    std::vector<std::string> blacklist;

    if (scores.empty()) {
        auto &scoresNotFoundEnt = _mgr.addEntity("recentsServersNotFound");
        auto &scoresNotFoundComp = scoresNotFoundEnt.addComponent<TextComp>(
            _mgr.getTrad().get(Traductions::serversNotFound), 22,
            sf::Color(181, 181, 181));
        scoresNotFoundEnt.addGroup(GUI_TOP);
        scoresNotFoundEnt.getComponent<TransformComp>().position.y =
            _mgr.mainWindow.getSize().y * 0.18;
        scoresNotFoundEnt.getComponent<TransformComp>().position.x =
            _mgr.mainWindow.getSize().x * 0.65;
    } else {
        int id = 0;
        for (std::string e: scores) {
            if (id == 5)
                break;
            if (e.empty() || e == "\n" || e.length() < 5 || std::count(blacklist.begin(), blacklist.end(), e))
                continue;
            blacklist.push_back(e);
            auto &recentServerEnt =
                _mgr.addEntity("recentServer" + std::to_string(id));
            auto &recentServerComp = recentServerEnt.addComponent<TextButton>(
                e, []() {}, recentServerEnt.assets()->click,
                sf::Vector2u{280, 55});
            recentServerComp.set_on_click([&recentServerEnt, this]() {
//                std::string test = inputServerEnt->getComponent<InputTextComp>().text.getString();
//                std::cout << "Input server default: " << test << std::endl;
//                inputServerEnt->getComponent<InputTextComp>().text.setString(recentServerEnt.getComponent<TextButton>().text.getString());
            });
            recentServerEnt.addGroup(GUI_TOP);
            recentServerEnt.getComponent<TransformComp>().position.y =
                _mgr.mainWindow.getSize().y * (0.18 + (id * 0.12));
            recentServerEnt.getComponent<TransformComp>().position.x =
                _mgr.mainWindow.getSize().x * 0.66;
            id++;
        }
    }
}
