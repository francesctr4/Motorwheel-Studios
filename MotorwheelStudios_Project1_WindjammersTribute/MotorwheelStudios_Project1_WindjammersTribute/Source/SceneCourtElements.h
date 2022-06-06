#pragma once

#include "Module.h"
#include "Animation.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneSelectCourt.h"

struct SDL_Texture;

class SceneCourtElements : public Module
{
public:
	//Constructor
	SceneCourtElements(bool startEnabled);

	//Destructor
	~SceneCourtElements();

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

	SDL_Texture* beachDownWallPNG = nullptr;
	Animation beachDownWall;

	SDL_Texture* concreteDownWallPNG = nullptr;
	Animation concreteDownWall;

	SDL_Texture* stadiumDownWallPNG = nullptr;
	Animation stadiumDownWall;

	Animation* currentAnimationDownWall = nullptr;

	SDL_Texture* goals = nullptr;

	SDL_Texture* marcador = nullptr;

	bool activateAnim;

	int mapSelection;

	SDL_Texture* arbit = nullptr;

	bool arbit_looking_left;

	bool arbit_looking_center;

	bool arbit_looking_right;

	bool arbit_hand_player1;

	bool arbit_hand_player2;

	Uint32 startTimerArbit;
	Uint32 stopTimerArbit;

	Uint32 startTimerArbitThrowing;
	Uint32 stopTimerArbitThrowing;

	bool arbit_throwing_left;
	bool arbit_throwing_right;

};

