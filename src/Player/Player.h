/**
 * @file Player.h
 * @brief This file contains the declaration of the Player class.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../includes/InitRole.h"
#include "../includes/InitCard.h"
#include "../includes/InitCharacter.h"

/**
 * @class Player
 * @brief Represents a player in the game.
 */
class Player {
    private:
        Role *role;                                         /**< The role of the player */
        Character *character;                               /**< The character of the player */
        std::vector<Card*> *hand;                           /**< The hand of the player */
        std::vector<Permanent*> *permanentCardsPlayed;      /**< The permanent cards played by the player */

        int maxNbAttack;

    public:
        int HP;             /**< Health points of the player */
        int honorPoints;    /**< Honor points of the player */
        bool asAttacked;    /**< Whether the player has attacked or not */
        int nbAttack;       /**< Number of attacks the player can perform */
        
        /**
         * @brief Constructs a new Player object.
         * 
         * @param role The role of the player.
         * @param character The character of the player.
         */
        Player(Role *role, Character *character);

        /**
         * @brief Get the role of the player.
         * 
         * @return Role* The role of the player.
         */
        Role* getRole() const;

        /**
         * @brief Get the character of the player.
         * 
         * @return Character* The character of the player.
         */
        Character* getCharacter() const;

        /**
         * @brief Get the hand of the player.
         * 
         * @return std::vector<Card*>* The hand of the player.
         */
        std::vector<Card*>* getHand() const;

        /**
         * @brief Get the permanent cards played by the player.
         * 
         * @return std::vector<Permanent*>* The permanent cards played by the player.
         */
        std::vector<Permanent*>* getPermanentCardsPlayed() const;

        /**
         * @brief Get the maximum number of attacks the player can perform.
         * 
         * @return int The maximum number of attacks the player can perform.
         */
        int getMaxNbAttack() const;
        
        /**
         * @brief the action of the mediation action card
         */
        void meditationFunction();

        /**
         * @brief the action of the attack rapide permanent card
         * @return int The number of damage the player can deal with all the attack rapide cards played.
         */
        int attackRapideFunction();

        /**
         * @brief the action of the code du bushido permanent card
         * @return std::pair<Permanent*, int> The code du bushido card and its index in the permanent cards played.
         */
        std::pair<Permanent*, int> asCodeDuBushido();

        /**
         * @brief the action of the armure permanent card
         * @return int The number of armor points the player has.
         */
        int armureFunction();

        /**
         * @brief the action of the concentration permanent card
         */
        void concentrationFunction();

        /**
         * @brief if the player is down
         * @return bool if the player is down
         */
        bool isDown() const;

        /**
         * @brief recover all the HP of is character maxHP
         */
        void recover();

        /**
         * @brief Destructor for the Player object.
         */
        ~Player();
};

#endif // PLAYER_H