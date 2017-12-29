#include "Player.class.hpp"

    Player::Player()
    {
        this->pos_x = 0;
        this->pos_y = 0;
        this->type = '-';
    }

    Player::Player(const Player &obj)
    {
        this->pos_x = obj.pos_x;
        this->pos_y = obj.pos_y;
        this->type = obj.type;
    }

Player &Player::operator=(const Player &obj)
    {
        this->pos_x = obj.pos_x;
        this->pos_y = obj.pos_y;
        this->type = obj.type;
        return (*this);
    }

void  Player::move(int x, int y)
    {
        this->pos_x += x;
        this->pos_y += y;

    }

void  Player::xy(int x, int y)
{
    this->pos_x = x;
    this->pos_y = y;
}

void Player::die(char d)
    {
        this->type = d;
    }

int   Player::overlap_coord(int x, int y)
    {
        if (this->pos_x == x && this->pos_y == y)
            return (0);
        return (1);
    }

int  Player::get_x()
    {
        return (this->pos_x);
    }

int  Player::get_y()
    {
        return (this->pos_y);
    }

int  Player::get_type()
    {
        return (this->type);
    }

Player::~Player()
    {
    }