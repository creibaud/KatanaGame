#ifndef WEAPON_H
#define WEAPON_H

#include "../Card.h"

enum class WeaponType {
    NODACHI,
    NAGINATA,
    NAGAYARI,
    TANEGASHIMA,
    DAIKYU,
    BO,
    KUSARIGAMA,
    KATANA,
    SHURIKEN,
    KANABO,
    BOKKEN,
    KISERU,
    WAKIZASHI
};

class Weapon : public Card {
    private:
        WeaponType weaponType;
        int damage;
        int range;
    
    public:
        Weapon(WeaponType weaponType, int damage, int range);
        WeaponType getWeaponType() const;
        int getDamage() const;
        int getRange() const;
        int getIndex() override;
};

#endif // WEAPON_H