#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include "screen.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define SCALE 4

#define RANDCOLOR rand()%255

using namespace std;

const int directions[8][2] = {{-1,1}, {0,1}, {1,1}, {-1,0}, {1,0}, {-1,-1}, {0,-1}, {1,-1}};
const int deadOrAlive[8] = {-1,-1,0,1,-1,-1,0,-1};

bool add(int k, int n) {
    if (n+k > 0) {
        return true;
    } else {
        return false;
    }
}

bool nextGenerationAlive(array<array<int, WINDOW_HEIGHT>, WINDOW_WIDTH>& game, int x, int y) {
    int neighbours = 0;

    for (int i=0; i<8; i++) {
        if (game[x - directions[i][0]][y - directions[i][1]] == 1) {
            neighbours++;
        }
    }

    /*if (neighbours < 2) {
        return false;
    }

    if (game[x][y] && (neighbours == 2 || neighbours == 3)) {
        return true;
    }

    if (neighbours > 3) {
        return false;
    }

    if (!game[x][y] && neighbours == 3) {
        return true;
    }
    */

    return add(game[x][y], deadOrAlive[neighbours]);
}

int main(int argc, char** args) {
    int myint = 0;
    cout << myint -1 << endl;
    Screen screen;
    array<array<int, WINDOW_HEIGHT>, WINDOW_WIDTH> display {};
    array<array<int, WINDOW_HEIGHT>, WINDOW_WIDTH> swap {};

    for(auto& row : display) {
        generate(row.begin(), row.end(), []() {return rand() % 10 == 0 ? 1 : 0; });
    }

    while(true)
    {
        for (int i=0; i< WINDOW_WIDTH; ++i) {
            for (int j=0; j < WINDOW_HEIGHT; j++){
                swap[i][j] = int(nextGenerationAlive(display, i, j));
            }
        }

        for (int x=0; x < WINDOW_WIDTH; ++x) {
            for (int y=0; y < WINDOW_HEIGHT; ++y) {
                if (swap[x][y]) {
                    screen.drawPixel(x, y);
                }
            }
        }

        copy(swap.begin(), swap.end(), display.begin());

        screen.update();
        SDL_Delay(1000/120);
        screen.input();
        screen.clearPixels();
    }



    return 0;
}
