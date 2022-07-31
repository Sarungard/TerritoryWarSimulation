#include <iostream>
#include <SDL.h>
#include <Speed.h>

SDL_Rect dest;
Uint32 render_flags;
SDL_Window* win;
SDL_Renderer* rend;
Speed speed;

void initWindow();

int main(int argc, char* argv[])
{
    initWindow();
    //speed = Speed(300);

    int close = 0;
    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            std::cout << speed.getSpeed() << std::endl;
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    dest.y -= speed / 30;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    dest.x -= speed / 30;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    dest.y += speed / 30;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    dest.x += speed / 30;
                    break;
                case SDL_SCANCODE_KP_PLUS:
                    speed += 90;
                    break;
                case SDL_SCANCODE_KP_MINUS:
                    speed -= 90;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    SDL_Quit();
                    return 0;
                default:
                    break;
                }
            }
        }

        // right boundary
        if (dest.x + dest.w > 400)
            dest.x = 400 - dest.w;

        // left boundary
        if (dest.x < 0)
            dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > 400)
            dest.y = 400 - dest.h;

        // upper boundary
        if (dest.y < 0)
            dest.y = 0;

        // clears the screen
        SDL_RenderClear(rend);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);

        // calculates to 60 fps
        SDL_Delay(400 / 60);
    }

    // destroy renderer
    SDL_DestroyRenderer(rend);

    // destroy window
    SDL_DestroyWindow(win);

    // close SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}

void initWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initalizing SDL: %s\n", SDL_GetError());
    }
    win = SDL_CreateWindow("Territory War", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    render_flags = SDL_RENDERER_ACCELERATED;
    rend = SDL_CreateRenderer(win, -1, render_flags);
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    SDL_RenderClear(rend);
    dest.w = 50;
    dest.h = 50;
    dest.x = (400 - dest.w) / 2;
    dest.y = (400 - dest.h) / 2;
    SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
    SDL_RenderFillRect(rend, &dest);
    SDL_RenderPresent(rend);
}