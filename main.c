#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

typedef struct circle
{
    int x;
    int y;
    int radius;
} Circle;

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Bouncy Ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_Event event;
    int running = 1;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        SDL_Rect rect = (SDL_Rect){0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
        SDL_FillRect(surface, &rect, 0xffffffff);

        SDL_UpdateWindowSurface(window);
    }

}
