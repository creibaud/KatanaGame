#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font *font, std::string text, int fontSize) {
    this->shape.setSize(size);
    this->shape.setPosition(position);

    this->text.setFont(*font);
    this->text.setString(text);
    this->text.setCharacterSize(fontSize);
    this->text.setPosition(position.x + size.x / 2 - this->text.getGlobalBounds().width / 2, position.y + size.y / 2 - this->text.getGlobalBounds().height / 2 - 3);
}

void Button::draw(sf::RenderWindow &window, sf::Color color) {
    this->shape.setFillColor(color);
    window.draw(this->shape);
    
    if (sf::Color::White == color) {
        this->text.setFillColor(sf::Color::Black);
    } else {
        this->text.setFillColor(sf::Color::White);
    }
    window.draw(this->text);
}

sf::RectangleShape Button::getShape() const {
    return this->shape;
}