
#include "ClassGame.hpp"

#define N 50

Game::Game() {
    this->score = 0;
    this->wnd = initscr();
    cbreak();
    noecho();
    curs_set(0);
    if(!has_colors()) {
        endwin();
        std::cout << "ERROR: Terminal does not support color." << std::endl;
        exit(1);
    }
    start_color();
    refresh();
    keypad(wnd, true);
    nodelay(wnd,true);
    this->exit_requested = false;
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
}

bool Game::getExit() {
    return (this->exit_requested);
}

int Game::getScore() {
    return (this->score);
}

void Game::setScore(int s) {
    this->score = s;
}

void Game::setExit(bool e) {
    this->exit_requested = e;
}

void Game::run() {
    clear();
    int in_char;
    int i = -1;
    int T = 8;
    struct winsize w;
    double e;
    useconds_t delay;
    clock_t st;
    ioctl(0, TIOCGWINSZ, &w);
    Hero hero(w.ws_col / 2 - 1, w.ws_row - 7);
    Attack attack[3];
    Enemies enemies[N];
    int q = 1;
    while (++i < N)
        enemies[i].xy((rand() % w.ws_col - 1), -((rand() % (w.ws_row - 5))));
    enemies[i - 2].die('*');
    i = -1;
    bool exit_requested = false;
    while (1) {
        st = clock();
        in_char = wgetch(wnd);
        mvaddch(hero.get_y(), hero.get_x(), ' ');
        while (++i < 3)
            mvaddch(attack[i].get_y(), attack[i].get_x(), ' ');
        i = -1;
        while (++i < N)
            mvaddch(enemies[i].get_y(), enemies[i].get_x(), ' ');
        i = -1;
        switch (in_char) {
            case 'q':
                exit_requested = true;
                break;
            case KEY_UP:
            case 'w': {
                hero.move(0, -1);
                if (hero.get_y() < 2)
                    hero.xy(hero.get_x(), 2);
            }
                break;
            case ' ': {
                while (++i < 3)
                    if (attack[i].get_type() == '-') {
                        attack[i].set();
                        attack[i].xy(hero.get_x(), hero.get_y() - 1);
                        break;
                    }
                i = -1;
                break;
            }
            case KEY_DOWN:
            case 's': {
                hero.move(0, 1);
                if (hero.get_y() > w.ws_row - 6)
                    hero.xy(hero.get_x(), w.ws_row - 6);
            }
                break;
            case KEY_LEFT:
            case 'a': {
                hero.move(-1, 0);
                if (hero.get_x() < 1)
                    hero.xy(1, hero.get_y());
            }
                break;
            case KEY_RIGHT:
            case 'd': {
                hero.move(1, 0);
                if (hero.get_x() > w.ws_col - 2)
                    hero.xy(w.ws_col - 2, hero.get_y());
            }
                break;
            default:
                break;
        }
        while (++i < N) {
            if (q % T == 0)
                enemies[i].move(0, 1);
            if (enemies[i].get_y() == w.ws_row - 5)
                enemies[i].xy((rand() % w.ws_col - 1),  -((rand() % (w.ws_row - 5)) ));
            if (enemies[i].overlap_coord(hero.get_x(), hero.get_y()) == 0 && hero.get_type() == 'A') {
                if (enemies[i].get_type() == 'X')
                    hero.setHP(hero.getHP() - 1);
                if (enemies[i].get_type() == '*' && hero.getHP() < 3) {
                    this->setScore(this->getScore() + 50);
                    hero.setHP(hero.getHP() + 1);
                }
                enemies[i].xy((rand() % w.ws_col - 1),  -((rand() % (w.ws_row - 5)) ));
                if (hero.getHP() == 0) {
                    exit_requested = true;;
                    hero.die('-');
                }
            }
            if (enemies[i].get_type() == '*')
            {
                attron(COLOR_PAIR(1));
                mvaddch(enemies[i].get_y(), enemies[i].get_x(), enemies[i].get_type());
                attroff(COLOR_PAIR(1));
            }
            else
                mvaddch(enemies[i].get_y(), enemies[i].get_x(), enemies[i].get_type());
            if (q == 2000)
                T = 3;
            else if (q == 4000)
                T = 2;
            else if (q == 6000)
                T = 1;
        }
        q++;
        i = -1;
        while (++i < 3) {
            if (attack[i].get_y() == 1)
                attack[i].die('-');
            if (attack[i].get_type() == '.') {
                attack[i].move(0, -1);
                mvaddch(attack[i].get_y(), attack[i].get_x(), attack[i].get_type());
            }
            int j = -1;
            while (++j < N)
                if (attack[i].overlap_coord(enemies[j].get_x(), enemies[j].get_y()) == 0 && attack[i].get_type() == '.')
                {
                    attack[i].get_type();
                    enemies[j].xy((rand() % w.ws_col - 1),  -((rand() % (w.ws_row - 6)) ));
                    this->setScore(this->getScore() + 25);
                }
        }
        i = -1;
        if (!exit_requested)
            mvaddch(hero.get_y(), hero.get_x(), hero.get_type());
        else {
            mvwprintw(this->wnd, w.ws_row / 2 - 3, w.ws_col / 2 - 4, "GAME OVER");
            mvwprintw(this->wnd, w.ws_row / 2 - 1, w.ws_col / 2 - 6, "TRY AGAIN: Y/N");
            switch (in_char) {
                case 'n':
                    this->setExit(true);
                    return;
                case 'y': {
                    this->setScore(0);
                    this->setExit(false);
                    return;
                }
                default:
                    break;
            }
        }
        attron(A_BOLD);
        box(wnd, 0, 0);
        attroff(A_BOLD);
        mvwprintw(wnd, w.ws_row - 3, w.ws_col / 2 - 4, "Score: %d", this->score);
        attron(COLOR_PAIR(1));
        mvwprintw(wnd, w.ws_row - 3, 2, "Life: %d", hero.getHP());
        attroff(COLOR_PAIR(1));
        e = static_cast<clock_t>((st - clock()) / (double) CLOCKS_PER_SEC);
        delay = static_cast<useconds_t>(e) / 700000;
        usleep(delay);
        refresh();
        usleep(10000);
    }
}

Game::~Game() {
    endwin();
    std::cout << "GAME OVER" << std::endl;
}