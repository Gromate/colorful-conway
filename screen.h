#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <algorithm>
#include <SDL2/SDL.h>

#pragma once

const float SCALE = 4;

using namespace std;

class Screen {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_bool done;
    vector<SDL_Point> points;
    vector<SDL_Color> colors;
    SDL_Event event;

public:
    Screen() {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, SCALE, SCALE);
    }

    void drawPixel (int x, int y, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255) {
        points.emplace_back(SDL_Point{x,y});
        colors.emplace_back(SDL_Color{r,g,b,a});
    }

    void clearPixels()
    {
        points.clear();
    }

    void update()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for(long unsigned int i = 0; i < points.size(); i++)
        {
            SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
            SDL_RenderDrawPointF(renderer, points[i].x,points[i].y);
        }


        SDL_RenderPresent(renderer);
    }

    void input() {
        while( SDL_PollEvent( &event ) )
        {
            switch( event.type )
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
};
