#include "engine.hpp"
#include "utils.hpp"

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
    // std::cout << "Home scene update function called." << std::endl;
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

    int tex_w = 0, tex_h = 0;
    Vector2 center;

    SDL_Texture *logo = engine.load_texture("../assets/images/start_screen_logo.png");
    SDL_Texture *background = engine.load_texture("../assets/background/home_background.png");
    SDL_Texture *text = engine.load_text("Press anything to continue...", 24);

    SDL_QueryTexture(logo, NULL, NULL, &tex_w, &tex_h);
    center = utils::transform::get_screen_center(SCREEN_WIDTH, SCREEN_HEIGHT, tex_w, tex_h);
    home->ui.emplace_back(
        "logo",
        logo,
        center.x, center.y - 100, tex_w, tex_h, 0);

    home->background.emplace_back(
        "home_background",
        background,
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    SDL_QueryTexture(text, NULL, NULL, &tex_w, &tex_h);
    center = utils::transform::get_screen_center(SCREEN_WIDTH, SCREEN_HEIGHT, tex_w, tex_h);
    home->ui.emplace_back(
        "ui elem",
        text,
        center.x, center.y + 100, tex_w, tex_h, 0);

    return home;
}