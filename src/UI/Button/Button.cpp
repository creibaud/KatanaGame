#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font *font, std::string text, int fontSize) {
    this->shape.setSize(size);
    this->shape.setPosition(position);

    this->text.setFont(*font);
    this->text.setString(text);
    this->text.setCharacterSize(fontSize);
    this->text.setPosition(position.x + size.x / 2 - this->text.getGlobalBounds().width / 2, position.y + size.y / 2 - this->text.getGlobalBounds().height / 2 - 3);
}

sf::RectangleShape Button::getShape() const {
    return this->shape;
}

bool Button::isHovered(sf::RenderWindow &window) const {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if (this->shape.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        return true;
    }
    
    return false;
}

bool Button::isClicked(sf::RenderWindow &window) const {
    if (this->isHovered(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }
    
    return false;
}

void Button::draw(sf::RenderWindow &window) {
    if (this->isHovered(window)) {
        this->shape.setFillColor(sf::Color::Red);
    } else {
        this->shape.setFillColor(sf::Color::White);
    }

    window.draw(this->shape);
    
    if (this->shape.getFillColor() == sf::Color::White) {
        this->text.setFillColor(sf::Color::Black);
    } else {
        this->text.setFillColor(sf::Color::White);
    }
    window.draw(this->text);
}