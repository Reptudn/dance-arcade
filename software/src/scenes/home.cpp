#include "engine.hpp"

static void update()
{
    std::cout << "Home scene update function called." << std::endl;
}

Scene *home_scene(Engine &engine)
{
    Scene *home = new Scene("Home", update);
    // home->background.push_back(engine.load_texture("../assets/background/home_background.png"));
    home->ui.push_back(engine.load_texture("../assets/background/home_ui.png"));
    home->ui.push_back(engine.load_text("Home Scene", 24));
    return home;
}