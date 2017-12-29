#ifndef ENEMIES_CLASS_HPP
# define ENEMIES_CLASS_HPP

#include "Player.class.hpp"

class Enemies: public Player
{
public:
    Enemies();
    Enemies(const Enemies &obj);
Enemies &operator=(const Enemies &obj);
    ~Enemies();
};

#endif