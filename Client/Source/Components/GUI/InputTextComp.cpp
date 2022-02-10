/*
** EPITECH PROJECT, 2024
** InputTextComp.cpp
** File description:
** Created by Achille Bourgault
*/

#include "Components/GUI/InputTextComp.hpp"
#include "TransformComp.hpp"

InputTextComp::InputTextComp(
    std::function<void()> &onEnterPressed,
    std::string defaultPlaceholder,
    sf::Color textColor,
    sf::Color backgroundColor,
    int textSize, int width, int height
)
    : background(),
      text(),
      font(),
      onPressedEnter(onEnterPressed),
      placeholder(defaultPlaceholder),
      hasFocus(false)
{
    background.setSize({(float) width, (float) height});
    background.setFillColor(backgroundColor);
    font.loadFromFile("./Client/Assets/Cinzel-Regular.ttf");
    playerInput = defaultPlaceholder;
    text = sf::Text(defaultPlaceholder, font, textSize);
    text.setFillColor(textColor);

}

void InputTextComp::draw()
{
    entity->_mgr.mainWindow.draw(background);
    entity->_mgr.mainWindow.draw(text);
}

void InputTextComp::init()
{
    Component::init();

    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    }
}

void InputTextComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(0, 0, inputs);
    if (!entity->_mgr.mainWindow.hasFocus()) {return;}

//    if (hasFocus) {
//        playerInput = text.getString() == placeholder ? "" : playerInput;
//    }
    sf::Vector2f textPos = {(float)entity->getComponent<TransformComp>().position.x + 10,
        (float)entity->getComponent<TransformComp>().position.y + (background.getSize().y / 8)};
    text.setPosition(textPos);
    background.setPosition(transform->position);
    UpdateFocus();
    if (!hasFocus) return;
    if (inputs.enterReleased && onPressedEnter)
        onPressedEnter();
    switch (inputs.textInput) {
    case 0:
        break;
    case 8:
        if (!playerInput.empty()) {
            playerInput.pop_back();
        }
        break;
    case '\n':
        break;
    case ' ':
        break;
    default:
        for (std::tuple<char, char> filter : _filters) {
            if (inputs.textInput >= std::get<0>(filter) &&
                inputs.textInput <= std::get<1>(filter)) {
                playerInput += inputs.textInput;
                break;
            }
        }
        if (_filters.empty())
            playerInput += inputs.textInput;
    }
    text.setString(playerInput);
    text.setPosition(entity->getComponent<TransformComp>().position);
}

void InputTextComp::UpdateFocus()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (isHovering()) {
            hasFocus = true;
        } else {
            hasFocus = false;
        }
    }
}

bool InputTextComp::isHovering()
{
    sf::Vector2i
        mousePos = sf::Mouse::getPosition(entity->_mgr.mainWindow);

    return mousePos.x >=
        background.getPosition().x
        && mousePos.x <=
        background.getPosition().x + background.getGlobalBounds().width
        && mousePos.y >=
        background.getPosition().y
        && mousePos.y <=
        background.getPosition().y + background.getGlobalBounds().height;
}

void InputTextComp::centerHorizontally()
{
    auto txtWidth = background.getSize().x;
    auto screenWidth = entity->_mgr.mainWindow.getSize().x;
    transform->position.x = (screenWidth / 2) - (txtWidth / 2);
}

void InputTextComp::updateText(char const *newText)
{
    text.setString(newText);
}

void InputTextComp::setFilters(std::vector<std::tuple<char, char>> filters)
{
    _filters = filters;
}
