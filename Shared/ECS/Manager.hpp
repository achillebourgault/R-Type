/*
** EPITECH PROJECT, 2024
** Manager.hpp
** File description:
** Created by Leo Fabre
*/
#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <ECS/ECS.hpp>
#include <SFML/Graphics.hpp>
#include <Traductions.hpp>
#include <functional>
#include "Scene.hpp"

enum GroupLabel {
    Background,
    Floor,
    Walls,
    Obstacles,
    Monsters,
    Players,
    MyProjectiles,
    AlliesProjectiles,
    EnemiesProjectiles,
    GUI,
    GUI_TOP,
    PowerUps
};

class Entity;

class Client;

class Manager {
public:
    struct PlayerInputs {
        char textInput = 0;
        bool clickedPressed = false;
        bool clickedReleased = false;
        bool enterPressed = false;
        bool enterReleased = false;
        bool shootPressed = false;
        bool shootReleased = false;
        bool shootDown = false;
        bool upKeyDown = false;
        bool downKeyDown = false;
        bool leftKeyDown = false;
        bool rightKeyDown = false;
    } inputs;

    explicit Manager(
        sf::RenderWindow &mainWindow, Client *client,
        std::function<void()> SceneLoop
    );
    explicit Manager();
    void update(double t, double dt, Manager::PlayerInputs inputs);
    void draw();
    void refresh();
    std::function<void()> _onRefresh;
    Client &_client;

    //region Entity Management

public:
    Entity &addEntity(std::string name);
    void addEntityToGroup(Entity *entity, Group group);
    std::vector<Entity *> &getEntitiesInGroup(Group group);
    std::shared_ptr<Entity> getEntByName(const std::string &name);


private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::array<std::vector<Entity *>, maxGroups> groupedEntities;
    //endregion

    //region Scene Loading
public:
    std::function<void()> SceneLoop;
    Scene *sceneToLoad = nullptr;
    void doLoadScene();
    template<class SceneType>
    int LoadScene()
    {
        static_assert(std::is_base_of<Scene, SceneType>::value,
            "LoadScene: template class must derive from Scene class");
        sceneToLoad = new SceneType(*this);
        if (!isSceneAlive()) { //first time loading a scene
            doLoadScene();
        } else {
            setSceneAlive(false);
        }
        return 0;
    }

public:
    bool isSceneAlive() const;
    void setSceneAlive(bool alive);
    void destroyOnLoad();
private:
    bool curSceneAlive = false;
    size_t playernb = 0;
    //endregion

public:
    sf::RenderWindow &mainWindow;
    Traductions trad;
    Traductions getTrad() const;
    void processInputs();
};

#endif //MANAGER_HPP