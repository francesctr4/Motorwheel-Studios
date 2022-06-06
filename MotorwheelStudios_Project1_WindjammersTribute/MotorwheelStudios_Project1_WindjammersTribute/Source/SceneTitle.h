#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

#include "Module.h"
#include "Animation.h"
#include "ModuleFonts.h"

struct SDL_Texture;

class SceneTitle : public Module
{
public:
	//Constructor
	SceneTitle(bool startEnabled);

	//Destructor
	~SceneTitle();

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

	SDL_Texture* WindjammersPNG = nullptr;
	
	SDL_Texture* WindjammersPNG_1 = nullptr;
	SDL_Texture* WindjammersPNG_2 = nullptr;
	SDL_Texture* WindjammersPNG_3 = nullptr;
	SDL_Texture* WindjammersPNG_4 = nullptr;

	Animation* currentAnimation = nullptr;

	Animation Windjammers1;
	Animation Windjammers2;
	Animation Windjammers3;
	Animation Windjammers4;

	int scoreFont = -1;

};

#endif