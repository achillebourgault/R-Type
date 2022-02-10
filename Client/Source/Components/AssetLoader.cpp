/*
** EPITECH PROJECT, 2024
** AssetLoader.cpp
** File description:
** Created by Leo Fabre
*/

#include "AssetLoader.hpp"
#include <ECS/Entity.hpp>
#include <ECS/Manager.hpp>
#include <boost/filesystem.hpp>
#include <filesystem>

AssetLoader::AssetLoader()
{
    LoadPlayerTextures();
    LoadParallax();
    LoadPlayerProjectiles();
    LoadSounds();
    LoadMonsterSprites();
    Explosion.loadFromImage(PlayerParticlesProjectiles,
        sf::IntRect(266, 296, 195, 30));
}

void AssetLoader::LoadPlayerTextures()
{//This is broken on windows, try loading files from memory instead (ifstream)
    //https://en.sfml-dev.org/forums/index.php?topic=17256.msg124123#msg124123
    std::filesystem::path
        playerSpritePath("./Client/Assets/r-typesheet42.gif");
    std::cout << "playerSpritePath = ["<< absolute(playerSpritePath).string() << "]" << std::endl;
    if (!exists(playerSpritePath)) {
        std::cerr << "File does not exist" << std::endl;
    }
    PlayerSpriteSheet.loadFromFile(absolute(playerSpritePath).string());
    std::cout << "Loaded !" << std::endl;
    BluePlayerTexture.loadFromImage(PlayerSpriteSheet,
        sf::IntRect{0, 0, 166, 86 / 5});
    RedPlayerTexture.loadFromImage(PlayerSpriteSheet,
        sf::IntRect{0, (86 / 5) * 3, 166, 86 / 5});
    YellowPlayerTexture.loadFromImage(PlayerSpriteSheet,
        sf::IntRect{0, (86 / 5) * 1, 166, 86 / 5});
    GreenPlayerTexture.loadFromImage(PlayerSpriteSheet,
        sf::IntRect{0, (86 / 5) * 2, 166, 86 / 5});
}

void AssetLoader::LoadPlayerProjectiles()
{
    //Projectile vec : 215,85 102*12px

    PlayerParticlesProjectiles.loadFromFile("./Client/Assets/r-typesheet1.gif");
    PlayerProjectileBasic.loadFromImage(
        PlayerParticlesProjectiles,
        sf::IntRect{249, 87, 16, 10}
    );
    PlayerProjectileForce1.loadFromImage(
        PlayerParticlesProjectiles,
        sf::IntRect{249, 97, 16, 10}
    );
    PlayerProjectileForce2.loadFromImage(
        PlayerParticlesProjectiles,
        sf::IntRect{249, 107, 16, 10}
    );
    PlayerProjectileForce3.loadFromImage(
        PlayerParticlesProjectiles,
        sf::IntRect{233, 117, 32, 16}
    );
    PlayerProjectileForce4.loadFromImage(
        PlayerParticlesProjectiles,
        sf::IntRect{217, 133, 48, 16}
    );
    PlayerProjectileForce5.loadFromImage(
        PlayerParticlesProjectiles,
        sf::IntRect{201, 152, 64, 16}
    );
}

sf::Texture &AssetLoader::getPlayerTexture(int playerIndex)
{
    auto ent = entity->_mgr.getEntByName("AssetLoader");
    auto &assets = ent->getComponent<AssetLoader>();
    switch (playerIndex) {
    case 0:
        return assets.BluePlayerTexture;
    case 1:
        return assets.RedPlayerTexture;
    case 2:
        return assets.YellowPlayerTexture;
    case 3:
        return assets.GreenPlayerTexture;
    }
}

void AssetLoader::init()
{
    Component::init();
    entity->SetDontDestroyOnLoad(true);
}

void AssetLoader::LoadMonsterSprites()
{
    Monster1Sprite.loadFromFile("./Client/Assets/r-typesheet5.gif",
        sf::IntRect(0, 0, 266, 36));
    MonsterProjSprite.loadFromFile("./Client/Assets/r-typesheet43.gif",
        sf::IntRect(131, 0, 17 * 4, 17));
}

void AssetLoader::LoadParallax()
{
    MenuASprite.loadFromFile("./Client/Assets/Textures/GUI/stars01.png");
    MenuBSprite.loadFromFile("./Client/Assets/Textures/GUI/stars01.png");
    MenuCSprite.loadFromFile("./Client/Assets/Textures/GUI/planet01.png");

    MenuAsteroid.loadFromFile("./Client/Assets/Textures/GUI/asteroid.png");

    MenuPlanetB.loadFromFile("./Client/Assets/Textures/GUI/planet02.png");
    MenuPlanetC.loadFromFile("./Client/Assets/Textures/GUI/planet03.png");
    MenuPlanetD.loadFromFile("./Client/Assets/Textures/GUI/planet04.png");

}

//TODO: Fix MainMusic
void AssetLoader::LoadSounds()
{
    if (!bufferMainMusic.loadFromFile("./Client/Assets/8BEAT.wav")) {
        std::cout << "Error: file 8BEAT.wav not found." << std::endl;
        exit(0);
    }
    mainMusic.setBuffer(bufferMainMusic);
    if (!bufferClick.loadFromFile("./Client/Assets/click.wav")) {
        std::cout << "Error: file click.wav not found." << std::endl;
        exit(0);
    }
    click.setBuffer(bufferClick);
    if (!bufferShoot.loadFromFile("./Client/Assets/shoot.wav")) {
        std::cout << "Error: file shoot.wav not found." << std::endl;
        exit(0);
    }
    shoot.setBuffer(bufferShoot);
    if (!bufferExplosion.loadFromFile("./Client/Assets/explosion.wav")) {
        std::cout << "Error: file explosion.wav not found." << std::endl;
        exit(0);
    }
    explosion.setBuffer(bufferExplosion);
    explosion.setVolume(50);
    shoot.setVolume(20);
    click.setVolume(10);
}
