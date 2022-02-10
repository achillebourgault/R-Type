/*
** EPITECH PROJECT, 2024
** Manager.cpp
** File description:
** Created by Leo Fabre
*/
#include <memory>
#include <iostream>
#include <utility>
#include <Client.hpp>
#include "ECS/Manager.hpp"
#include "ECS/Entity.hpp"
#include <AssetLoader.hpp>

Manager::Manager(
    sf::RenderWindow &mainWindow, Client *client,
    std::function<void()> SceneLoop
)
    : mainWindow(mainWindow),
      trad(),
      _client(*client),
      SceneLoop(std::move(SceneLoop))
{
    _onRefresh = [this]() {this->draw();};
    auto &logic = addEntity("AssetLoader");
    logic.addComponent<AssetLoader>();
}

void Manager::processInputs()
{
    inputs = PlayerInputs();
    sf::Event event;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        inputs.shootDown = true;
    }
    while (mainWindow.pollEvent(event)) {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            std::cout << "Closing window" << std::endl;
            setSceneAlive(false);
            mainWindow.close();
        }
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128)
                inputs.textInput += static_cast<char>(event.text.unicode);
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter)
                inputs.enterPressed = true;
            else if (event.key.code == sf::Keyboard::Space)
                inputs.shootPressed = true;
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Space) {
                inputs.shootReleased = true;
            } else if (event.key.code == sf::Keyboard::Enter) {
                inputs.enterReleased = true;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left)
                inputs.clickedPressed = true;
        }
        inputs.upKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        inputs.downKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        inputs.leftKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        inputs.rightKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    }
}

void Manager::update(double t, double dt, Manager::PlayerInputs inputs)
{
    for (int i = 0; i < entities.size(); i++) {
        if (!entities[i]) {
            std::cout << "UPDATING NULL ENT !!! Skipping... " << std::endl;
            continue;
        }
        entities[i]->update(t, dt, inputs);
    }
}

void Manager::draw()
{
    auto &bg(getEntitiesInGroup(Background));
    auto &floorEnts(getEntitiesInGroup(Floor));
    auto &walls(getEntitiesInGroup(Walls));
    auto &obstacles(getEntitiesInGroup(Obstacles));
    auto &monsters = (getEntitiesInGroup(Monsters));
    auto &powerups(getEntitiesInGroup(PowerUps));
    auto &players(getEntitiesInGroup(Players));
    auto &myProj(getEntitiesInGroup(MyProjectiles));
    auto &AlliesProj(getEntitiesInGroup(AlliesProjectiles));
    auto &EnemiesProj(getEntitiesInGroup(EnemiesProjectiles));
    auto &guiEnts(getEntitiesInGroup(GUI));
    auto &guiEnts2(getEntitiesInGroup(GUI_TOP));

    mainWindow.clear();
    for (const auto &ent: bg)
        if (ent->isActive()) ent->draw();
    for (auto &ent: floorEnts)
        if (ent->isActive()) ent->draw();
    for (auto &ent: walls)
        if (ent->isActive()) ent->draw();
    for (auto &ent: obstacles)
        if (ent->isActive()) ent->draw();
    for (auto &ent: monsters)
        if (ent->isActive()) ent->draw();
    for (auto &ent: powerups)
        if (ent->isActive()) ent->draw();
    for (auto &ent: players)
        if (ent->isActive()) ent->draw();
    for (auto &ent: myProj)
        if (ent->isActive()) ent->draw();
    for (auto &ent: AlliesProj)
        if (ent->isActive()) ent->draw();
    for (auto &ent: EnemiesProj)
        if (ent->isActive()) ent->draw();
    for (auto &ent: guiEnts)
        if (ent->isActive()) ent->draw();
    for (auto &ent: guiEnts2)
        if (ent->isActive()) ent->draw();

    mainWindow.display();
}

void Manager::refresh()
{
    for (auto i(0u); i < maxGroups; i++) {
        auto &v(groupedEntities[i]);
        v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity *entity) {
            bool shouldRemove =
                ((!entity->isActive() && !entity->GetDontDestroyOnLoad()) ||
                    !entity->hasGroup(i));
            /*if (shouldRemove)
                std::cout << "removing ent from group " << i << " : "
                    << entity->getName() << std::endl;*/
            return shouldRemove;
        }), std::end(v));
    }
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
        [](const std::shared_ptr<Entity> &entity) {
            bool shouldRemove =
                !entity->isActive() && !entity->GetDontDestroyOnLoad();
            /*if (shouldRemove)
                std::cout << "removing ent " << entity->getName() << std::endl;*/
            return shouldRemove;
        }), std::end(entities));
}

Entity &Manager::addEntity(std::string name)
{
    auto *e = new Entity(std::move(name), *this);
    std::shared_ptr<Entity> ptr{e};
    entities.emplace_back(std::move(ptr));
    return *e;
}

void Manager::destroyOnLoad()
{
    //set inactive all entities except dontDestroyOnLoad ones
    for (auto &item: entities) {
        if (!item->GetDontDestroyOnLoad())
            item->destroy();
    }
    //refresh to effectively destroy marked entities
    refresh();
}

bool Manager::isSceneAlive() const
{
    return curSceneAlive;
}

void Manager::addEntityToGroup(Entity *entity, Group group)
{
    groupedEntities[group].emplace_back(entity);
}

std::vector<Entity *> &Manager::getEntitiesInGroup(Group group)
{
    return groupedEntities[group];
}

void Manager::setSceneAlive(bool alive)
{
    Manager::curSceneAlive = alive;
}

std::shared_ptr<Entity> Manager::getEntByName(const std::string &name)
{
    for (auto a: entities) {
        if (a->getName() == name)
            return a;
    }
    return nullptr;
}

Traductions Manager::getTrad() const
{
    return trad;
}

void Manager::doLoadScene()
{
    if (!sceneToLoad) {
        std::cout << "doSceneLoad ERROR: scene nullptr !!!" << std::endl;
    }
    destroyOnLoad();
    sceneToLoad->load();
    delete sceneToLoad;
    sceneToLoad = nullptr;
    setSceneAlive(true);
    update(0, 0, PlayerInputs()); //Do a blank update just to set positions
    SceneLoop();
}
