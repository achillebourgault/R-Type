/*
** EPITECH PROJECT, 2024
** AudioComp.cpp
** File description:
** Created by Achille Bourgault
*/

#include "Components/AudioComp.hpp"
#include <ECS/Manager.hpp>
#include <Mediator.hpp>
#include <Client.hpp>
#include "AssetLoader.hpp"
#include "TransformComp.hpp"

void AudioComp::init()
{
    Component::init();
    audioFile.setLoop(repeated);
    audioFile.play();

    entity->SetDontDestroyOnLoad(true);
}

void AudioComp::draw()
{
//    if (audioFile.getStatus() != sf::SoundSource::Playing) {
//        if (hasEverPlayed && !repeated)
//            return;
//        hasEverPlayed = true;
//        audioFile.play();
//    }
}

void AudioComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
}

AudioComp::AudioComp(sf::Sound audioFile, bool repeated) : audioFile(audioFile),
    repeated(repeated)
{
}
