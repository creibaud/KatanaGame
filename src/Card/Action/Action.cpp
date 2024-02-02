#include "Action.h"

Action::Action(ActionType actionType) 
    : Card(CardType::ACTION), actionType(actionType) {
}

ActionType Action::getActionType() const {
    return this->actionType;
}