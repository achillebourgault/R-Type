/*
** EPITECH PROJECT, 2024
** OptionsScene.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef OptionsScene_HPP
#define OptionsScene_HPP

#include <ECS/Scene.hpp>
#include <string>

class OptionsScene : public Scene {
public:
    void load() override;
    explicit OptionsScene(Manager &mgr) : _mgr(mgr) {}
private:
    Manager &_mgr;
    void loadDefaults();
    void loadOptionFields();
    void loadSidebar();
    void updateEffectsVolume(int volume);
    void updateMusicVolume(int volume);
    void loadLanguageSelector();
    void loadSoundFXOptions();
    void loadMusicOptions();
};

#endif //OptionsScene_HPP
