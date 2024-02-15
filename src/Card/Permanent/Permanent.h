/**
 * @file Permanent.h
 * @brief This file contains the declaration of the Permanent class and the enum class PermanentType.
*/

#ifndef PERMANENT_H
#define PERMANENT_H

#include "../Card.h"

/**
 * @enum PermanentType
 * @brief Represents the type of a Permanent.
 * @note The type of a Permanent is also the index of the Permanent in the Image List
 * and as the name of the Permanent
 */
enum class PermanentType {
    ATTAQUE_RAPIDE,     /**< ATTAQUE_RAPIDE permanent type*/
    CODE_DU_BUSHIDO,    /**< CODE_DU_BUSHIDO permanent type*/
    ARMURE,             /**< ARMURE permanent type*/
    CONCENTRATION       /**< CONCENTRATION permanent type*/
};

/**
 * @class Permanent
 * @brief The Permanent class represents a permanent card in the game.
 * This class inherits from the Card class and adds functionality specific to permanent cards.
 */
class Permanent : public Card {
    private:
        PermanentType permanentType; /**< Type of permanent card*/
    
    public:
        /**
         * @brief Constructs a new Permanent object with the specified permanent type.
         * 
         * @param permanentType The type of the permanent card.
         */
        Permanent(PermanentType permanentType);
        
        /**
         * @brief Gets the type of the permanent card.
         * 
         * @return The permanent type.
         */
        PermanentType getPermanentType() const;
        
        /**
         * @brief Gets the index of the card.
         * 
         * @return The index of the card.
         */
        int getIndex() override;
};

#endif // PERMANENT_H