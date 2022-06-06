#pragma once

#include "Module.h"
#include "Animation.h"
#include "SceneSelectPlayer.h"
#include "Application.h"

struct SDL_Texture;

class SceneVersus : public Module
{
public:
	//Constructor
	SceneVersus(bool startEnabled);

	//Destructor
	~SceneVersus();

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

	int player1_selection;
	int player2_selection;

	SDL_Texture* HiromiMitaVS_left = nullptr;
	SDL_Texture* HiromiMitaVS_right = nullptr;

	SDL_Texture* JapanVS_left = nullptr;
	SDL_Texture* JapanVS_right = nullptr;

	SDL_Texture* JordiCostaVS_left = nullptr;
	SDL_Texture* JordiCostaVS_right = nullptr;

	SDL_Texture* SpainVS_left = nullptr;
	SDL_Texture* SpainVS_right = nullptr;

	SDL_Texture* GaryScottVS_left = nullptr;
	SDL_Texture* GaryScottVS_right = nullptr;

	SDL_Texture* UsaVS_left = nullptr;
	SDL_Texture* UsaVS_right = nullptr;

	SDL_Texture* VS = nullptr;

	//Background

	SDL_Texture* VersusVS = nullptr;
	Animation* currentAnimation = nullptr;
	Animation Versus;

};

