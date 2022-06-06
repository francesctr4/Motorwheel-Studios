#pragma once

#include "Module.h"
#include "Animation.h"
#include "ModuleFonts.h"

struct SDL_Texture;

class SceneSelectPlayer : public Module
{
public:
	//Constructor
	SceneSelectPlayer(bool startEnabled);

	//Destructor
	~SceneSelectPlayer();

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
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* playerSelection = nullptr;

	SDL_Rect playerSprite1;
	SDL_Rect playerSprite2;

	int iteratorY[3];
	int characterP1;
	int characterP2;

	bool player1_selected;
	bool player2_selected;

	uint selectFx = 0;
	uint moveUI = 0;

	uint HiromiSelected = 0;
	uint JordiSelected = 0;
	uint GarySelected = 0;

	SDL_Texture* timer = nullptr;

	Animation* currentAnimation = nullptr;

	Animation time;

	Uint32 start;
	Uint32 stop;

	Uint32 startTimer;
	Uint32 stopTimer;

	Uint32 startTimerPlayerSelection;
	Uint32 stopTimerPlayerSelection;

	bool both_selected_once;

};

