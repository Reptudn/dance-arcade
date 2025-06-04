#include "engine.hpp"

Scene *no_scene(Engine &engine)
{
    Scene *no_scene = new Scene("No Scene", nullptr, nullptr, nullptr, nullptr);
    no_scene->background.push_back(engine.load_texture("assets/backgrounds/no_scene_background.png"));
    no_scene->scene.push_back(engine.load_texture("assets/scenes/no_scene_scene.png"));
    no_scene->ui.push_back(engine.load_texture("assets/ui/no_scene_ui.png"));
    return no_scene;
}
