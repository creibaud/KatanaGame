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