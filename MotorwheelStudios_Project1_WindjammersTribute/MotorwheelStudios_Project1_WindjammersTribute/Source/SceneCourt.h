#ifndef __SCENE_COURT_H__
#define __SCENE_COURT_H__

#include "Module.h"
#include "Animation.h"
#include "SceneSelectCourt.h"
#include "SceneGamePhase.h"
#include "SceneCourtElements.h"
#include "ModuleScore.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class SceneCourt : public Module
{
public:
	//Constructor
	SceneCourt(bool startEnabled);

	//Destructor
	~SceneCourt();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp() override;

public:
	
	// The scene sprite sheet loaded into an SDL_Texture

	int mapSelection;

	Animation* currentAnimation = nullptr;

	SDL_Texture* BeachSpritesheet = nullptr;
	SDL_Texture* BeachWalls = nullptr;
	SDL_Texture* BeachNet = nullptr;
	Animation Beach;

	SDL_Texture* ConcreteSpritesheet = nullptr;
	SDL_Texture* ConcreteWalls = nullptr;
	SDL_Texture* ConcreteNet = nullptr;
	Animation Concrete;

	SDL_Texture* StadiumSpritesheet = nullptr;
	SDL_Texture* StadiumWalls = nullptr;
	SDL_Texture* StadiumNet = nullptr;
	Animation Stadium;

	SDL_Texture* beachUpWallPNG = nullptr;
	Animation beachUpWall;

	SDL_Texture* concreteUpWallPNG = nullptr;
	Animation concreteUpWall;

	SDL_Texture* stadiumUpWallPNG = nullptr;
	Animation stadiumUpWall;

	Animation* currentAnimationUpWall = nullptr;

	bool activateAnim;

};

#endif