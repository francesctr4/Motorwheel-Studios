#include "SceneGamePhase.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

SceneGamePhase::SceneGamePhase(bool startEnabled) : Module(startEnabled)
{

	for (int i = 0; i < 2; i++) {

		for (int j = 0; j < 16; j++) {

			time.PushBack({ 16 * j, 16 * i, 15, 15 });

		}

	}

	time.loop = false;
	time.speed = (1.0f / 60.0f);

	for (int i = 0; i < 2; i++) {

		if (i == 0) {

			for (int j = 10; j < 16; j++) {

				time_suddendeath.PushBack({ 16 * j, 16 * i, 15, 15 });

			}

		}
		else {

			for (int j = 0; j < 16; j++) {

				time_suddendeath.PushBack({ 16 * j, 16 * i, 15, 15 });

			}

		}

	}

	time_suddendeath.loop = false;
	time_suddendeath.speed = (1.0f / 60.0f);

}

SceneGamePhase::~SceneGamePhase()
{

}

// Load assets
bool SceneGamePhase::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	mapSelection = App->sceneSelectCourt->map;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	timer = App->textures->Load("Assets/Sprites/timer.png");

	currentAnimation = &time;

	state = Game_Phase::BEFORE_SET_1;

	SetCounts = App->textures->Load("Assets/Sprites/SetCounts.png");

	number0_left = App->textures->Load("Assets/Sprites/n0left.png");
	number1_left = App->textures->Load("Assets/Sprites/n1left.png");
	number2_left = App->textures->Load("Assets/Sprites/n2left.png");
	number3_left = App->textures->Load("Assets/Sprites/n3left.png");

	number0_right = App->textures->Load("Assets/Sprites/n0right.png");
	number1_right = App->textures->Load("Assets/Sprites/n1right.png");
	number2_right = App->textures->Load("Assets/Sprites/n2right.png");
	number3_right = App->textures->Load("Assets/Sprites/n3right.png");

	player1_wins = false;
	player2_wins = false;

	player1_selection = App->sceneSelectPlayer->characterP1;
	player2_selection = App->sceneSelectPlayer->characterP2;

	player1_winsPNG = App->textures->Load("Assets/Sprites/Player1Win.png");
	player2_winsPNG = App->textures->Load("Assets/Sprites/Player2Win.png");
	draw_game = App->textures->Load("Assets/Sprites/DrawGame.png");

	switch (player1_selection) {

	case 0: // Hiromi left

		character1_winning = App->textures->Load("Assets/Sprites/HMitaWin.png");
		character1_losing = App->textures->Load("Assets/Sprites/HMitaLose.png");
		break;

	case 1: // Jordi left

		character1_winning = App->textures->Load("Assets/Sprites/JCostaWin.png");
		character1_losing = App->textures->Load("Assets/Sprites/JCostaLose.png");
		break;

	case 2: // Gary left

		character1_winning = App->textures->Load("Assets/Sprites/GScottWin.png");
		character1_losing = App->textures->Load("Assets/Sprites/GScottLose.png");
		break;

	}

	switch (player2_selection) {

	case 0: // Hiromi right

		character2_winning = App->textures->Load("Assets/Sprites/HMita2Win.png");
		character2_losing = App->textures->Load("Assets/Sprites/HMita2Lose.png");
		break;

	case 1: // Jordi right

		character2_winning = App->textures->Load("Assets/Sprites/JCosta2Win.png");
		character2_losing = App->textures->Load("Assets/Sprites/JCosta2Lose.png");
		break;

	case 2: // Gary right

		character2_winning = App->textures->Load("Assets/Sprites/GScott2Win.png");
		character2_losing = App->textures->Load("Assets/Sprites/GScott2Lose.png");
		break;

	}

	set1 = App->textures->Load("Assets/Sprites/Set1.png");
	set2 = App->textures->Load("Assets/Sprites/Set2.png");
	setfinal = App->textures->Load("Assets/Sprites/SetFinal.png");
	suddendeath = App->textures->Load("Assets/Sprites/SuddenDeath.png");
	gameOver = App->textures->Load("Assets/Sprites/GameOver.png");

	showSet = false;
	showSet1 = false;

	startTimer = SDL_GetTicks();

	startSetTimer = SDL_GetTicks();

	startTimerMusic = SDL_GetTicks();

	startTimerChangingSet = SDL_GetTicks();

	startTimerArbitThrow = SDL_GetTicks();

	player1_won_set1 = false;
	player1_won_set2 = false;
	player1_won_setfinal = false;
	player1_won_suddendeath = false;

	player2_won_set1 = false;
	player2_won_set2 = false;
	player2_won_setfinal = false;
	player2_won_suddendeath = false;

	setfinal_reached = false;
	suddendeath_reached = false;
	DrawGame = false;

	playingCourtMusic = true;

	playingEndingMusic = false;

	endgame = false;

	whistle = App->audio->LoadFx("Assets/Fx/Whistle.wav");
	set = App->audio->LoadFx("Assets/Fx/Set!.wav");
	getReady = App->audio->LoadFx("Assets/Fx/GetReady!.wav");
	gameSet = App->audio->LoadFx("Assets/Fx/GameSet!.wav");

	set_said = false;
	getReady_said = false;
	gameSet_said = false;

	showResults = false;
	showGameOver = false;

	switch (mapSelection) {

		case 0: // Beach

			points = App->textures->Load("Assets/Sprites/BeachStadiumPoints.png");
			break;

		case 1: // Concrete

			points = App->textures->Load("Assets/Sprites/ConcretePoints.png");
			break;

		case 2: // Stadium

			points = App->textures->Load("Assets/Sprites/BeachStadiumPoints.png");
			break;

	}

	betweenSets = true;

	return ret;
}

