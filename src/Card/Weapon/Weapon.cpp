#include "Weapon.h"

Weapon::Weapon(WeaponType weaponType, int damage, int range) 
    : Card(CardType::WEAPON), weaponType(weaponType), damage(damage), range(range) {
}

WeaponType Weapon::getWeaponType() const {
    return this->weaponType;
}

int Weapon::getDamage() const {
    return this->damage;
}

int Weapon::getRange() const {
    return this->range;
}

int Weapon::getIndex() {
    return static_cast<int>(this->weaponType) + 12;
}