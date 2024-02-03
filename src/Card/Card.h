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
        virtual int getIndex();
        virtual ~Card();
};

#endif // CARD_H