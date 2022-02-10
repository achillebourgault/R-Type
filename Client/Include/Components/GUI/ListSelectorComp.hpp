/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Created by Frédéric Lawecki--Walkowiak
*/

#ifndef LISTSELECTORCOMP_HPP
#define LISTSELECTORCOMP_HPP

#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>

class ListSelectorComp : public Component {
public:
    enum BtnState {idle, hoveringPrev, hoveringNext, clickedPrev, clickedNext};
    ListSelectorComp(
        const std::vector<std::string> &options, std::function<void(const std::string)> onClicked
    );
    void init() override;
    void update(double t, double dt, Manager::PlayerInputs inputs) override;
    void draw() override;
    std::string getOptions() const;
private:
    std::vector<std::string> _options;
    std::function<void(const std::string)> onClick;
    TransformComp *transform;
    int _index;
    sf::Font _font;
    sf::Text _value;
    sf::RectangleShape _prevBtnRect;
    sf::RectangleShape _nextBtnRect;
    sf::Text _prevText;
    sf::Text _nextText;
    bool _isLeftBtnDown;
    bool _isLeftBtnReleased;
    void updatePositions();
    void updateMouseBtnState();
    bool isHoveringPrevBtn() const;
    bool isClickedPrevBtn();
    bool isHoveringNextBtn() const;
    bool isClickedNextBtn();
    void setState(BtnState state);
};

#endif //LISTSELECTORCOMP_HPP