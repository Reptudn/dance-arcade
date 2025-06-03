#include "engine.hpp"

void Engine::load_scene(Scene *scene)
{
	(void)scene;
}
void Engine::unload_scene(Scene *scene)
{
	if (!scene)
		return;

	current_scene = nullptr;
}