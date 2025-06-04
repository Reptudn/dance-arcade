#include "engine.hpp"
#include "utils.hpp"

Scene *no_scene(Engine &engine)
{
    Scene *no_scene = new Scene("No Scene", nullptr, nullptr, nullptr, nullptr);
    SDL_Texture *text = engine.load_text("No Scene Loaded", 24);

    int tex_w = 0, tex_h = 0;
    Vector2 center;
    SDL_QueryTexture(text, NULL, NULL, &tex_w, &tex_h);
    center = utils::transform::get_screen_center(SCREEN_WIDTH, SCREEN_HEIGHT, tex_w, tex_h);

    no_scene->ui.emplace_back("No Scene Text", text, center.x, center.y, tex_w, tex_h, 0);
    return no_scene;
}
