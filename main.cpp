#include <iostream>
#include <SDL.h>

const int WIN_WIDTH = 800, WIN_HEIGHT = 600;

int main(int argv, char** args){

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *w = SDL_CreateWindow("Auto Clicker",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    WIN_WIDTH, WIN_HEIGHT, 
                                    SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == w){

        std::cout << "Couldn't create the window" << std::endl << SDL_GetError() << std::endl;
        return 1;

    }  

SDL_Event windowEvent;

    while(true){

        if (SDL_PollEvent(&windowEvent)){

            if (SDL_QUIT == windowEvent.type) { break; }

        }

    }

    SDL_DestroyWindow(w);
    SDL_Quit();

    return EXIT_SUCCESS;

}