Update_Status SceneGamePhase::Update()
{
	stopTimer = SDL_GetTicks();

	stopTimerMusic = SDL_GetTicks();

	stopSetTimer = SDL_GetTicks();

	stopTimerChangingSet = SDL_GetTicks();

	stopTimerArbitThrow = SDL_GetTicks();

	switch (state) {

		case Game_Phase::BEFORE_SET_1:

			if (stopSetTimer - startSetTimer >= 500 && !getReady_said) {

				App->audio->PlayFx(getReady);
				getReady_said = true;

			}

			if (stopSetTimer - startSetTimer <= 2500) {

				showSet1 = true;

			}
			else {

				showSet1 = false;

			}

			if (stopSetTimer - startSetTimer >= 3500) {

				startTimer = SDL_GetTicks();
				App->audio->PlayFx(whistle);

				App->sceneCourtElements->startTimerArbitThrowing = SDL_GetTicks();
				App->sceneCourtElements->arbit_throwing_left = true;

				switch (mapSelection) {

					case 0: // Beach

						App->audio->PlayFx(App->player->throwdisk_normal);

						App->particles->AddParticle(App->particles->disk_upLeftThrow, 131, 176, Collider::Type::PLAYER_SHOT);

						break;

					case 1: // Concrete

						App->audio->PlayFx(App->player->throwdisk_normal);

						App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);

						break;

					case 2: // Stadium

						App->audio->PlayFx(App->player->throwdisk_normal);

						App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);

						break;

				}

				state = Game_Phase::SET_1;

			}

		case Game_Phase::SET_1:

			if ((App->moduleScore->scoreP1 >= 12 || App->moduleScore->scoreP2 >= 12 || (stopTimer - startTimer >= 31000)) && !(App->moduleScore->scoreP1 == App->moduleScore->scoreP2)) {
				
				App->audio->PlayFx(whistle);
				App->audio->PlayMusic("Assets/Music/04_SetClear.ogg", false, 0.0f);
				playingCourtMusic = false;
				startTimerMusic = SDL_GetTicks();

				if (App->moduleScore->scoreP1 > App->moduleScore->scoreP2) {

					player1_won_set1 = true;

					/*App->sceneCourtElements->startTimerArbitSet = SDL_GetTicks();
					App->sceneCourtElements->arbit_hand_player1 = true;*/

				}
				else if (App->moduleScore->scoreP2 > App->moduleScore->scoreP1) {

					player2_won_set1 = true;

					/*App->sceneCourtElements->startTimerArbitSet = SDL_GetTicks();
					App->sceneCourtElements->arbit_hand_player2 = true;*/

				}

				set_said = false;
				getReady_said = false;

				startSetTimer = SDL_GetTicks();
				startTimerChangingSet = SDL_GetTicks();
				state = Game_Phase::SET_1_to_2;

			}
			else if (App->moduleScore->scoreP1 == App->moduleScore->scoreP2 && (stopTimer - startTimer >= 31000)) {
				
				App->audio->PlayFx(whistle);
				App->audio->PlayMusic("Assets/Music/13_DrawSet.ogg", false, 0.0f);
				playingCourtMusic = false;
				startTimerMusic = SDL_GetTicks();

				player1_won_set1 = true;
				player2_won_set1 = true;

				set_said = false;
				getReady_said = false;

				startSetTimer = SDL_GetTicks();
				startTimerChangingSet = SDL_GetTicks();
				state = Game_Phase::SET_1_to_FINAL;

			}

			break;

		case Game_Phase::SET_1_to_2:

			if (stopTimerChangingSet - startTimerChangingSet <= 3000) {

				App->moduleScore->showScoreEndSet = true;

			}
			else {

				App->moduleScore->showScoreEndSet = false;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 2000 && !set_said) {

				App->audio->PlayFx(set);
				set_said = true;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 4000 && !getReady_said) {

				App->audio->PlayFx(getReady);
				getReady_said = true;

			}

			if ((stopTimerMusic - startTimerMusic >= 3000) && !playingCourtMusic) {

				switch (mapSelection) {

				case 0: // Beach

					App->audio->PlayMusic("Assets/Music/08_Flying-Power-Disc-_Beach-Court_.ogg", false, 0.0f);
					break;

				case 1: // Concrete

					App->audio->PlayMusic("Assets/Music/09_You-Got-a-Power-_Concrete-Court_.ogg", false, 0.0f);
					break;

				case 2: // Stadium

					App->audio->PlayMusic("Assets/Music/11_Break Point Champs (Stadium Court).ogg", false, 0.0f);
					break;

				}

				playingCourtMusic = true;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 6000) {

				App->audio->PlayFx(whistle);

				App->moduleScore->scoreP1 = 0;
				App->moduleScore->scoreP2 = 0;

				currentAnimation->Reset();
				startTimer = SDL_GetTicks();

				App->player->position_player1.x = 31;
				App->player->position_player1.y = 78;

				App->player->position_player2.x = SCREEN_WIDTH - App->player->position_player1.x - 23;
				App->player->position_player2.y = App->player->position_player1.y;

				App->sceneCourtElements->startTimerArbitThrowing = SDL_GetTicks();
				App->sceneCourtElements->arbit_throwing_left = true;

				switch (mapSelection) {

				case 0: // Beach

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 131, 176, Collider::Type::PLAYER_SHOT);

					break;

				case 1: // Concrete

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);

					break;

				case 2: // Stadium

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);

					break;

				}

				state = Game_Phase::SET_2;

			}

			break;

		case Game_Phase::SET_1_to_FINAL:

			if (stopTimerChangingSet - startTimerChangingSet <= 3000) {

				App->moduleScore->showScoreEndSet = true;

			}
			else {

				App->moduleScore->showScoreEndSet = false;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 2000 && !set_said) {

				App->audio->PlayFx(set);
				set_said = true;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 4000 && !getReady_said) {

				App->audio->PlayFx(getReady);
				getReady_said = true;

			}

			if ((stopTimerMusic - startTimerMusic >= 3000) && !playingCourtMusic) {

				switch (mapSelection) {

				case 0: // Beach

					App->audio->PlayMusic("Assets/Music/08_Flying-Power-Disc-_Beach-Court_.ogg", false, 0.0f);
					break;

				case 1: // Concrete

					App->audio->PlayMusic("Assets/Music/09_You-Got-a-Power-_Concrete-Court_.ogg", false, 0.0f);
					break;

				case 2: // Stadium

					App->audio->PlayMusic("Assets/Music/11_Break Point Champs (Stadium Court).ogg", false, 0.0f);
					break;

				}

				playingCourtMusic = true;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 6000) {

				App->audio->PlayFx(whistle);

				App->moduleScore->scoreP1 = 0;
				App->moduleScore->scoreP2 = 0;

				currentAnimation->Reset();
				startTimer = SDL_GetTicks();

				App->player->position_player1.x = 31;
				App->player->position_player1.y = 78;

				App->player->position_player2.x = SCREEN_WIDTH - App->player->position_player1.x - 23;
				App->player->position_player2.y = App->player->position_player1.y;

				App->sceneCourtElements->startTimerArbitThrowing = SDL_GetTicks();
				App->sceneCourtElements->arbit_throwing_left = true;

				switch (mapSelection) {

				case 0: // Beach

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 131, 176, Collider::Type::PLAYER_SHOT);

					break;

				case 1: // Concrete

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);

					break;

				case 2: // Stadium

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);

					break;

				}

				state = Game_Phase::SET_FINAL;

			}

			break;

		case Game_Phase::SET_2:

			if ((App->moduleScore->scoreP1 >= 12 || App->moduleScore->scoreP2 >= 12 || (stopTimer - startTimer >= 31000)) && !(App->moduleScore->scoreP1 == App->moduleScore->scoreP2)) {

				App->audio->PlayFx(whistle);

				App->audio->PlayMusic("Assets/Music/04_SetClear.ogg", false, 0.0f);
				playingCourtMusic = false;
				startTimerMusic = SDL_GetTicks();

				if (App->moduleScore->scoreP1 > App->moduleScore->scoreP2) {

					player1_won_set2 = true;

					/*App->sceneCourtElements->startTimerArbitSet = SDL_GetTicks();
					App->sceneCourtElements->arbit_hand_player1 = true;*/

				}
				else if (App->moduleScore->scoreP2 > App->moduleScore->scoreP1) {

					player2_won_set2 = true;

					/*App->sceneCourtElements->startTimerArbitSet = SDL_GetTicks();
					App->sceneCourtElements->arbit_hand_player2 = true;*/

				}

				if ((player1_won_set1 && !player1_won_set2 && !player2_won_set1 && player2_won_set2) || (!player1_won_set1 && player1_won_set2 && player2_won_set1 && !player2_won_set2)) {

					startSetTimer = SDL_GetTicks();
					startTimerChangingSet = SDL_GetTicks();

					set_said = false;
					getReady_said = false;

					state = Game_Phase::SET_2_to_FINAL;

				}
				else if ((player1_won_set1 && player1_won_set2 && !player2_won_set1 && !player2_won_set2) || (!player1_won_set1 && !player1_won_set2 && player2_won_set1 && player2_won_set2)) {

					set_said = false;
					getReady_said = false;

					/*App->sceneCourtElements->startTimerArbitSet = SDL_GetTicks();
					App->sceneCourtElements->arbit_hand_player1 = true;*/

					startTimerChangingSet = SDL_GetTicks();
					state = Game_Phase::GAME_RESULT;

				}

			}
			else if (App->moduleScore->scoreP1 == App->moduleScore->scoreP2 && (stopTimer - startTimer >= 31000)) {

				App->audio->PlayFx(whistle);

				App->audio->PlayMusic("Assets/Music/13_DrawSet.ogg", false, 0.0f);
				playingCourtMusic = false;
				startTimerMusic = SDL_GetTicks();

				player1_won_set2 = true;
				player2_won_set2 = true;

				set_said = false;
				getReady_said = false;

				startTimerChangingSet = SDL_GetTicks();
				state = Game_Phase::GAME_RESULT;

			}

			break;

		case Game_Phase::SET_2_to_FINAL:

			if (stopTimerChangingSet - startTimerChangingSet <= 3000) {

				App->moduleScore->showScoreEndSet = true;

			}
			else {

				App->moduleScore->showScoreEndSet = false;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 2000 && !set_said) {

				App->audio->PlayFx(set);
				set_said = true;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 4000 && !getReady_said) {

				App->audio->PlayFx(getReady);
				getReady_said = true;

			}

			if ((stopTimerMusic - startTimerMusic >= 3000) && !playingCourtMusic) {

				switch (mapSelection) {

				case 0: // Beach

					App->audio->PlayMusic("Assets/Music/08_Flying-Power-Disc-_Beach-Court_.ogg", false, 0.0f);
					break;

				case 1: // Concrete

					App->audio->PlayMusic("Assets/Music/09_You-Got-a-Power-_Concrete-Court_.ogg", false, 0.0f);
					break;

				case 2: // Stadium

					App->audio->PlayMusic("Assets/Music/11_Break Point Champs (Stadium Court).ogg", false, 0.0f);
					break;

				}

				playingCourtMusic = true;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 6000) {

				App->audio->PlayFx(whistle);

				App->moduleScore->scoreP1 = 0;
				App->moduleScore->scoreP2 = 0;

				currentAnimation->Reset();
				startTimer = SDL_GetTicks();

				App->player->position_player1.x = 31;
				App->player->position_player1.y = 78;

				App->player->position_player2.x = SCREEN_WIDTH - App->player->position_player1.x - 23;
				App->player->position_player2.y = App->player->position_player1.y;

				App->sceneCourtElements->startTimerArbitThrowing = SDL_GetTicks();
				App->sceneCourtElements->arbit_throwing_left = true;

				switch (mapSelection) {

				case 0: // Beach

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 131, 176, Collider::Type::PLAYER_SHOT);

					break;

				case 1: // Concrete

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);

					break;

				case 2: // Stadium

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);

					break;

				}

				state = Game_Phase::SET_FINAL;

			}

			break;

		case Game_Phase::SET_FINAL:

			setfinal_reached = true;

			if ((App->moduleScore->scoreP1 >= 12 || App->moduleScore->scoreP2 >= 12 || (stopTimer - startTimer >= 31000)) && !(App->moduleScore->scoreP1 == App->moduleScore->scoreP2)) {

				App->audio->PlayFx(whistle);

				currentAnimation->Reset();
				startTimer = SDL_GetTicks();

				App->audio->PlayMusic("Assets/Music/04_SetClear.ogg", false, 0.0f);
				playingCourtMusic = false;
				startTimerMusic = SDL_GetTicks();

				if (App->moduleScore->scoreP1 > App->moduleScore->scoreP2) {

					player1_won_setfinal = true;

				}
				else if (App->moduleScore->scoreP2 > App->moduleScore->scoreP1) {

					player2_won_setfinal = true;

				}

				set_said = false;
				getReady_said = false;

				startTimerChangingSet = SDL_GetTicks();
				state = Game_Phase::GAME_RESULT;

			}
			else if (App->moduleScore->scoreP1 == App->moduleScore->scoreP2 && (stopTimer - startTimer >= 31000)) {

				App->audio->PlayFx(whistle);

				player1_won_setfinal = true;
				player2_won_setfinal = true;

				App->audio->PlayMusic("Assets/Music/13_DrawSet.ogg", false, 0.0f);
				playingCourtMusic = false;
				startTimerMusic = SDL_GetTicks();

				startTimer = SDL_GetTicks();

				startSetTimer = SDL_GetTicks();
				startTimerChangingSet = SDL_GetTicks();

				set_said = false;
				getReady_said = false;

				state = Game_Phase::SET_FINAL_to_SUDDEN_DEATH;

			}

			break;

		case Game_Phase::SET_FINAL_to_SUDDEN_DEATH:

			if (stopTimerChangingSet - startTimerChangingSet <= 3000) {

				App->moduleScore->showScoreEndSet = true;

			}
			else {

				App->moduleScore->showScoreEndSet = false;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 2000 && !set_said) {

				App->audio->PlayFx(set);
				set_said = true;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 4000 && !getReady_said) {

				App->audio->PlayFx(getReady);
				getReady_said = true;

			}

			if ((stopTimerMusic - startTimerMusic >= 3000) && !playingCourtMusic) {

				switch (mapSelection) {

				case 0: // Beach

					App->audio->PlayMusic("Assets/Music/08_Flying-Power-Disc-_Beach-Court_.ogg", false, 0.0f);
					break;

				case 1: // Concrete

					App->audio->PlayMusic("Assets/Music/09_You-Got-a-Power-_Concrete-Court_.ogg", false, 0.0f);
					break;

				case 2: // Stadium

					App->audio->PlayMusic("Assets/Music/11_Break Point Champs (Stadium Court).ogg", false, 0.0f);
					break;

				}

				playingCourtMusic = true;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 6000) {

				App->audio->PlayFx(whistle);

				App->moduleScore->scoreP1 = 0;
				App->moduleScore->scoreP2 = 0;

				currentAnimation->Reset();
				currentAnimation = &time_suddendeath;

				startTimer = SDL_GetTicks();

				App->player->position_player1.x = 31;
				App->player->position_player1.y = 78;

				App->player->position_player2.x = SCREEN_WIDTH - App->player->position_player1.x - 23;
				App->player->position_player2.y = App->player->position_player1.y;

				App->sceneCourtElements->startTimerArbitThrowing = SDL_GetTicks();
				App->sceneCourtElements->arbit_throwing_left = true;

				switch (mapSelection) {

				case 0: // Beach

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 131, 176, Collider::Type::PLAYER_SHOT);

					break;

				case 1: // Concrete

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);

					break;

				case 2: // Stadium

					App->audio->PlayFx(App->player->throwdisk_normal);

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);

					break;

				}

				state = Game_Phase::SUDDEN_DEATH;

			}

			break;

		case Game_Phase::SUDDEN_DEATH:

			if ((stopTimerMusic - startTimerMusic >= 3000) && !playingCourtMusic) {

				switch (mapSelection) {

				case 0: // Beach

					App->audio->PlayMusic("Assets/Music/08_Flying-Power-Disc-_Beach-Court_.ogg", false, 0.0f);
					break;

				case 1: // Concrete

					App->audio->PlayMusic("Assets/Music/09_You-Got-a-Power-_Concrete-Court_.ogg", false, 0.0f);
					break;

				case 2: // Stadium

					App->audio->PlayMusic("Assets/Music/11_Break Point Champs (Stadium Court).ogg", false, 0.0f);
					break;

				}
		
				playingCourtMusic = true;

			}

			suddendeath_reached = true;

			if ((App->moduleScore->scoreP1 > 1) || (App->moduleScore->scoreP2 > 1) || (stopTimer - startTimer >= 22000)) {

				App->audio->PlayFx(whistle);

				set_said = false;
				getReady_said = false;

				if (App->moduleScore->scoreP1 > App->moduleScore->scoreP2) {

					App->audio->PlayMusic("Assets/Music/04_SetClear.ogg", false, 0.0f);
					playingCourtMusic = false;
					startTimerMusic = SDL_GetTicks();

					player1_won_suddendeath = true;

				}
				else if (App->moduleScore->scoreP2 > App->moduleScore->scoreP1) {


					App->audio->PlayMusic("Assets/Music/04_SetClear.ogg", false, 0.0f);
					playingCourtMusic = false;
					startTimerMusic = SDL_GetTicks();

					player2_won_suddendeath = true;

				}
				else if (App->moduleScore->scoreP1 == 0 && App->moduleScore->scoreP2 == 0) {

					App->audio->PlayMusic("Assets/Music/13_DrawSet.ogg", false, 0.0f);
					playingCourtMusic = false;
					startTimerMusic = SDL_GetTicks();

					DrawGame = true;

				}
				startTimerChangingSet = SDL_GetTicks();
				state = Game_Phase::GAME_RESULT;

			}

			break;

		case Game_Phase::GAME_RESULT:

			if (stopTimerChangingSet - startTimerChangingSet >= 1500 && !set_said) {

				App->audio->PlayFx(set);
				set_said = true;

			}

			if (stopTimerChangingSet - startTimerChangingSet >= 2500 && !gameSet_said) {

				App->audio->PlayFx(gameSet);
				gameSet_said = true;

			}

			if (stopTimerChangingSet - startTimerChangingSet <= 3000) {

				App->moduleScore->showScoreEndSet = true;

			}
			else {

				App->moduleScore->showScoreEndSet = false;
				showResults = true;

			}

			if ((stopTimerMusic - startTimerMusic >= 3000) && !playingCourtMusic) {

				App->audio->PlayMusic("Assets/Music/15_GameOver.ogg", false, 0.0f);
				playingCourtMusic = true;

			}

			if ((stopTimerMusic - startTimerMusic >= 9500) && !playingEndingMusic) {

				App->audio->PlayMusic("Assets/Music/16_EndTheme.ogg", false, 0.0f);
				playingEndingMusic = true;
				showGameOver = true;

			}

			if ((stopTimerMusic - startTimerMusic >= 16000) && !endgame) {

				App->fade->FadeToBlack((Module*)App->sceneCourt, (Module*)App->sceneTitle, 30);
				endgame = true;

			}

			if (player1_won_set1 && player1_won_set2 && !player2_won_set1 && !player2_won_set2) {

				player1_wins = true;

			}
			else if (player1_won_set1 && !player2_won_set1 && player1_won_set2 && player2_won_set2){

				player1_wins = true;

			}
			else if (setfinal_reached && player1_won_setfinal && !player2_won_setfinal) {

				player1_wins = true;

			}
			else if (suddendeath_reached && player1_won_suddendeath && !player2_won_suddendeath) {

				player1_wins = true;

			}

			if (!player1_won_set1 && !player1_won_set2 && player2_won_set1 && player2_won_set2) {

				player2_wins = true;

			}
			else if (!player1_won_set1 && player2_won_set1 && player1_won_set2 && player2_won_set2) {

				player2_wins = true;

			}
			else if (setfinal_reached && !player1_won_setfinal && player2_won_setfinal) {

				player2_wins = true;

			}
			else if (suddendeath_reached && !player1_won_suddendeath && player2_won_suddendeath) {

				player2_wins = true;

			}

			break;
	}

	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN && !player2_wins) {
		
		player1_won_set1 = true;
		player1_won_set2 = true;
		player2_won_set1 = false; 
		player2_won_set2 = false;

		player1_wins = true;

		startTimerChangingSet = SDL_GetTicks();
		startTimerMusic = SDL_GetTicks();

		App->audio->PlayMusic("Assets/Music/04_SetClear.ogg", false, 0.0f);
		playingCourtMusic = false;

		state = Game_Phase::GAME_RESULT;

	}

	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && !player1_wins) {

		player1_won_set1 = false;
		player1_won_set2 = false;
		player2_won_set1 = true;
		player2_won_set2 = true;

		player2_wins = true;

		startTimerChangingSet = SDL_GetTicks();
		startTimerMusic = SDL_GetTicks();

		App->audio->PlayMusic("Assets/Music/04_SetClear.ogg", false, 0.0f);
		playingCourtMusic = false;

		state = Game_Phase::GAME_RESULT;

	}

	if ((stopSetTimer - startSetTimer >= 3000) && (stopSetTimer - startSetTimer <= 5000)) {

		showSet = true;

	}
	else {

		showSet = false;

	}

	if (state != Game_Phase::BEFORE_SET_1 && state != Game_Phase::SET_1_to_2 && state != Game_Phase::SET_1_to_FINAL && state != Game_Phase::SET_2_to_FINAL && state != Game_Phase::SET_FINAL_to_SUDDEN_DEATH && state != Game_Phase::GAME_RESULT) {

		currentAnimation->Update();
		App->player->playersCanMove = true;
		betweenSets = false;

	}
	else {

		startTimerArbitThrow = SDL_GetTicks();

		App->moduleScore->arbit_throw_disk_player2 = false;

		App->player->player1_hasTheDisk = false;
		App->player->player2_hasTheDisk = false;

		App->player->playersCanMove = false;
		betweenSets = true;

	}

	if (stopTimerArbitThrow - startTimerArbitThrow <= 500) {

		App->player->playersCanMove = false;

	}
	else {

		App->player->playersCanMove = true;

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneGamePhase::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(timer, 144, 13, &rect);

	SDL_Rect rect2 = { 168, 0, 29, 3 };

	switch (state) {

		case Game_Phase::BEFORE_SET_1:

			if (showSet1) {

				App->render->Blit(points, 0, 0, NULL);
				App->render->Blit(set1, 0, 0, NULL);


			}

		case Game_Phase::SET_1:
			
			break;

		case Game_Phase::SET_1_to_2:

			if (showSet) {

				SDL_Rect rect2 = { 168, 0, 29, 3 };

				App->render->Blit(set2, 0, 0, NULL);

			}

			if (App->moduleScore->showScoreEndSet) {

				App->render->Blit(SetCounts, 0, 0, NULL);

				if (player1_won_set1 && !player2_won_set1) {

					App->render->Blit(number1_left, 0, 0, NULL);
					App->render->Blit(number0_right, 0, 0, NULL);

				}
				else if (!player1_won_set1 && player2_won_set1) {

					App->render->Blit(number0_left, 0, 0, NULL);
					App->render->Blit(number1_right, 0, 0, NULL);

				}

			}

			if (player1_won_set1 && !player2_won_set1) {

				App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);

			}
			else if (!player1_won_set1 && player2_won_set1) {

				App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

			}

			break;

		case Game_Phase::SET_1_to_FINAL:

			if (showSet) {

				SDL_Rect rect2 = { 168, 0, 29, 3 };

				App->render->Blit(setfinal, 0, 0, NULL);

			}

			if (App->moduleScore->showScoreEndSet) {

				App->render->Blit(SetCounts, 0, 0, NULL);

				App->render->Blit(number1_left, 0, 0, NULL);
				App->render->Blit(number1_right, 0, 0, NULL);

			}

			App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
			App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

			break;

		case Game_Phase::SET_2:

			if (player1_won_set1 && !player2_won_set1) {

				App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);

			}
			else if (!player1_won_set1 && player2_won_set1) {

				App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

			}

			break;

		case Game_Phase::SET_2_to_FINAL:

			if (showSet) {

				SDL_Rect rect2 = { 168, 0, 29, 3 };

				App->render->Blit(setfinal, 0, 0, NULL);

			}

			if (App->moduleScore->showScoreEndSet) {

				App->render->Blit(SetCounts, 0, 0, NULL);

				App->render->Blit(number1_left, 0, 0, NULL);
				App->render->Blit(number1_right, 0, 0, NULL);

			}

			App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
			App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

			break;

		case Game_Phase::SET_FINAL:

			App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
			App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

			break;

		case Game_Phase::SET_FINAL_to_SUDDEN_DEATH:

			if (showSet) {

				SDL_Rect rect2 = { 168, 0, 29, 3 };

				App->render->Blit(suddendeath, 0, 0, NULL);

			}

			if (App->moduleScore->showScoreEndSet) {

				App->render->Blit(SetCounts, 0, 0, NULL);

				App->render->Blit(number2_left, 0, 0, NULL);
				App->render->Blit(number2_right, 0, 0, NULL);

			}

			App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
			App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

			break;

		case Game_Phase::SUDDEN_DEATH:

			App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
			App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

			break;

		case Game_Phase::GAME_RESULT:

			if (!showGameOver) {

				if (player1_wins) {

					if (showResults) {

						App->render->Blit(character2_losing, 0, 0, NULL);
						App->render->Blit(character1_winning, 0, 0, NULL);
						App->render->Blit(player1_winsPNG, 0, 0, NULL);

					}

					App->render->Blit(SetCounts, 0, 0, NULL);

					if (player1_won_set1 && player1_won_set2 && !player2_won_set1 && !player2_won_set2) {

						App->render->Blit(number2_left, 0, 0, NULL);
						App->render->Blit(number0_right, 0, 0, NULL);

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);

					}
					else if (player1_won_set1 && !player2_won_set1 && player1_won_set2 && player2_won_set2) {

						App->render->Blit(number2_left, 0, 0, NULL);
						App->render->Blit(number1_right, 0, 0, NULL);

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}
					else if (setfinal_reached && player1_won_setfinal && !player2_won_setfinal) {

						App->render->Blit(number2_left, 0, 0, NULL);
						App->render->Blit(number1_right, 0, 0, NULL);

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}
					else if (suddendeath_reached && player1_won_suddendeath && !player2_won_suddendeath) {

						App->render->Blit(number3_left, 0, 0, NULL);
						App->render->Blit(number2_right, 0, 0, NULL);

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}

				}
				else if (player2_wins) {

					if (showResults) {

						App->render->Blit(character1_losing, 0, 0, NULL);
						App->render->Blit(character2_winning, 0, 0, NULL);
						App->render->Blit(player2_winsPNG, 0, 0, NULL);

					}

					App->render->Blit(SetCounts, 0, 0, NULL);

					if (!player1_won_set1 && !player1_won_set2 && player2_won_set1 && player2_won_set2) {

						App->render->Blit(number0_left, 0, 0, NULL);
						App->render->Blit(number2_right, 0, 0, NULL);

						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}
					else if (!player1_won_set1 && player2_won_set1 && player1_won_set2 && player2_won_set2) {

						App->render->Blit(number1_left, 0, 0, NULL);
						App->render->Blit(number2_right, 0, 0, NULL);

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}
					else if (setfinal_reached && !player1_won_setfinal && player2_won_setfinal) {

						App->render->Blit(number1_left, 0, 0, NULL);
						App->render->Blit(number2_right, 0, 0, NULL);

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}
					else if (suddendeath_reached && !player1_won_suddendeath && player2_won_suddendeath) {

						App->render->Blit(number2_left, 0, 0, NULL);
						App->render->Blit(number3_right, 0, 0, NULL);

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}

				}
				else if (DrawGame) {

					if (showResults) {

						App->render->Blit(character1_losing, 0, 0, NULL);
						App->render->Blit(character2_losing, 0, 0, NULL);
						App->render->Blit(draw_game, 0, 0, NULL);

					}

					App->render->Blit(SetCounts, 0, 0, NULL);

					App->render->Blit(number3_left, 0, 0, NULL);
					App->render->Blit(number3_right, 0, 0, NULL);

					App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
					App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

				}

			}
			else {

				App->render->Blit(gameOver, 0, 0, NULL);

				if (player1_wins) {

					if (player1_won_set1 && player1_won_set2 && !player2_won_set1 && !player2_won_set2) {

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);

					}
					else if (player1_won_set1 && !player2_won_set1 && player1_won_set2 && player2_won_set2) {

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}
					else if (setfinal_reached && player1_won_setfinal && !player2_won_setfinal) {

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}
					else if (suddendeath_reached && player1_won_suddendeath && !player2_won_suddendeath) {

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}

				}
				else if (player2_wins) {

					if (!player1_won_set1 && !player1_won_set2 && player2_won_set1 && player2_won_set2) {

						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}
					else if (!player1_won_set1 && player2_won_set1 && player1_won_set2 && player2_won_set2) {

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}
					else if (setfinal_reached && !player1_won_setfinal && player2_won_setfinal) {

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}
					else if (suddendeath_reached && !player1_won_suddendeath && player2_won_suddendeath) {

						App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
						App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

					}

				}
				else if (DrawGame) {

					App->render->Blit(App->moduleScore->ScorePanel, 114, 12, &rect2);
					App->render->Blit(App->moduleScore->ScorePanel, 162, 12, &rect2);

				}

			}

			break;

	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneGamePhase::CleanUp() {

	currentAnimation->Reset();

	App->textures->Unload(timer);

	App->textures->Unload(SetCounts);

	App->textures->Unload(number0_left);
	App->textures->Unload(number1_left);
	App->textures->Unload(number2_left);
	App->textures->Unload(number3_left);

	App->textures->Unload(number0_right);
	App->textures->Unload(number1_right);
	App->textures->Unload(number2_right);
	App->textures->Unload(number3_right);

	App->textures->Unload(player1_winsPNG);
	App->textures->Unload(player2_winsPNG);

	App->textures->Unload(draw_game);

	App->textures->Unload(character1_winning);
	App->textures->Unload(character2_winning);

	App->textures->Unload(character1_losing);
	App->textures->Unload(character2_losing);

	App->textures->Unload(set1);
	App->textures->Unload(set2);

	App->textures->Unload(setfinal);

	App->textures->Unload(suddendeath);

	App->textures->Unload(gameOver);

	App->textures->Unload(points);

	return true;
}
