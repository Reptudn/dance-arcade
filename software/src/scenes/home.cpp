#include "engine.hpp"

static void init(Engine &engine)
{
    (void)engine;
}

static void destroy(Engine &engine)
{
    (void)engine;
}

static void on_set_as_curr_scene(Engine &engine)
{
    (void)engine;
}

static void update(Engine &engine, SDL_Event &event)
{
    (void)event;
    std::cout << "Home scene update function called." << std::endl;
    if (engine.state[SDL_SCANCODE_ESCAPE])
    {
        std::cout << "Escape key held!" << std::endl;
    }

    if (engine.state[SDL_SCANCODE_SPACE])
    {
        std::cout << "Space key held!" << std::endl;
    }

    if (engine.state[SDL_SCANCODE_A])
    {
        std::cout << "A key held!" << std::endl;
    }
    if (engine.state[SDL_SCANCODE_S])
    {
        std::cout << "S key held!" << std::endl;
    }

    if (engine.state[SDL_SCANCODE_J])
    {
        std::cout << "J key held!" << std::endl;
    }

    if (engine.state[SDL_SCANCODE_K])
    {
        std::cout << "K key held!" << std::endl;
    }
}

Scene *home_scene(Engine &engine)
{
    Scene *home = new Scene("Home", update, init, destroy, on_set_as_curr_scene);

    home->background.emplace_back(
        "background picture",
        engine.load_texture("../assets/background/home_ui.png"));

    home->ui.emplace_back(
        "ui elem",
        engine.load_text("Home Scene", 24));

    return home;
}