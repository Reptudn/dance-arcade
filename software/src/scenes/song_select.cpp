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
	(void)engine;

	std::cout << "Song select update" << std::endl;

	if (engine.state[SDL_SCANCODE_Q])
	{
		engine.set_current_scene("Home");
	}
}

Scene *song_select_scene(Engine &engine)
{
	Scene *song_select = new Scene("Song Select", update, init, destroy, on_set_as_curr_scene);

	int tex_w = 0, tex_h = 0;
	Vector2 center;

	SDL_Texture *background = engine.load_texture("../assets/background/home_background.png");
	SDL_Texture *text = engine.load_text("Song Select", 24);

	song_select->background.emplace_back(
		"home_background",
		background,
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	SDL_QueryTexture(text, NULL, NULL, &tex_w, &tex_h);
	center = utils::transform::get_screen_center(SCREEN_WIDTH, SCREEN_HEIGHT, tex_w, tex_h);
	song_select->ui.emplace_back(
		"song_select_text",
		text,
		center.x, center.y, tex_w, tex_h, 0);

	return song_select;
}