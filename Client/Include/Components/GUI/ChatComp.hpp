/*
** EPITECH PROJECT, 2024
** ChatComp.hpp
** File description:
** Created by Achille Bourgault
*/

#ifndef ChatComp_HPP
#define ChatComp_HPP
#include "SFML/Graphics.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Manager.hpp"
#include "TransformComp.hpp"
#include "SubPanelComp.hpp"
#include "InputTextComp.hpp"

class ChatComp : public Component {
public:
    explicit ChatComp(int width, int height, sf::Color color = sf::Color::White);
    void draw() override;
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;

private:
    sf::RectangleShape shape;
    SubPanelComp *chatPan;
    SubPanelComp *inputPan;
    SubPanelComp *readyPan;
    InputTextComp *inputChat;
    TransformComp *transform;
    TextButton *sendBtn;
    TextComp *labelChat;
    int _width;
    int _height;
    sf::Color _bgColor;
};

#endif //ChatComp_HPP
