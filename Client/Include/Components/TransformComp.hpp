/*
** EPITECH PROJECT, 2024
** TransformComp.hpp
** File description:
** Created by Leo Fabre
*/

#ifndef TRANSFORMCOMP_HPP
#define TRANSFORMCOMP_HPP
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

class TransformComp
    : public Component {
public:
    TransformComp();
    TransformComp(int x, int y);
    sf::Vector2f position;
};

#endif //TRANSFORMCOMP_HPP
