#ifndef PLAYER_CLASS_HPP
# define PLAYER_CLASS_HPP

#include <iostream>

class Player
{
protected:
    int pos_x;
    int pos_y;
    char type;

public:
    Player();
    Player(const Player &obj);
    Player &operator=(const Player &obj);
    void move(int x, int y);
    void xy(int x, int y);
    int overlap_coord(int x, int y);
    void die(char d);
    int get_x();
    int get_y();
    int get_type();
    ~Player();
};

#endif