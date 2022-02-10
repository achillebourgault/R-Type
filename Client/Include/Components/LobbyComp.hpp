/*
** EPITECH PROJECT, 2024
** LobbyComp.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef LOBBYCOMP_HPP
#define LOBBYCOMP_HPP

#include "ECS/Component.hpp"
#include "Components/GUI/SubPanelComp.hpp"
#include "Components/GUI/TextComp.hpp"

class LobbyComp : public Component {
public:
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    void draw() override;
    TextComp *player1;
    TextComp *player2;
    TextComp *player3;
    TextComp *player4;
    SubPanelComp *panPlayers;
    TextComp *labelPlayers;
private:
    TransformComp *transform;
};

#endif //LOBBYCOMP_HPP
