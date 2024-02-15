/**
 * @file Menu.h
 * @brief This file contains the declaration of the Menu class and of the constants SCREEN_WIDTH and SCREEN_HEIGHT.
*/

#ifndef MENU_H
#define MENU_H

#include "../Button/Button.h"

#define SCREEN_WIDTH 1920       /**< Width of the window */
#define SCREEN_HEIGHT 1080      /**< Height of the window */

/**
 * @class Menu
 * @brief Represents a menu in the game.
 * 
 * The Menu class is responsible for displaying a menu with buttons and images.
 * It allows the user to interact with the menu and retrieve the number of players selected.
 */
class Menu {
    private:
        sf::Font *font;                     /**< Font used for the title and buttons */
        sf::Text *title;                    /**< Title of the menu */
        std::vector<Button*> *buttons;      /**< List of buttons */
        sf::Texture *leftTexture;           /**< Texture for the left image */
        sf::Texture *rightTexture;          /**< Texture for the right image */
        sf::Sprite *leftSprite;             /**< Sprite for the left image */
        sf::Sprite *rightSprite;            /**< Sprite for the right image */
        int nbPlayers;                      /**< Number of players */
    
    public:
        /**
         * @brief Constructs a new Menu object.
         * 
         * @param font The font used for the title and buttons.
         * @param leftImage The image for the left side of the menu.
         * @param rightImage The image for the right side of the menu.
         */
        Menu(sf::Font *font, sf::Image *leftImage, sf::Image *rightImage);

        /**
         * @brief Get the number of players selected.
         * 
         * @return int The number of players.
         */
        int getNbPlayers() const;

        /**
         * @brief Display the menu on a given window.
         * 
         * @param window The window to display the menu on.
         */
        void display(sf::RenderWindow &window);

        /**
         * @brief Destructor for the Menu object.
         */
        ~Menu();
};

#endif // MENU_H