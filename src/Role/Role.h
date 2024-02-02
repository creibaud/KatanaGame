#ifndef ROLE_H
#define ROLE_H

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
};

#endif // ROLE_H