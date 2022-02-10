/*
** EPITECH PROJECT, 2024
** ScoresScene.hpp
** File description:
** Created by Achille Bourgault
*/

#ifndef ScoresScene_HPP
#define ScoresScene_HPP

#include <ECS/Scene.hpp>
#include <vector>
#include <string>

class ScoresScene : public Scene {
public:
    void load() override;
    explicit ScoresScene(Manager &mgr) : _mgr(mgr) {}
private:
    Manager &_mgr;
    void loadDefaultsScores();
    void loadSidebarScores();
    void loadOptionFields();
    std::vector<std::string> scoreService();
};

#endif //OptionsScene_HPP
