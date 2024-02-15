/**
 * @file Button.h
 * @brief This file contains the declaration of the Button class.
*/

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

/**
 * @class Button
 * @brief Represents a graphical button element.
 */
class Button {
    private:
        sf::RectangleShape shape;   /**< The shape of the button. */
        sf::Text text;              /**< The text displayed on the button. */

    public:
        /**
         * @brief Constructs a Button object.
         * @param position The position of the button.
         * @param size The size of the button.
         * @param font A pointer to the font used for the button text.
         * @param text The text displayed on the button.
         * @param fontSize The font size of the button text.
         */
        Button(sf::Vector2f position, sf::Vector2f size, sf::Font *font, std::string text, int fontSize);

        /**
         * @brief Gets the shape of the button.
         * @return The shape of the button.
         */
        sf::RectangleShape getShape() const;

        /**
         * @brief Checks if the button is being hovered over.
         * @param window The render window to check against.
         * @return True if the button is being hovered over, false otherwise.
         */
        bool isHovered(sf::RenderWindow &window) const;

        /**
         * @brief Checks if the button is being clicked.
         * @param window The render window to check against.
         * @return True if the button is being clicked, false otherwise.
         */
        bool isClicked(sf::RenderWindow &window) const;

        /**
         * @brief Draws the button on the specified render window.
         * @param window The render window to draw on.
         */
        void draw(sf::RenderWindow &window);
};

#endif // BUTTON_H