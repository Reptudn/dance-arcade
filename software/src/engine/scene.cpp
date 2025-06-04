#include "engine.hpp"
#include "utils.hpp"

void Engine::load_scene(Scene *scene)
{
	if (!scene)
	{
		utils::log::error("Could not load Scene because its null");
		return;
	}

	if (scene->loaded || scenes.find(scene->title) != scenes.end())
	{
		utils::log::info("Scene " + scene->title + " already exists, reusing it.");
		current_scene = scenes[scene->title];
		return;
	}

	utils::log::info("Loading Scene " + scene->title + "...");
	scenes[scene->title] = scene;
	scene->loaded = true;
	utils::log::info("Loaded Scene " + scene->title + "!");
	if (scene->init)
	{
		utils::log::debug("Calling init function for Scene " + scene->title + "...");
		scene->init();
		utils::log::debug("Init function for Scene " + scene->title + " called successfully.");
	}
	else
		utils::log::warning("Scene " + scene->title + " has no init function, skipping.");
}

void Engine::set_current_scene(std::string name)
{
	if (scenes.find(name) == scenes.end())
	{
		utils::log::error("Could not set current Scene because it does not exist: " + name);
		return;
	}

	Scene *scene = scenes[name];
	if (!scene->loaded)
	{
		utils::log::error("Scene " + scene->title + " is not loaded, cannot set as current scene.");
		return;
	}

	current_scene = scene;
	utils::log::info("Set current Scene to: " + scene->title);

	if (scene->on_set_as_curr_scene)
	{
		utils::log::info("Running on set as current scene function for: " + scene->title);
		scene->on_set_as_curr_scene();
		utils::log::info("Ran on set as current scene function for: " + scene->title);
	}
	else
		utils::log::info("Scene has no on set as current scene function: " + scene->title);
}

void Engine::unload_scene(Scene *scene)
{
	if (!scene)
	{
		utils::log::error("Could not unload Scene because its null");
		return;
	}

	if (!scene->loaded)
	{
		utils::log::warning("Scene " + scene->title + " is not loaded, nothing to unload.");
		return;
	}

	utils::log::info("Unloading Scene " + scene->title + "...");

	std::cout << scene->title << " has " << scene->background.size() << " background textures, "
			  << scene->scene.size() << " scene textures, and "
			  << scene->ui.size() << " ui textures." << std::endl;

	if (scene->destroy)
	{
		utils::log::debug("Calling destroy function for Scene " + scene->title + "...");
		scene->destroy();
		utils::log::debug("Destroy function for Scene " + scene->title + " called successfully.");
	}
	else
		utils::log::warning("Scene " + scene->title + " has no destroy function, skipping.");

	utils::log::debug("Unloading background textures...");
	for (SceneObject obj : scene->background)
	{
		auto tex = obj.texture;
		if (tex == nullptr)
			continue;
		unload_texture(tex);
	}

	utils::log::debug("Unloading scene textures...");
	for (SceneObject obj : scene->scene)
	{
		auto tex = obj.texture;
		if (tex == nullptr)
			continue;
		unload_texture(tex);
	}

	utils::log::debug("Unloading ui textures...");
	for (SceneObject obj : scene->ui)
	{
		auto tex = obj.texture;
		if (tex == nullptr)
			continue;
		unload_texture(tex);
	}
	utils::log::debug("Unloaded all textures for Scene: " + scene->title + "!");

	if (current_scene == scene)
		current_scene = nullptr;
	if (scenes[scene->title])
		scenes.erase(scene->title);

	// XXX: probably memory leaking here beause i dont delete as of now
	// delete scene;
	utils::log::info("Unloaded Scene " + scene->title + "!");
}