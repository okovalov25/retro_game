#include "Attack.class.hpp"

    Attack::Attack()
    {
        this->type = '-';
    }

    Attack::Attack(int x, int y)
    {
        this->type = '.';
        this->pos_x = x;
        this->pos_y = y;
    }

    Attack::Attack(const Attack &obj)
    {
        this->type = obj.type;
        this->pos_x = obj.pos_x;
        this->pos_y = obj.pos_y;
    }

Attack& Attack::operator=(const Attack &obj)
    {
        this->type = obj.type;
        this->pos_x = obj.pos_x;
        this->pos_y = obj.pos_y;
        return (*this);
    }

void    Attack::set() {
    this->type = '.';
}

    Attack::~Attack()
    {
    }
