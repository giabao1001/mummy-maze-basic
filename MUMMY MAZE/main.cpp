#include <iostream>
#include <ncurses.h>
#include <cmath>
using namespace  std;
class Enemy {
    int x, y;
public:
    Enemy(int x0, int y0) : x(x0), y(y0) {} // get initial position
    int getX() const { return x; }
    int getY() const { return y; }
    void moveTo(int nx, int ny) { x = nx; y = ny; }
};
bool neardeath (int ex, int ey, int playerx, int playery) {
    if ( (abs(ex -playerx) ==1 && abs(ey - playery) ==0 ) || ( abs(ey -playery) == 1 && abs(ex - playerx) ==0 ) )
        return 1;
    return 0;
}
int main() {
    const int WIDTH = 100, HEIGHT = 20;
    int playerX = 0, playerY = 0;
    Enemy enemy(99, 19);

    // Initialize ncurses
    initscr();
    cbreak();        // Disable line buffering
    noecho();        // Don't echo pressed keys
    keypad(stdscr, TRUE); // Enable arrow keys
    nodelay(stdscr, FALSE); // Blocking input (optional)

    bool running = true;
    while (running) {
        // Clear screen using ncurses
        erase();

        // Draw borders and map
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                char ch = '.';
                if (x == playerX && y == playerY)
                    ch = '@';
                else if (x == enemy.getX() && y == enemy.getY())
                    ch = 'E';
                mvaddch(y, x, ch);
            }
        }

        refresh(); // Update screen
 if (playerX ==0 && playerY == HEIGHT-1) {
            // erase();
            refresh();
            mvprintw(10, 10, "You win!");
            move(10,10);
            printw("You win!");
     cout <<"you win!";
            break;
        }
        // Get input
        int key = getch();

        int oldX = playerX, oldY = playerY;

        switch (key) {
            case KEY_UP:    if (playerY > 0) playerY--; break;
            case KEY_DOWN:  if (playerY < HEIGHT - 1) playerY++; break;
            case KEY_LEFT:  if (playerX > 0) playerX--; break;
            case KEY_RIGHT: if (playerX < WIDTH - 1) playerX++; break;
            case 'q':
            case 'Q':       running = false; break;
        }
        // if enemmy gets in 1 square radius

        // Enemy AI: move one step toward player (Chebyshev distance: move diagonally)
        int ex = enemy.getX();
        int ey = enemy.getY();

        if (abs (ex - playerX) == 1 && abs (ey - playerY) == 1 ) {
            refresh();
            mvprintw(10, 10, "You lose!");
            move(10,10);
            printw("You lose!");
            cout <<"you lose!";
            break;
        }

        if (ey == playerY) {
            if (playerX > ex) {
                ex+=2;
            }
            else {
                ex-=2;
            }
        }
        else {
            if (ex < playerX) ex++;
            else if (ex > playerX) ex--;
        }

        if (ex == playerX) {
            if (playerY > ey) {
                ey+=2;
            }
            else {
                ey-=2;
            }
        }
        else {
            if (ey < playerY) ey++;
            else if (ey > playerY) ey--;
        }

        enemy.moveTo(ex, ey);

        if (neardeath(ex, ey, playerX, playerY)) {
            refresh();
            mvprintw(10, 10, "You lose!");
            move(10,10);
            printw("You lose!");
            cout <<"you lose!";
            break;
        }

        // Optional: add delay for smoother gameplay
        // napms(150);
    }

    // Clean up ncurses
    endwin();
    return 0;
}