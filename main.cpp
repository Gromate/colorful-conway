#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <random>
#include <array>
#include "cell.h"

#define SCALE 4

#define WINDOW_WIDTH 1200 / SCALE
#define WINDOW_HEIGHT 600 / SCALE

#define RANDCOLOR rand() % 255

using namespace std;

SDL_Color ageToColor(long int age);

const int directions[8][2] = {{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}};
const int deadOrAlive[8] = {-1, -1, 0, 1, -1, -1, -1, -1};

bool add(int k, int n)
{
    if (n + k > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool nextGenerationAlive(array<array<Cell, WINDOW_HEIGHT>, WINDOW_WIDTH> &game, int x, int y)
{
    int neighbours = 0;

    for (int i = 0; i < 8; i++)
    {
        if (game[x - directions[i][0]][y - directions[i][1]].aliveness == 1)
        {
            neighbours++;
        }
    }

    // random_device rd;
    // uniform_int_distribution<> percent(1, 1000);
    // const int liveChance = 99;
    // const int spontaneusAlive = 75;
    // if (percent(rd) == 1) {
    // return true;
    //}

    // if (rand()%liveChance) {
    return add(game[x][y].aliveness, deadOrAlive[neighbours]);
    //} else {
    // return false;
    //}
}

int main(int argc, char **args)
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH * SCALE, WINDOW_HEIGHT * SCALE, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, SCALE, SCALE);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    srand(time(0));
    array<array<Cell, WINDOW_HEIGHT>, WINDOW_WIDTH> display{};
    array<array<Cell, WINDOW_HEIGHT>, WINDOW_WIDTH> swap{};

    for (auto &row : display)
    {
        for (auto &cell : row)
        {
            cell = Cell(rand() % 10 ? 1 : 0);
            cell.updateColor();
        }
    }

    while (true)
    {
        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            for (int y = 0; y < WINDOW_HEIGHT; y++)
            {
                swap[x][y] = Cell(int(nextGenerationAlive(display, x, y)), display[x][y].getAge(), display[x][y].getColor());
                swap[x][y].upAge();
                swap[x][y].updateColor();
            }
        }

        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            for (int y = 0; y < WINDOW_HEIGHT; y++)
            {
                if (display[x][y].aliveness)
                {
                    SDL_Color color = ageToColor(display[x][y].age * 50);
                    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_Delay(1000 / 60);

        display.swap(swap);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            /* SDL_QUIT event (window close) */
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;

            default:
                break;
            }
        }
    }
    return 0;
}

SDL_Color ageToColor(long int age)
{
    SDL_Color color;
    color.r = 255;
    color.g = age % 255;
    color.b = age / 255 % 256;
    color.a = 255;

    return color;
}
