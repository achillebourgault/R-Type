/*
** EPITECH PROJECT, 2024
** AssetLoader.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef ASSETLOADER_HPP
#define ASSETLOADER_HPP

#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetLoader : public Component {
public:
    AssetLoader();
    void init() override;
    sf::Image PlayerSpriteSheet;
    sf::Texture BluePlayerTexture; //1
    sf::Texture RedPlayerTexture; //4
    sf::Texture YellowPlayerTexture; //2
    sf::Texture GreenPlayerTexture; //3
    sf::Texture MenuASprite;
    sf::Texture MenuBSprite;
    sf::Texture MenuCSprite;
    sf::Texture MenuAsteroid;
    sf::Texture MenuPlanetB;
    sf::Texture MenuPlanetC;
    sf::Texture MenuPlanetD;
    sf::Image PlayerParticlesProjectiles;
    sf::Texture PlayerProjectileBasic;
    sf::Texture PlayerProjectileForce1;
    sf::Texture PlayerProjectileForce2;
    sf::Texture PlayerProjectileForce3;
    sf::Texture PlayerProjectileForce4;
    sf::Texture PlayerProjectileForce5;
    sf::SoundBuffer bufferMainMusic;
    sf::Sound mainMusic;
    sf::SoundBuffer bufferClick;
    sf::SoundBuffer bufferShoot;
    sf::SoundBuffer bufferExplosion;
    sf::Sound click;
    sf::Sound shoot;
    sf::Sound explosion;
    sf::Texture Monster1Sprite; //sheet 5
    sf::Texture MonsterProjSprite; // sheet 43
    sf::Image ExplosionSheet;
    sf::Texture Explosion;
    void LoadPlayerTextures();
    void LoadPlayerProjectiles();
    sf::Texture &getPlayerTexture(int playerIndex);
    void LoadParallax();
    void LoadSounds();
    void LoadMonsterSprites();
};

#endif //ASSETLOADER_HPP
