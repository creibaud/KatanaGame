/**
 * @file Action.h
 * @brief This file contains the declaration of the Action class and the enum class ActionType.
*/

#ifndef ACTION_H
#define ACTION_H

#include "../Card.h"

/**
 * @enum ActionType
 * @brief Represents the type of an Action.
 * @note The type of an Action is also the index of the Action in the Image List
 * and as the name of the Action
 */
enum class ActionType {
    CRI_DE_GUERRE,      /**< CRI_DE_GUERRE action type*/
    DAIMYO,             /**< DAIMYO action type*/
    DIVERSION,          /**< DIVERSION action type*/
    GEISHA,             /**< GEISHA action type*/
    MEDITATION,         /**< MEDITATION action type*/
    PARADE,             /**< PARADE action type*/
    CEREMONIE_DU_THE,   /**< CEREMONIE_DUTHE action type*/
    JU_JITSU            /**< JU_JITSU action type*/
};

/**
 * @class Action
 * @brief The Action class represents an action card in the game.
 * This class inherits from the Card class and adds an ActionType attribute.
 * It provides methods to get the action type and the index of the card.
 */
class Action : public Card {
    private:
        ActionType actionType; /**< Type of action card */
    
    public:
        /**
         * @brief Constructs an Action object with the specified action type.
         * 
         * @param actionType The type of the action.
         */
        Action(ActionType actionType);
        
        /**
         * @brief Gets the action type of the card.
         * 
         * @return The action type of the card.
         */
        ActionType getActionType() const;
        
        /**
         * @brief Gets the index of the card.
         * 
         * @return The index of the card.
         */
        int getIndex() override;
};

#endif // ACTION_H