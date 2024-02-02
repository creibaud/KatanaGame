#ifndef PERMANENT_H
#define PERMANENT_H

#include "../Card.h"

enum class PermanentType {
    ATTAQUE_RAPIDE,
    CODE_DU_BUSHIDO,
    ARMURE,
    CONCENTRATION
};

class Permanent : public Card {
    private:
        PermanentType permanentType;
    
    public:
        Permanent(PermanentType permanentType);
        PermanentType getPermanentType() const;
};

#endif // PERMANENT_H