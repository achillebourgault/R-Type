/*
** EPITECH PROJECT, 2024
** TextButton.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef TEXTBUTTON_HPP
#define TEXTBUTTON_HPP
#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextComp.hpp"

class TextButton : public Component {
public:
    enum BtnState {idle, hovering, clicked};
    TextButton(
        std::string str, std::function<void()> onClicked, sf::Sound action,
        sf::Vector2u size = {0, 0}
    );
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    void draw() override;

    std::function<void()> const &get_on_click() const;
    void set_on_click(std::function<void()> const &on_click);

    void CenterHorizontally();

    sf::RectangleShape btnRect;

    sf::Text text;
    sf::Font font;
private:
    sf::Vector2u size;
    sf::Sound click;
    BtnState state;
    std::function<void()> onClick;
    TransformComp *transform;
    bool isHovering();
    bool isClicked();
    void updateMouseBtnState();
    bool isLeftBtnDown;
    bool isLeftBtnReleased;
    void updatePositions();
    void setState(BtnState state);
};

#endif //TEXTBUTTON_HPP
