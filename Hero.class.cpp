#include "Hero.class.hpp"

    Hero::Hero(int x, int y)
    {
        this->type = 'A';
        this->pos_x = x;
        this->pos_y = y;
        this->HP = 3;
    }

    int Hero::getHP() {
        return (this->HP);
    }

    void Hero::setHP(int h) {
        this->HP = h;
    }

    Hero::Hero(const Hero &obj)
    {
        this->type = obj.type;
        this->pos_x = obj.pos_x;
        this->pos_y = obj.pos_y;
    }

Hero& Hero::operator=(const Hero &obj)
    {
        this->type = obj.type;
        this->pos_x = obj.pos_x;
        this->pos_y = obj.pos_y;
        return (*this);
    }

    Hero::~Hero()
    {
    }