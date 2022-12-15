#include <iostream>
#include <SDL.h>
#include <World.h>
#include <time.h>

#define NORMAL_MODE
#ifdef NORMAL_MODE

SDL_Window* win;
SDL_Renderer* rend;
Uint32 render_flags;
World world;
Layout map;
bool isPaused = false;
bool isDebug = false;
int fps_curr;
int sec;
const int fps_set = 60;
int time_limit;
int sim_mode;

bool End();
bool InitMap();
bool InitWindow();
void InitSim();
void SetSimulationMode();
void Information();

int main(int argc, char* argv[])
{
    if (InitMap())
    {
        int close = 0;
        while (!close && !End()) {
            if (!isPaused)
            {
                fps_curr = world.Tick(fps_curr);
                if (fps_curr == fps_set)
                {
                    sec++;
                    if (sec % 45 == 0)
                    {
                        world.SpawnNewBalls();
                    }
                    Information();
                    fps_curr = 0;
                }
            }
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {

                case SDL_QUIT:
                    close = 1;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_KP_PLUS:
                    case SDL_SCANCODE_UP:
                        if (isDebug)
                            world.SpawnNewBalls();
                        break;
                    case SDL_SCANCODE_KP_MINUS:
                    case SDL_SCANCODE_DOWN:
                        break;
                    case SDL_SCANCODE_SPACE:
                        isPaused = !isPaused;
                        break;
                    case SDL_SCANCODE_R:
                        InitWindow();
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        close = 1;
                        break;
                    default:
                        break;
                    }
                }
            }
            SDL_Delay(map.Height() / fps_set);
        }
    }
    SDL_DestroyRenderer(rend);

    SDL_DestroyWindow(win);

    SDL_Quit();

    return EXIT_SUCCESS;
}

bool End()
{
    if (sim_mode == 0)
    {
        return world.Ended();
    }
    else
    {
        return sec > time_limit;
    }
}

bool InitMap()
{
    srand(time(NULL));
    std::string n[4] = {"1","2","3","4"};
    std::string mapFile = "Map" + n[rand() % 4] + ".txt";

    map = Layout(mapFile);
    isPaused = false;

    return true && InitWindow();
}

bool InitWindow()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initalizing SDL: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        win = SDL_CreateWindow("Territory Wars", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, map.Height(), map.Width(), SDL_WINDOW_SHOWN);
        if (win == NULL)
        {
            printf("error initalizing SDL: %s\n", SDL_GetError());
            return false;
        }
    }
    InitSim();
    return success;
}

void InitSim()
{
    fps_curr = 0;
    sec = 0;
    SetSimulationMode();
    render_flags = SDL_RENDERER_ACCELERATED;
    rend = SDL_CreateRenderer(win, -1, render_flags);
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    world = World(rend, map);
}

void SetSimulationMode()
{
    sim_mode = rand() % 3;
    std::cout << "Simulation mode selected: ";
    switch (sim_mode)
    {
    case 0:
        std::cout << "last man standing" << std::endl;
        break;
    case 1:
        std::cout << "time limit" << std::endl;
        time_limit = 480;
        break;
    case 2:
        std::cout << "blitz" << std::endl;
        time_limit = 120;
        break;
    }
}

void Information()
{
    std::cout << sec << " seconds have passed since running.";
    if (sim_mode > 0)
    {
        int minutes = (time_limit - sec) / 60;
        int seconds = (time_limit - sec) % 60;
        std::cout << "Time remaining: " << minutes << ":" << seconds;
    }
    std::cout << std::endl;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Build from file")
{
    Layout map = Layout("Map1.txt");
    CHECK((map.Height() > 0 && map.Width() > 0 && map.Controllers() == 8));
    map = Layout("Map2.txt");
    CHECK((map.Height() > 0 && map.Width() > 0 && map.Controllers() == 4));
    map = Layout("Map3.txt");
    CHECK((map.Height() > 0 && map.Width() > 0 && map.Controllers() == 4));
    map = Layout("Map4.txt");
    CHECK((map.Height() > 0 && map.Width() > 0 && map.Controllers() == 4));
}

TEST_CASE("Generate world")
{
    Layout map = Layout("Map1.txt");
    World world = World(map);
    CHECK(world.TileCount() == 1600);
    CHECK(world.GetDynamicObjects().size() == 24);
    CHECK(!world.Ended());
}

TEST_CASE("Add new objects")
{
    Layout map = Layout("Map1.txt");
    World world = World(map);

    CHECK(world.GetDynamicObjects().size() == 24);
    world.SpawnNewBalls();
    CHECK(world.GetDynamicObjects().size() == 32);
    world.AddDynamicObject(new Interactable(1633,Vector2(400,400),world.GetControllers().at(1),circle,20));
    CHECK(world.GetDynamicObjects().size() == 33);
    world.AddDynamicObject(new Interactable(1634, Vector2(420, 420), world.GetControllers().at(1), circle, 20));
    CHECK(world.GetDynamicObjects().size() == 34);
}

TEST_CASE("Create collision between two balls")
{
    Layout map = Layout("Map1.txt");
    World world = World(map);
    world.AddDynamicObject(new Interactable(1625, Vector2(400, 400), world.GetControllers().at(1), circle, 20));
    world.AddDynamicObject(new Interactable(1626, Vector2(420, 420), world.GetControllers().at(1), circle, 20));
    Collision c;
    CHECK(world.GetDynamicObjects().at(24).get().Intersects(world.GetDynamicObjects().at(25).get(), c));
    CHECK(c.GetVelocity().Length() > 0);
    Collision d;
    CHECK(world.GetDynamicObjects().at(25).get().Intersects(world.GetDynamicObjects().at(24).get(), d));
    CHECK(d.GetVelocity().Length() > 0);
    CHECK(c.GetVelocity().Length() == d.GetVelocity().Length());
}

TEST_CASE("Don't create collision between two balls")
{
    Layout map = Layout("Map1.txt");
    World world = World(map);
    world.AddDynamicObject(new Interactable(1625, Vector2(200, 200), world.GetControllers().at(1), circle, 20));
    world.AddDynamicObject(new Interactable(1626, Vector2(400, 400), world.GetControllers().at(1), circle, 20));
    Collision c;
    CHECK(!world.GetDynamicObjects().at(24).get().Intersects(world.GetDynamicObjects().at(25).get(), c));
    CHECK(c.GetVelocity().Length() == 0);
}

TEST_CASE("End of simulation")
{
    Layout map = Layout("Map2.txt");
    World world = World(map);
    CHECK(world.Tick(0) == 1);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            world.GetControllers().at(i).get().LoseACore();
        }
    }
    world.CheckControllers();
    for (int i = 0; i < 4; ++i)
    {
        CHECK(world.GetControllers().at(i).get().GetNumberOfCores() < 4);
    }
    CHECK(world.Ended());
}
#endif