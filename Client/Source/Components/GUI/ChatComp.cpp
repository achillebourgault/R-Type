/*
** EPITECH PROJECT, 2024
** ChatComp.cpp
** File description:
** Created by Leo Fabre
*/

#include <GUI/TextButton.hpp>
#include "Components/GUI/ChatComp.hpp"
#include "TransformComp.hpp"
#include <AssetLoader.hpp>

void ChatComp::init()
{
    Component::init();

    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    } else {
        transform = &entity->getComponent<TransformComp>();
    }

    auto &subInputPanEnt = entity->_mgr.addEntity("subInputPan");
    inputPan = &subInputPanEnt.addComponent<SubPanelComp>(_width, 70, sf::Color(39, 20, 79));
    subInputPanEnt.getComponent<TransformComp>().position = transform->position;
    subInputPanEnt.getComponent<TransformComp>().position.x = entity->_mgr.mainWindow.getSize().x - (_width) + 5;
    subInputPanEnt.getComponent<TransformComp>().position.y = 0;
    subInputPanEnt.addGroup(GUI);

//    auto &subReadyPanEnt = entity->_mgr.addEntity("subReadyPan");
//    readyPan = &subReadyPanEnt.addComponent<SubPanelComp>(_width, 70, sf::Color(227, 227, 227));
//    subReadyPanEnt.getComponent<TransformComp>().position = transform->position;
//    subReadyPanEnt.getComponent<TransformComp>().position.x = entity->_mgr.mainWindow.getSize().x - (_width);
//    subReadyPanEnt.getComponent<TransformComp>().position.y = 0;
//    subReadyPanEnt.addGroup(GUI);


    auto &chatPanEnt = entity->_mgr.addEntity("chatPan");
    chatPanEnt.addGroup(GUI);

    chatPan = &chatPanEnt.addComponent<SubPanelComp>(_width, _height, _bgColor);
    chatPanEnt.getComponent<TransformComp>().position = transform->position;
    chatPanEnt.getComponent<TransformComp>().position.x = 405;

    auto &labelChatEnt = entity->_mgr.addEntity("labelChat");
    labelChat = &labelChatEnt.addComponent<TextComp>("CHAT", 45);
    labelChatEnt.getComponent<TransformComp>().position = transform->position;
    labelChatEnt.getComponent<TransformComp>().position.x = 425;
    labelChatEnt.getComponent<TransformComp>().position.y = 5;
    labelChatEnt.addGroup(GUI_TOP);

    std::vector<std::tuple<char, char>> filtersServer;
    filtersServer.push_back(std::make_tuple('0', '9'));
    filtersServer.push_back(std::make_tuple('.', '.'));

    std::function<void()> onEnter = []() {return;};
    auto &inputPlayerNameEnt = entity->_mgr.addEntity("inputChat");
    inputChat = &inputPlayerNameEnt.addComponent<InputTextComp>(
        onEnter, "", sf::Color::Black, sf::Color::White, 30, _width - 175, 85);
    inputPlayerNameEnt.getComponent<TransformComp>().position.y =
        entity->_mgr.mainWindow.getSize().y * 0.82;
    inputPlayerNameEnt.getComponent<TransformComp>().position.x =
        entity->_mgr.mainWindow.getSize().x * 0.37;
    inputPlayerNameEnt.addGroup(GUI);

    auto &sendButtonEnt = entity->_mgr.addEntity("sendButton");
    sendBtn = &sendButtonEnt.addComponent<TextButton>(
        "^", [&sendButtonEnt]() {

        }, sendButtonEnt.assets()->click, sf::Vector2u{85, 85});
    sendButtonEnt.addGroup(GUI);
    sendButtonEnt.getComponent<TransformComp>().position.y =
        entity->_mgr.mainWindow.getSize().y * 0.82;
    sendButtonEnt.getComponent<TransformComp>().position.x =
        entity->_mgr.mainWindow.getSize().x * 0.9;
}

ChatComp::ChatComp(int width, int height, sf::Color color)
    : _width(width), _height(height), _bgColor(color), shape()
{
    shape.setFillColor(color);
    shape.setSize(sf::Vector2f{(float) width, (float) height});
    //    font.loadFromFile("./Client/Assets/Cinzel-Regular.ttf");
    //    text = sf::Text(str, font, size);
}

void ChatComp::draw()
{
    //    entity->_mgr.mainWindow.draw(text);
    entity->_mgr.mainWindow.draw(shape);
    inputPan->draw();
    readyPan->draw();
    inputChat->draw();
    sendBtn->draw();
    labelChat->draw();
}

void ChatComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    //    text.setPosition(entity->getComponent<TransformComp>().spawnPos);
    shape.setPosition(entity->getComponent<TransformComp>().position);
}
