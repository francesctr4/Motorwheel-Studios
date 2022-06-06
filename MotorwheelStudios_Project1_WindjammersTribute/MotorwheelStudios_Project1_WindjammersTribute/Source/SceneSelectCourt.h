#pragma once

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneSelectCourt : public Module
{
public:
	//Constructor
	SceneSelectCourt(bool startEnabled);

	//Destructor
	~SceneSelectCourt();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool CleanUp() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture

	SDL_Texture* iterator[3];
	int map;

	SDL_Texture* beach = nullptr;
	SDL_Texture* concrete = nullptr;
	SDL_Texture* stadium = nullptr;

	SDL_Texture* titulos = nullptr;

	uint selectFx = 0;
	uint moveUI = 0;

	SDL_Texture* timer = nullptr;

	Animation* currentAnimation = nullptr;

	Animation time;

	Uint32 start;
	Uint32 stop;

	bool map_selected;

	Uint32 startTimerMapSelection;
	Uint32 stopTimerMapSelection;

};

