
#ifndef CLASSGAME_HPP
#define CLASSGAME_HPP

#include "Attack.class.hpp"
#include "Hero.class.hpp"
#include "Enemies.class.hpp"
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>

class Game {
private:
    WINDOW *wnd;
    int score;
    bool exit_requested;


public:
    Game();
    Game(const Game &obj);
    Game &operator=(const Game &ob);
    void    run(void);
    ~Game();
    int getScore(void);
    void setScore(int s);
    bool getExit(void);
    void setExit(bool e);
};

#endif
