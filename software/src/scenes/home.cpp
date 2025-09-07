#include "engine.hpp"
#include "utils.hpp"
#include "scenes.hpp"
#include <game.hpp>

static void init(Engine &engine)
{
    engine.load_music_audio("../assets/songs/start_screen.mp3", "home_background_music");
    engine.load_chunk_audio("../assets/sounds/random.mp3", "random");
    engine.load_chunk_audio("../assets/sounds/thats_ddr.mp3", "thats_ddr");
}

static void destroy(Engine &engine)
{
    engine.unload_sound("home_background_music");
    engine.unload_sound("random");
    engine.unload_sound("thats_ddr");
}

static void on_set_as_curr_scene(Engine &engine)
{
    engine.play_sound("thats_ddr", 0);
    engine.play_sound("home_background_music", -1);
}

static void on_unset_as_curr_scene(Engine &engine)
{
    engine.stop_playing("home_background_music");
}

static void update(Engine &engine, SDL_Event &event)
{
    (void)event;
    // std::cout << "Home scene update function called." << std::endl;
    if (engine.state[SDL_SCANCODE_ESCAPE])
    {
        engine.running = false;
        return;
    }

    if (event.key.keysym.scancode == SDL_SCANCODE_X)
    {
        engine.play_sound("random", 0);
        return;
    }

    if (event.type == SDL_KEYDOWN)
    {
        // load song selection scene
        engine.load_scene(song_select_scene(engine));
        engine.set_current_scene("Song Select");
        return;
    }
}

Scene *home_scene(Engine &engine)
{
    Scene *home = new Scene("Home", update, init, destroy, on_set_as_curr_scene, on_unset_as_curr_scene);

    int tex_w = 0, tex_h = 0;
    Vector2 center;

    SDL_Texture *logo = engine.load_texture("../assets/images/start_screen_logo.png");
    SDL_Texture *background = engine.load_texture("../assets/background/home_background.jpg");
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