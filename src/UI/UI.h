#ifndef UI_H
#define UI_H

#include "Menu/Menu.h"
#include "../Game/Game.h"

#define FPS 60  /**< Frames per second */

/**
 * @class UI
 * @brief Represents the user interface of the game.
 * 
 * The UI class handles the rendering and interaction with the game's graphical user interface.
 * It manages the window, fonts, textures, sprites, buttons, and other UI elements.
 * It also provides methods for updating and displaying the UI, as well as handling user input.
 */
class UI {
    private:
        sf::RenderWindow *window;                               /**< The game window */
        sf::Font *font;                                         /**< Font used for the text */

        sf::Texture *HPTexture;                                 /**< Texture for the health points */
        sf::Texture *HonorTexture;                              /**< Texture for the honor points */
        sf::Texture *backRoleTexture;                           /**< Texture for the back of the role cards */
        sf::Texture *backCardTexture;                           /**< Texture for the back of the card */
        std::vector<sf::Texture*> *roleTextures;                /**< Textures for the role cards */
        std::vector<sf::Texture*> *cardTextures;                /**< Textures for the cards */
        std::vector<sf::Texture*> *characterTextures;           /**< Textures for the characters */

        sf::Sprite *backRoleSprite;                             /**< Sprite for the back of the role cards */
        std::vector<sf::Sprite*> *playersSprites;               /**< Sprites for the players */
        std::vector<sf::Sprite*> *HPSprites;                    /**< Sprites for the health points */
        std::vector<sf::Text*> *HPTexts;                        /**< Texts for the health points */
        std::vector<sf::Sprite*> *HonorSprites;                 /**< Sprites for the honor points */
        std::vector<sf::Text*> *HonorTexts;                     /**< Texts for the honor points */

        sf::Sprite *actualPlayerSprite;                         /**< Sprite for the actual player */
        sf::Sprite *actualPlayerRoleSprite;                     /**< Sprite for the role of the actual player */
        std::vector<sf::Sprite*> *actualPlayerCardSprites;      /**< Sprites for the cards of the actual player */
        sf::Sprite *HPSpritePlayer;                             /**< Sprite for the health points of the actual player */
        sf::Text *HPTextPlayer;                                 /**< Text for the health points of the actual player */
        sf::Sprite *HonorSpritePlayer;                          /**< Sprite for the honor points of the actual player */
        sf::Text *HonorTextPlayer;                              /**< Text for the honor points of the actual player */

        std::vector<sf::Sprite*> *stackSprites;                 /**< Sprites for the stack */
        std::vector<sf::Sprite*> *discardStackSprites;          /**< Sprites for the discard stack */

        std::vector<Player*> *players;                          /**< List of players */
        std::vector<Card*> *hand;                               /**< Hand of the actual player */
        std::vector<Card*> *stack;                              /**< Stack of the game */
        std::vector<Card*> *discardStack;                       /**< Discard stack of the game */

        std::vector<std::string*> *logs;                        /**< List of logs */
        std::vector<sf::Text*> *logsTexts;                      /**< Texts for the logs */
        sf::RectangleShape *logsBackground;                     /**< Background for the logs */
        sf::Text *openLogsText;                                 /**< Text for opening the logs */
        sf::RectangleShape *openLogsBtn;                        /**< Button for opening the logs */
        sf::Text *closeLogsText;                                /**< Text for closing the logs */
        sf::RectangleShape *closeLogsBtn;                       /**< Button for closing the logs */
        bool isOpenLogsText;                                    /**< Whether the logs are open or not */

        Button *passParadeBtn;                                  /**< Button for passing the parade */
        Button *endTurnBtn;                                     /**< Button for ending the turn */
        Button *discardingBtn;                                  /**< Button for discarding */
        bool isDiscarding;                                      /**< Whether the player is discarding or not */

        Game *game;                                             /**< The game */
        int indexActualPlayer;                                  /**< Index of the actual player */
        bool blocking;                                          /**< Whether the player is blocking the attack or not */
        int nbPlayers;                                          /**< Number of players */
        int spriteShogunIndex;                                  /**< Index of the shogun sprite */
        int indexSelectedCard;                                  /**< Index of the selected card */
        int indexSelectedPlayer;                                /**< Index of the selected player */

        int attackRapideNbDamage;                               /**< Number of damage for the attack rapide */
    
    public:
        /**
         * @brief Constructs a new UI object.
         * 
         * @param font The font used for the text.
         * @param HPImage The image for the health points.
         * @param HonorImage The image for the honor points.
         * @param backRoleImage The image for the back of the role cards.
         * @param backCardImage The image for the back of the cards.
         * @param roleImages The images for the role cards.
         * @param cardImages The images for the cards.
         * @param characterImages The images for the characters.
         */
        UI(sf::Font *font, sf::Image *HPImage, sf::Image *HonorImage, sf::Image *backRoleImage, sf::Image *backCardImage, std::vector<sf::Image*> *roleImages, std::vector<sf::Image*> *cardImages, std::vector<sf::Image*> *characterImages);
        
        /**
         * @brief the menu screen
         */
        void menu(sf::Image *leftImage, sf::Image *rightImage);

        /**
         * @brief the game screen
         */
        void start();

        /**
         * @brief update the UI
         */
        void update();

        /**
         * @brief display the UI
         */
        void display();

        /**
         * @brief set the player sprite other than the actual player 
         */
        void setPlayersSprites();

        /**
         * @brief set the honor points and health points of the players other than the actual player 
         */
        void setSpriteHonorCharactersHP(int index);

        /**
         * @brief set the actual player sprite, honor points and health points
         */
        void setActualPlayerSprite();

        /**
         * @brief set the actual player card sprites
         */
        void setHandSprite();

        /**
         * @brief set the stack sprites
         */
        void setStackSprite();

        /**
         * @brief set the discard stack sprites
         */
        void setDiscardStackSprite();

        /**
         * @brief set the logs texts and logs background
         */
        void setLogsTexts();

        /**
         * @brief set the red circle that indicates the shogun player if is not is turn
         */
        void setPermanentCircleSprites();

        /**
         * @brief handle the click event on the logs button
         */
        void handleClickLogBtn(sf::Event event);

        /**
         * @brief handle the click event on the hand cards
         */
        void handleClickHandCard(sf::Event event);

        /**
         * @brief handle the click event on the parade pass button
         */
        void handleClickPassParadeBtn(sf::Event event);

        /**
         * @brief handle the click event on the end turn button
         */
        void handleClickEndTurnBtn(sf::Event event);

        /**
         * @brief handle the click event on the discard button
         */
        void handleClickDiscardingBtn(sf::Event event);

        /**
         * @brief handle the click event on the Nobunage character if the actual player is Nobunaga
         */
        void handleClickNobunaga(sf::Event event);

        /**
         * @brief score screen at end of the game
         */
        void score();

        /**
         * @brief destroy the UI
         */
        ~UI();
};

#endif // UI_H