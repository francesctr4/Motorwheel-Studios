#pragma once

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneNeoGeo : public Module
{
public:
	//Constructor
	SceneNeoGeo(bool startEnabled);

	//Destructor
	~SceneNeoGeo();

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

	SDL_Texture* NeoGeoPNG_1 = nullptr;
	SDL_Texture* NeoGeoPNG_2 = nullptr;

	Animation* currentAnimation = nullptr;

	Animation NeoGeo1;
	Animation NeoGeo2;

};
