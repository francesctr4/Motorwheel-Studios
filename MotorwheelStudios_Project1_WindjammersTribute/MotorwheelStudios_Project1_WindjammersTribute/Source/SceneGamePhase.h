#pragma once

#include "Module.h"
#include "Animation.h"
#include "ModuleScore.h"
#include "sceneSelectPlayer.h"
#include "sceneSelectCourt.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class SceneGamePhase : public Module
{
public:
	//Constructor
	SceneGamePhase(bool startEnabled);

	//Destructor
	~SceneGamePhase();

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

	enum class Game_Phase {

		BEFORE_SET_1,
		SET_1,
		SET_1_to_2,
		SET_1_to_FINAL,
		SET_2,
		SET_2_to_FINAL,
		SET_FINAL,
		SET_FINAL_to_SUDDEN_DEATH,
		SUDDEN_DEATH,
		GAME_RESULT
		
	};

private:

	Game_Phase state;

	// The scene sprite sheet loaded into an SDL_Texture

public:

	SDL_Texture* SetCounts = nullptr;

	SDL_Texture* number0_left = nullptr;
	SDL_Texture* number1_left = nullptr;
	SDL_Texture* number2_left = nullptr;
	SDL_Texture* number3_left = nullptr;

	SDL_Texture* number0_right = nullptr;
	SDL_Texture* number1_right = nullptr;
	SDL_Texture* number2_right = nullptr;
	SDL_Texture* number3_right = nullptr;

	SDL_Texture* timer = nullptr;

	Animation* currentAnimation = nullptr;

	Animation time;
	Animation time_suddendeath;

	Uint32 startTimer;
	Uint32 stopTimer;

	Uint32 startSetTimer;
	Uint32 stopSetTimer; 
	bool showSet;
	bool showSet1;

	bool player1_won_set1;
	bool player1_won_set2;
	bool player1_won_setfinal;
	bool player1_won_suddendeath;

	bool player2_won_set1;
	bool player2_won_set2;
	bool player2_won_setfinal;
	bool player2_won_suddendeath;

	bool setfinal_reached;
	bool suddendeath_reached;
	bool DrawGame;

	SDL_Texture* player1_winsPNG = nullptr;
	SDL_Texture* player2_winsPNG = nullptr;
	SDL_Texture* draw_game = nullptr;

	SDL_Texture* character1_winning = nullptr;
	SDL_Texture* character1_losing = nullptr;

	SDL_Texture* character2_winning = nullptr;
	SDL_Texture* character2_losing = nullptr;

	SDL_Texture* set1 = nullptr;
	SDL_Texture* set2 = nullptr;
	SDL_Texture* setfinal = nullptr;
	SDL_Texture* suddendeath = nullptr;
	SDL_Texture* gameOver = nullptr;

	int player1_selection;
	int player2_selection;

	bool player1_wins;
	bool player2_wins;

	Uint32 startTimerMusic;
	Uint32 stopTimerMusic;

	uint whistle = 0;

	uint set = 0;
	uint getReady = 0;
	uint gameSet = 0;
	bool set_said;
	bool getReady_said;
	bool gameSet_said;

	bool playingCourtMusic;
	bool playingEndingMusic;
	bool endgame;

	int mapSelection;

	Uint32 startTimerChangingSet;
	Uint32 stopTimerChangingSet;

	bool showResults;
	bool showGameOver;

	SDL_Texture* points = nullptr;

	bool betweenSets;

	Uint32 startTimerArbitThrow;
	Uint32 stopTimerArbitThrow;

};

