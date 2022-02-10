/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Created by Frédéric Lawecki--Walkowiak
*/

#include <TransformComp.hpp>
#include <Components/GUI/ListSelectorComp.hpp>
#include <ECS/Entity.hpp>
#include <ECS/Manager.hpp>

ListSelectorComp::ListSelectorComp(
    const std::vector<std::string> &options, std::function<void(const std::string)> onClicked
)
    : _options(options),
      _index(0),
      _isLeftBtnDown(false),
      _isLeftBtnReleased(false),
      onClick(onClicked)
{
    _font.loadFromFile("./Client/Assets/Cinzel-Regular.ttf");
    _value.setFont(_font);
    _value.setCharacterSize(30);
    _value.setFillColor(sf::Color::White);
    _prevText.setFont(_font);
    _prevText.setCharacterSize(30);
    _prevText.setFillColor(sf::Color::Black);
    _prevText.setString("<");
    _nextText.setFont(_font);
    _nextText.setCharacterSize(30);
    _nextText.setFillColor(sf::Color::Black);
    _nextText.setString(">");
    _value.setString(_options[_index]);
}

void ListSelectorComp::init()
{
    Component::init();
    if (!entity->hasComponent<TransformComp>()) {
        transform = &entity->addComponent<TransformComp>();
    }

    _prevBtnRect.setSize({50, 50});
    _prevBtnRect.setFillColor(sf::Color::White);
    _nextBtnRect.setSize({50, 50});
    _nextBtnRect.setFillColor(sf::Color::White);
}

void ListSelectorComp::update(double t, double dt, Manager::PlayerInputs inputs)
{
    Component::update(t, dt, inputs);
    updateMouseBtnState();

    if (isHoveringPrevBtn()) {
        setState(hoveringPrev);
        if (isClickedPrevBtn()) {
            setState(clickedPrev);
            if (_isLeftBtnReleased) {
                _index--;
                onClick(getOptions());
            }
            _isLeftBtnReleased = false;
        }
    } else if (isHoveringNextBtn()) {
        setState(hoveringNext);
        if (isClickedNextBtn()) {
            setState(clickedNext);
            if (_isLeftBtnReleased) {
                _index++;
                onClick(getOptions());
            }
            _isLeftBtnReleased = false;
        }
    } else {
        setState(idle);
    }

    if (_index < 0) {
        _index = _options.size() - 1;
    }
    else if (_index > _options.size() - 1) {
        _index = 0;
    }
    if (_value.getString() != _options[_index]) {
        _value.setString(_options[_index]);
    }
    updatePositions();
}

void ListSelectorComp::draw()
{
    Component::draw();
    entity->_mgr.mainWindow.draw(_prevBtnRect);
    entity->_mgr.mainWindow.draw(_nextBtnRect);
    entity->_mgr.mainWindow.draw(_prevText);
    entity->_mgr.mainWindow.draw(_nextText);
    entity->_mgr.mainWindow.draw(_value);
}

bool ListSelectorComp::isHoveringNextBtn() const
{
    sf::Vector2i
        mousePos = sf::Mouse::getPosition(entity->_mgr.mainWindow);

    return mousePos.x >=
        _nextBtnRect.getPosition().x
        && mousePos.x <=
        _nextBtnRect.getPosition().x + _nextBtnRect.getGlobalBounds().width
        && mousePos.y >=
        _nextBtnRect.getPosition().y
        && mousePos.y <=
        _nextBtnRect.getPosition().y + _nextBtnRect.getGlobalBounds().height;
}

bool ListSelectorComp::isHoveringPrevBtn() const
{
    sf::Vector2i
        mousePos = sf::Mouse::getPosition(entity->_mgr.mainWindow);

    return mousePos.x >=
        _prevBtnRect.getPosition().x
        && mousePos.x <=
        _prevBtnRect.getPosition().x + _prevBtnRect.getGlobalBounds().width
        && mousePos.y >=
        _prevBtnRect.getPosition().y
        && mousePos.y <=
        _prevBtnRect.getPosition().y + _prevBtnRect.getGlobalBounds().height;
}

void ListSelectorComp::updatePositions()
{
    auto _prevBtnPos = transform->position;
    auto _nextBtnPos = transform->position;
    auto _valuePos = transform->position;
    auto _prevTextBounds = _prevText.getGlobalBounds();
    auto _valueBounds = _value.getGlobalBounds();
    auto _prevTextPos = sf::Vector2f(
        _prevBtnPos.x + (_prevBtnRect.getSize().x - (_prevTextBounds.width * 2)) / 2,
        _prevBtnPos.y + (_prevBtnRect.getSize().y - (_prevTextBounds.height * 2)) / 4
    );
    auto _nextTextBounds = _nextText.getGlobalBounds();
    auto _nextTextPos = sf::Vector2f(
        (_nextBtnPos.x * 1.825) + (_nextBtnRect.getSize().x - (_nextTextBounds.width * 2)) / 2,
        _nextBtnPos.y + (_nextBtnRect.getSize().y - (_nextTextBounds.height * 2)) / 4
    );

    _prevBtnRect.setPosition(_prevBtnPos);
    _prevText.setPosition(_prevTextPos);
    _nextBtnPos.x = _nextBtnPos.x * 1.825;
    _nextBtnRect.setPosition(_nextBtnPos);
    _nextText.setPosition(_nextTextPos);
    _valuePos.x = (_prevBtnPos.x + (_nextBtnPos.x - _prevBtnPos.x) / 2) - (_valueBounds.width / 4);
    _value.setPosition(_valuePos);
}

void ListSelectorComp::updateMouseBtnState()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        _isLeftBtnDown = true;
    }
    if (_isLeftBtnDown &&
        !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        _isLeftBtnDown = false;
        _isLeftBtnReleased = true;
    }
}

std::string ListSelectorComp::getOptions() const
{
    return _options[_index];
}

bool ListSelectorComp::isClickedPrevBtn()
{
    return isHoveringPrevBtn() && _isLeftBtnDown;
}

bool ListSelectorComp::isClickedNextBtn()
{
    return isHoveringNextBtn() && _isLeftBtnDown;
}

void ListSelectorComp::setState(ListSelectorComp::BtnState state)
{
    switch (state) {
    case idle:
        _prevBtnRect.setFillColor(sf::Color::White);
        _nextBtnRect.setFillColor(sf::Color::White);
        break;
    case hoveringPrev:
        _prevBtnRect.setFillColor(sf::Color(212, 212, 212));
        break;
    case hoveringNext:
        _nextBtnRect.setFillColor(sf::Color(212, 212, 212));
        break;
    case clickedPrev:
        _prevBtnRect.setFillColor(sf::Color(99, 82, 199));
        break;
    case clickedNext:
        _nextBtnRect.setFillColor(sf::Color(99, 82, 199));
        break;
    }
}