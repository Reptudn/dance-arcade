#include "engine.hpp"

static void init()
{
}

static void destroy()
{
}

static void on_set_as_curr_scene()
{
}

static void update(SDL_Event &event)
{
    std::cout << "Home scene update function called." << std::endl;
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