#ifndef ACTION_H
#define ACTION_H

#include "../Card.h"

enum class ActionType {
    CRI_DE_GUERRE,
    DAIMYO,
    DIVERSION,
    GEISHA,
    MEDITATION,
    PARADE,
    CEREMONIE_DU_THE,
    JU_JITSU
};

class Action : public Card {
    private:
        ActionType actionType;
    
    public:
        Action(ActionType actionType);
        ActionType getActionType() const;
        int getIndex() override;
};

#endif // ACTION_H