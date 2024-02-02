#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
    private:
        sf::RectangleShape shape;
        sf::Text text;

    public:
        Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Font *font, std::string text, int fontSize);
        void draw(sf::RenderWindow &window);
        sf::RectangleShape getShape() const;
};

#endif // BUTTON_H