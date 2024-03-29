#include "Role.h"

Role::Role(RoleType type, int level)
    : type(type), level(level) {
}

RoleType Role::getType() const {
    return this->type;
}

int Role::getLevel() const {
    return this->level;
}

int Role::getIndex() const {
    return static_cast<int>(this->type);
}

std::string Role::getName() const {
    switch (this->type) {
        case RoleType::SHOGUN:
            return "Shogun";
        case RoleType::SAMURAI:
            return "Samurai";
        case RoleType::NINJA:
            return "Ninja lv" + std::to_string(this->level);
        case RoleType::RONIN:
            return "Ronin";
        default:
            return "";
    }
}