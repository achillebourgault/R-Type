/*
** EPITECH PROJECT, 2024
** InputTextComp.hpp
** File description:
** Created by Achille Bourgault
*/

#ifndef InputTextComp_HPP
#define InputTextComp_HPP

#include "SFML/Graphics.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Manager.hpp"
#include "TransformComp.hpp"

class InputTextComp : public Component {
public:
    explicit InputTextComp(
        std::function<void()> &onEnterPressed,
        std::string defaultPlaceholder = "",
        sf::Color textColor = sf::Color::Black,
        sf::Color backgroundColor = sf::Color::White,
        int textSize = 30, int width = 470, int height = 50);
    void draw() override;
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs);
    void centerHorizontally();
    void updateText(char const *newText);

    void setFilters(std::vector<std::tuple<char, char>> filters);
    sf::Text text;
    sf::Font font;
    sf::Color color;
    sf::RectangleShape background;
    std::vector<std::tuple<char, char>> _filters;
    bool hasFocus = false;
    std::string placeholder;
    std::function<void()> onPressedEnter;
private:
    TransformComp *transform;
    std::string playerInput;
    bool isHovering();
    void UpdateFocus();
};

#endif //InputTextComp_HPP
