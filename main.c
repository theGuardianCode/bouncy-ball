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

void DrawCircle(SDL_Surface* surface, Circle circle, int colour)
{
    int low_x = circle.x - circle.radius;
    int high_x = circle.x + circle.radius;
    int low_y = circle.y - circle.radius;
    int high_y = circle.y + circle.radius;

    int radius_squared = circle.radius * circle.radius;

    for (int y = low_y; y <= high_y; y++)
    {
        for (int x = low_x; x <= high_x; x++)
        {
            // dst^2 = (x^2 + y^2)
            // if dst2 <= rad2 then draw point
            int distance_squared = (x-circle.x)*(x-circle.x) + (y-circle.y)*(y-circle.y);
            if (distance_squared <= radius_squared)
            {
                SDL_Rect rect = {x, y, 1, 1};
                SDL_FillRect(surface, &rect, colour);
            }
        }
    }
}

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
        
        Circle circle = {300, 300, 50};
        DrawCircle(surface, circle, 0xffffffff);

        SDL_UpdateWindowSurface(window);
    }

}
