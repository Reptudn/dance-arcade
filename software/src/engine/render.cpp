#include "engine.hpp"

void render_background() {}
void render_ui() {}
void render_scene() {}

void Engine::render()
{
	render_background();
	render_scene();
	render_ui();
}
