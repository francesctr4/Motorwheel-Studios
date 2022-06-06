#pragma once

#include "Module.h"
#include "ModulePlayer.h"
#include "SceneGamePhase.h"
#include "SceneCourtElements.h"
#include "ModuleFonts.h"
#include "ModuleParticles.h"
#include "SceneSelectCourt.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class ModuleScore : public Module
{
public:
	//Constructor
	ModuleScore(bool startEnabled);

	//Destructor
	~ModuleScore();

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

	SDL_Texture* PurpleScoreBase;
	SDL_Texture* PurpleScoreNumbers;
	SDL_Texture* ScorePanel;

	Uint32 startTimerScore;
	Uint32 stopTimerScore;

	bool showScore;
	bool showScoreEndSet;

	int scoreP1;
	int scoreP2;

	bool scored;

	int mapSelection;

	bool arbit_throw_disk_player2;

};
