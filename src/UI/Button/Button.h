#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
    private:
        sf::RectangleShape shape;
        sf::Text text;

    public:
        Button(sf::Vector2f position, sf::Vector2f size, sf::Font *font, std::string text, int fontSize);
        sf::RectangleShape getShape() const;
        bool isHovered(sf::RenderWindow &window) const;
        bool isClicked(sf::RenderWindow &window) const;
        void draw(sf::RenderWindow &window);
};

#endif // BUTTON_H