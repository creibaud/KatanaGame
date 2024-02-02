#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Font *font, std::string text, int fontSize) {
    this->shape.setSize(size);
    this->shape.setPosition(position);
    this->shape.setFillColor(color);

    this->text.setFont(*font);
    this->text.setString(text);
    this->text.setCharacterSize(fontSize);
    this->text.setFillColor(sf::Color::Black);
    this->text.setPosition(position.x + size.x / 2 - this->text.getGlobalBounds().width / 2, position.y + size.y / 2 - this->text.getGlobalBounds().height / 2);
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(this->shape);
    window.draw(this->text);
}

sf::RectangleShape Button::getShape() const {
    return this->shape;
}