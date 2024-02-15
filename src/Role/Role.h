#ifndef ROLE_H
#define ROLE_H

#include <string>

enum class RoleType {
    SHOGUN,
    SAMURAI,
    NINJA,
    RONIN
};

class Role {
    private:
        RoleType type;
        int level;

    public:
        Role(RoleType type, int level = 0);
        RoleType getType() const;
        int getLevel() const;
        int getIndex() const;
        std::string getName() const;
};

#endif // ROLE_H