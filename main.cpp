#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

// You must include the command line parameters for your main function to be recognized by SDL
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

#define SCALE 4
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

    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);

    int x = 0;
    int y = 0;
	int close = 0;
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


		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderDrawPoint(renderer, x, y);

        SDL_RenderPresent(renderer);
        x++;
        y++;



		// calculates to 60 fps
		SDL_Delay(1000 / 30);
	}

    // Destroy the window. This will also destroy the surface
    SDL_DestroyWindow( window );

    // Quit SDL
    SDL_Quit();

    // End the program
    return 0;
}
