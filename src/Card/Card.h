#ifndef CARD_H
#define CARD_H

enum class CardType {
    ACTION,
    PERMANENT,
    WEAPON
};

class Card {
    private:
        CardType type;
    
    public:
        Card(CardType type);
        CardType getType() const;
};

#endif // CARD_H