/**
 * @file Game.h
 * @brief This file contains the declaration of the Game class.
*/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include "../Player/Player.h"

/**
 * @class Game
 * @brief Represents the game state and logic.
 * 
 * The Game class manages the game state and provides methods for initializing the game, 
 * performing game actions, and checking game conditions.
 */
class Game {
    private:
        std::vector<Role*> *roles;                  /**< List of roles */
        std::vector<Character*> *characters;        /**< List of characters */
        std::vector<Card*> *cards;                  /**< List of cards */
        std::vector<Card*> *discards;               /**< List of discarded cards */
        std::vector<Player*> *players;              /**< List of players */
        std::vector<std::string*> *logs;            /**< List of logs */
        int nbPlayers;                              /**< Number of players */
        int indexActualPlayer;                      /**< Index of the actual player */

    public:
        bool isCarteDuBushidoInGame;                /**< Boolean to know if the Carte du Bushido is in the game */
        
        /**
         * @brief Constructs a new Game object.
        */
        Game();

        /**
         * @brief Initializes the roles in the game.
        */
        void initRole();
        
        /**
         * @brief Initializes the characters in the game.
        */
        void initCharacter();

        /**
         * @brief Initializes the cards in the game.
        */
        void initCard();

        /**
         * @brief Initializes the players in the game.
        */
        void initPlayer();

        /**
         * @brief set the number of players in the game.
         * @param nbPlayers The number of players.
        */
        void setNbPlayers(int nbPlayers);

        /**
         * @brief get the number of players in the game.
         * @return The number of players.
        */
        int getNbPlayers() const;

        /**
         * @brief get the index of the actual player.
         * @return The index of the actual player.
        */
        int getIndexActualPlayer() const;

        /**
         * @brief get the index of the player attacked.
         * @return The index of the player attacked.
        */
        int getIndexPlayerAttacked() const;

        /**
         * @brief get the players in the game.
         * @return The list of players.
        */
        std::vector<Player*> *getPlayers() const;

        /**
         * @brief get the cards in the stack
         * @return The list of cards.
        */
        std::vector<Card*> *getCards() const;

        /**
         * @brief get the discards in the game.
         * @return The list of discarded cards.
        */
        std::vector<Card*> *getDiscards() const;

        /**
         * @brief get the logs of the game.
         * @return The list of logs.
        */
        std::vector<std::string*> *getLogs() const;

        /**
         * @brief update the honor points and health points of the players.
        */
        void updateHonorPointsHP();

        /**
         * @brief recover the players' health points.
        */
        void recoverHP();

        /**
         * @brief pick a card from the stack.
         * @param player The player who picks the card.
         * @param nbCard The number of cards to pick.
        */
        void pick(Player *player, int nbCard);

        /**
         * @brief attack the player with a weapon card
         * @param card The weapon card used to attack.
         * @param player The player attacked.
         * @return True if the attack is successful, false otherwise.
        */
        bool attack(Weapon *card, Player *player);

        /**
         * @brief calculate the distance between the actual player and the target player.
         * @param playerTarget The target player.
         * @return The distance between the actual player and the target player.
        */
        int calculateDistance(Player *playerTarget);

        /**
         * @brief if the player can block the attack.
         * @param player The player who can block the attack.
         * @return True if the player can block the attack, false otherwise.
        */
        bool canBlock(Player *player);

        /**
         * @brief discard a card from the player's hand.
         * @param player The player who discards the card.
         * @param card The card to discard.
        */
        void discard(Player *player, Card* card);

        /**
         * @brief take the cards from the discard stack.
        */
        void recoverCards();

        /**
         * @brief change the actual player.
        */
        void changePlayer();

        /**
         * @brief action of cri de guerre action card.
        */
        void criDeGuerreFunction();

        /**
         * @brief action of the daimyo action card.
        */
        void daimyoFunction();

        /**
         * @brief action of the geisha action card.
         * @param player The player who uses the geisha card.
        */
        void geishaFunction(Player *player = nullptr);

        /**
         * @brief action of the ceremonie du the action card.
        */
        void ceremonieDuTheFunction();

        /**
         * @brief action of the ju jitsu action card.
        */
        void juJitsuFunction();

        /**
         * @brief action of the code du bushido permanent card.
        */
        void codeDuBushidoFunction();

        /**
         * @brief verification of the end of the game.
         * @return True if the game is over, false otherwise.
        */
        bool isGameOver();

        /**
         * @brief destructs a Game object.
        */
        ~Game();
};

#endif // GAME_H