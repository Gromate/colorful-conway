#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include "screen.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define SCALE 4

#define RANDCOLOR rand()%255

using namespace std;

int main(int argc, char** args) {

    // Pointers to our window and surface
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Initialize SDL. SDL_Init will return -1 if it fails.
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        system("pause");
        // End the program

        return 1;
    }

    // Create our window
    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
    //window = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
    //renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetScale(renderer, SCALE, SCALE);

    // Make sure creating the window succeeded
    if ( !window ) {
        cout << "Error creating window: " << SDL_GetError()  << endl;
        system("pause");
        // End the program
        return 1;
    }

    SDL_RenderClear(renderer);

    srand(time(NULL));

	int close = 0;
    int time = 0;
	while (!close) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				close = 1;
				break;
            default:
                continue;
                break;
            }
		}



        for (int x=0; x < WINDOW_WIDTH/SCALE; x++) {
            for (int y=0; y < WINDOW_HEIGHT/SCALE; y++) {
            SDL_SetRenderDrawColor(renderer, x + (time%255),y+ (time%255),(time)%255,255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        time++;

        SDL_RenderPresent(renderer);

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}

    // Destroy the window. This will also destroy the surface
    SDL_DestroyWindow( window );

    // Quit SDL
    SDL_Quit();

    // End the program
    return 0;
}
