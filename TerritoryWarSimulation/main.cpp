#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <World.h>
#include <time.h>
#include <Layout.h>

SDL_Window* win;
SDL_Renderer* rend;
Uint32 render_flags;
World world;
const Layout map = Layout("Map1.txt");
int fps_curr;
int sec;
const int fps_set = 60;

bool initWindow();

int main(int argc, char* argv[])
{
    if (initWindow())
    {
        srand(time(NULL));
        render_flags = SDL_RENDERER_ACCELERATED;
        rend = SDL_CreateRenderer(win, -1, render_flags);
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        IMG_Init(IMG_INIT_PNG);
        world = World(rend, map);

        int close = 0;
        while (!close) {
            fps_curr = world.Tick(fps_curr);
            if (fps_curr == fps_set)
            {
                sec++;
                if (sec % 30 == 0)
                {
                    world.SpawnNewBalls();
                }
                fps_curr = 0;
                std::cout << sec << " seconds have passed since running." << std::endl;
            }
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {

                case SDL_QUIT:
                    // handling of close button
                    close = 1;
                    break;

                case SDL_KEYDOWN:
                    // keyboard API for key pressed
                    switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_KP_PLUS:
                    case SDL_SCANCODE_UP:
                        break;
                    case SDL_SCANCODE_KP_MINUS:
                    case SDL_SCANCODE_DOWN:
                        break;
                    case SDL_SCANCODE_SPACE:
                        world.SpawnNewBalls();
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        SDL_Quit();
                        return 0;
                    default:
                        break;
                    }
                }
            }
            // calculates to 60 fps
            SDL_Delay(map.Height / fps_set);
        }
        IMG_Quit();

        // destroy renderer
        SDL_DestroyRenderer(rend);

        // destroy window
        SDL_DestroyWindow(win);

        // close SDL
        SDL_Quit();

        return EXIT_SUCCESS;
    }
}

bool initWindow()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initalizing SDL: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        win = SDL_CreateWindow("Territory Wars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, map.Height, map.Width, SDL_WINDOW_SHOWN);
        if (win == NULL)
        {
            printf("error initalizing SDL: %s\n", SDL_GetError());
            success = false;
        }
    }
    fps_curr = 0;
    return success;
}