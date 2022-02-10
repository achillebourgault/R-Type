/*
** EPITECH PROJECT, 2024
** TextButton.cpp
** File description:
** Created by Leo Fabre
*/

#include "Components/GUI/TextButton.hpp"

TextButton::TextButton(
    std::string str, std::function<void()> onClicked, sf::Sound action,
    sf::Vector2u size
)
    : size(size), onClick(onClicked), isLeftBtnDown(false), isLeftBtnReleased(false), click(action)
{
    font.loadFromFile("./Client/Assets/Cinzel-Regular.ttf");
    text = sf::Text(str, font, 30);
    text.setFillColor(sf::Color::Black);
}

void TextButton::init()
{
    Component::init();
    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    }

    if (size == sf::Vector2u{0, 0}) {
        auto textBounds = text.getLocalBounds();
        btnRect.setSize(
            sf::Vector2f(textBounds.width * 1.25f, textBounds.height * 2.f));
    } else
        btnRect.setSize({(float)size.x, (float)size.y});

    btnRect.setFillColor(sf::Color(99, 82, 199));
}

void TextButton::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    if (!entity->_mgr.mainWindow.hasFocus()) {return;}
    updateMouseBtnState();
    updatePositions();
    if (isHovering()) {
        setState(hovering);
        if (isClicked()) {
            click.play();
            setState(clicked);
            while(click.getStatus() != sf::SoundSource::Stopped);
            onClick();
        }
    } else {
        setState(idle);
    }
    isLeftBtnReleased = false;
}

void TextButton::updatePositions()
{
    auto btnPos = transform->position;
    auto textBounds = text.getGlobalBounds();
    auto textPos = sf::Vector2f(
        btnPos.x + (btnRect.getSize().x - textBounds.width) / 2,
        btnPos.y + (btnRect.getSize().y - (textBounds.height * 2)) / 2
    );
    btnRect.setPosition(btnPos);
    text.setPosition(textPos);
}

void TextButton::draw()
{
    Component::draw();
    entity->_mgr.mainWindow.draw(btnRect);
    entity->_mgr.mainWindow.draw(text);
}

bool TextButton::isHovering()
{
    sf::Vector2i
        mousePos = sf::Mouse::getPosition(entity->_mgr.mainWindow);

    return mousePos.x >=
        btnRect.getPosition().x
        && mousePos.x <=
        btnRect.getPosition().x + btnRect.getGlobalBounds().width
        && mousePos.y >=
        btnRect.getPosition().y
        && mousePos.y <=
        btnRect.getPosition().y + btnRect.getGlobalBounds().height;
}

void TextButton::CenterHorizontally()
{
    auto btnWidth = btnRect.getSize().x;
    auto screenWidth = (float) entity->_mgr.mainWindow.getSize().x;
    transform->position.x = (screenWidth / 2) - (btnWidth / 2);
}

bool TextButton::isClicked()
{
    return isHovering() && isLeftBtnDown;
}

void TextButton::updateMouseBtnState()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        isLeftBtnDown = true;
    }
    if (isLeftBtnDown &&
        !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        isLeftBtnDown = false;
        isLeftBtnReleased = true;
    }
}


void TextButton::setState(TextButton::BtnState state)
{
    switch (state) {
    case idle:
        btnRect.setFillColor(sf::Color::White);
        break;
    case hovering:
        btnRect.setFillColor(sf::Color(212, 212, 212));
        break;
    case clicked:
        btnRect.setFillColor(sf::Color(99, 82, 199));
        break;
    }
}

std::function<void()> const &TextButton::get_on_click() const
{
    return onClick;
}

void TextButton::set_on_click(std::function<void()> const &on_click)
{
    onClick = on_click;
}
