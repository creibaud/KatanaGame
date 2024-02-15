/**
 * @file Card.h
 * @brief This file contains the declaration of the Card class and the enum class CardType.
*/

#ifndef CARD_H
#define CARD_H

/**
 * @enum CardType
 * @brief Represents the type of a card.
 */
enum class CardType {
    ACTION,     /**< Action card type */
    PERMANENT,  /**< Permanent card type */
    WEAPON      /**< Weapon card type */
};

/**
 * @class Card
 * @brief The Card class represents a card in the game.
 * 
 * This class provides the basic functionality of a card, such as
 * the type of the card.
 */
class Card {
    private:
        CardType type; /**< Card type */
    
    public:
        /**
         * @brief Constructs a Card object with the specified type.
         * @param type The type of the card.
         * @note This constructor is used by the derived classes to set the type of the card.
         */
        Card(CardType type);

        /**
         * @brief Gets the type of the card.
         * @return The type of the card.
         */
        CardType getType() const;

        /**
         * @brief Gets the index of the card.
         * @return The index of the card.
         */
        virtual int getIndex();

        /**
         * @brief Destroys the Card object.
         */
        virtual ~Card();
};

#endif // CARD_H