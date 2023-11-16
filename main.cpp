#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include "screen.h"
#include "cell.h"

#define SCALE 4

#define WINDOW_WIDTH 800/SCALE
#define WINDOW_HEIGHT 600/SCALE

#define RANDCOLOR rand()%255

using namespace std;

const int directions[8][2] = {{-1,1}, {0,1}, {1,1}, {-1,0}, {1,0}, {-1,-1}, {0,-1}, {1,-1}};
const int deadOrAlive[8] = {-1,-1,0,1,-1,-1,-1,-1};


bool add(int k, int n) {
    if (n+k > 0) {
        return true;
    } else {
        return false;
    }
}

bool nextGenerationAlive(array<array<Cell, WINDOW_HEIGHT>, WINDOW_WIDTH>& game, int x, int y) {
    int neighbours = 0;

    for (int i=0; i<8; i++) {
        if (game[x - directions[i][0]][y - directions[i][1]].aliveness == 1) {
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

    //random_device rd;  
    //uniform_int_distribution<> percent(1, 1000);
    //const int liveChance = 99;
    //const int spontaneusAlive = 75;
    //if (percent(rd) == 1) {
        //return true;
    //}

    //if (rand()%liveChance) {
        return add(game[x][y].aliveness, deadOrAlive[neighbours]);
    //} else {
        //return false;
    //}
}

int main(int argc, char** args) {
    srand(time(0));
    Screen screen;
    array<array<Cell, WINDOW_HEIGHT>, WINDOW_WIDTH> display {};
    array<array<Cell, WINDOW_HEIGHT>, WINDOW_WIDTH> swap {};

    for (auto& row : display) {
        for (auto& cell : row) {
            cell = Cell(rand()%10 ? 1 : 0);
            cell.updateColor();
        }
    }
    /*for(auto& row : display) {
        generate(row.begin(), row.end(), []() {return rand() % 10 == 0 ? 1 : 0; });
    }*/

    while(true)
    {
        for (int x=0; x< WINDOW_WIDTH; x++) {
            for (int y=0; y < WINDOW_HEIGHT; y++){
                swap[x][y] = Cell(int(nextGenerationAlive(display, x, y)), display[x][y].getAge(), display[x][y].getColor());
                swap[x][y].upAge();
                swap[x][y].updateColor();
            }
        }

        const int number = 100;
        cout << swap[number][number].age << " " << display[number][number].age << endl;

        uint8_t red = 0;
        for (int x=0; x < WINDOW_WIDTH; x++) {
            for (int y=0; y < WINDOW_HEIGHT; y++) {
                if (display[x][y].aliveness) {
                    cout << "age" << display[x][y].getAge() << endl;
                    if (int(display[x][y].getAge()) >= 2) {
                        red = 255;
                    }
                    screen.drawPixel(x, y, uint8_t(red), display[x][y].green, display[x][y].blue, display[x][y].color.a);
                }
            }
        }

        //copy(swap.begin(), swap.end(), display.begin());
        //display = swap;

        screen.update();
        SDL_Delay(1000/5);
        screen.input();
        screen.clearPixels();

        display.swap(swap);
    }



    return 0;
}
