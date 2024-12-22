#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1152
#define SCREEN_HEIGHT 860

#define COLOUR_WHITE 0xffffff
#define COLOUR_BLACK 0x000000

#define GRAVITY 1

const double DAMPENING = 0.98;

SDL_Surface* g_surface = NULL;

typedef struct circle
{
    double x;
    double y;
    double radius;
    double vel_x;
    double vel_y;
} Circle;

void DrawCircle(Circle circle, int colour)
{
    double low_x = circle.x - circle.radius;
    double high_x = circle.x + circle.radius;
    double low_y = circle.y - circle.radius;
    double high_y = circle.y + circle.radius;

    double radius_squared = circle.radius * circle.radius;

    for (double y = low_y; y <= high_y; y++)
    {
        for (double x = low_x; x <= high_x; x++)
        {
            // dst^2 = (x^2 + y^2)
            // if dst2 <= rad2 then draw point
            double distance_squared = (x-circle.x)*(x-circle.x) + (y-circle.y)*(y-circle.y);
            if (distance_squared <= radius_squared)
            {
                SDL_Rect rect = {x, y, 1, 1};
                SDL_FillRect(g_surface, &rect, colour);
            }
        }
    }
}

void UpdatePosition(Circle* circle)
{
    circle->vel_y += GRAVITY;
    
    circle->x += circle->vel_x;
    circle->y += circle->vel_y;

    // Check if ball is outside boundaries
    // Right
    if (circle->x + circle->radius > SCREEN_WIDTH)
    {
        circle->x = SCREEN_WIDTH - circle->radius;
        circle->vel_x = -circle->vel_x * DAMPENING;
    }

    // Left
    if (circle->x - circle->radius < 0)
    {
        circle->x = circle->radius;
        circle->vel_x = -circle->vel_x * DAMPENING;
    }

    // Top
    if (circle->y - circle->radius < 0)
    {
        circle->y = circle->radius;
        circle->vel_y = -circle->vel_y * DAMPENING;
    }

    // Bottom
    if (circle->y + circle->radius > SCREEN_HEIGHT)
    {
        circle->y = SCREEN_HEIGHT - circle->radius;
        circle->vel_y = -circle->vel_y * DAMPENING;
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Bouncy Ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    g_surface = SDL_GetWindowSurface(window);

    SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Circle circle = {300, 300, 100, 10, 10};

    int now = SDL_GetPerformanceCounter();
    int last = 0;
    double dt = 0;

    SDL_Event event;
    bool running = true;
    bool holding = false;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (holding)
                {
                    holding = false;
                }
                else
                {
                    int mouse_x, mouse_y;
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    if (mouse_x > circle.x - circle.radius && mouse_x < circle.x + circle.radius &&
                            mouse_y > circle.y - circle.radius && mouse_y < circle.y + circle.radius)
                    {
                        holding = true;
                    }
                }
            }
        }
        last = now;
        now = SDL_GetPerformanceCounter();

        dt = (double)(now - last)/(double)SDL_GetPerformanceFrequency();

        SDL_FillRect(g_surface, &screenRect, COLOUR_BLACK);
        
        if (holding != true)
        {
            UpdatePosition(&circle);
        } else {
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            circle.x = mouse_x;
            circle.y = mouse_y;
        }
        DrawCircle(circle, COLOUR_WHITE);
        SDL_UpdateWindowSurface(window);

        SDL_Delay(20);
    }

}
