#include "ModuleScore.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"

ModuleScore::ModuleScore(bool startEnabled) : Module(startEnabled)
{

}

ModuleScore::~ModuleScore()
{

}

// Load assets
bool ModuleScore::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	mapSelection = App->sceneSelectCourt->map;

	PurpleScoreBase = App->textures->Load("Assets/Sprites/PurpleScoreBase.png");
	PurpleScoreNumbers = App->textures->Load("Assets/Sprites/PurpleScoreNumbers.png");
	ScorePanel = App->textures->Load("Assets/Sprites/ScorePanel.png");

	showScore = false;
	showScoreEndSet = false;

	scored = false;

	scoreP1 = 0;
	scoreP2 = 0;

	arbit_throw_disk_player2 = false;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status ModuleScore::Update()
{
	stopTimerScore = SDL_GetTicks();

	if (stopTimerScore - startTimerScore <= 2000) {

		showScore = true;
		App->player->playersCanMoveScore = false;

	}
	else {

		if (scored && !App->sceneGamePhase->betweenSets) {

			App->player->position_player1.x = 31;
			App->player->position_player1.y = 78;

			App->player->position_player2.x = SCREEN_WIDTH - App->player->position_player1.x - 23;
			App->player->position_player2.y = App->player->position_player1.y;

			switch (mapSelection) {

			case 0: // Beach

				App->audio->PlayFx(App->player->throwdisk_normal);
				App->sceneCourtElements->startTimerArbitThrowing = SDL_GetTicks();

				if (arbit_throw_disk_player2) {

					App->particles->AddParticle(App->particles->disk_upRightThrow, 166, 176, Collider::Type::PLAYER_SHOT);
					App->sceneCourtElements->arbit_throwing_right = true;

				}
				else {

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 131, 176, Collider::Type::PLAYER_SHOT);
					App->sceneCourtElements->arbit_throwing_left = true;

				}

				break;

			case 1: // Concrete

				App->audio->PlayFx(App->player->throwdisk_normal);
				App->sceneCourtElements->startTimerArbitThrowing = SDL_GetTicks();

				if (arbit_throw_disk_player2) {

					App->particles->AddParticle(App->particles->disk_upRightThrow, 166, 190, Collider::Type::PLAYER_SHOT);
					App->sceneCourtElements->arbit_throwing_right = true;

				}
				else {

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);
					App->sceneCourtElements->arbit_throwing_left = true;

				}

				break;

			case 2: // Stadium

				App->audio->PlayFx(App->player->throwdisk_normal);
				App->sceneCourtElements->startTimerArbitThrowing = SDL_GetTicks();

				if (arbit_throw_disk_player2) {

					App->particles->AddParticle(App->particles->disk_upRightThrow, 166, 190, Collider::Type::PLAYER_SHOT);
					App->sceneCourtElements->arbit_throwing_right = true;

				}
				else {

					App->particles->AddParticle(App->particles->disk_upLeftThrow, 137, 190, Collider::Type::PLAYER_SHOT);
					App->sceneCourtElements->arbit_throwing_left = true;

				}

				break;

			}

			scored = false;

		}

		showScore = false;
		App->player->playersCanMoveScore = true;

	}

	if (stopTimerScore - startTimerScore <= 2500) {

		App->player->playersCanMoveScore = false;

	}
	else {

		App->player->playersCanMoveScore = true;

	}

	if (showScoreEndSet) {

		if (stopTimerScore - startTimerScore <= 3000) {

			showScoreEndSet = true;

		}
		else {

			showScoreEndSet = false;

		}

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ModuleScore::PostUpdate()
{
	// Draw everything --------------------------------------

	// UI

	App->fonts->BlitText(10, 10, App->player->scoreFont, "P1");

	App->fonts->BlitText(42, 10, App->player->scoreFont, App->player->scoreText_player1);

	App->fonts->BlitText(SCREEN_WIDTH - 104, 10, App->player->scoreFont, "P2");

	App->fonts->BlitText(SCREEN_WIDTH - 72, 10, App->player->scoreFont, App->player->scoreText_player2);

	//App->fonts->BlitText(117, 216, App->player->scoreFont, "LEVEL-4");

	// SCORE

	SDL_Rect panelNumbers[10];

	for (int i = 0; i < 10; i++) {

		panelNumbers[i] = { i * 14, 0, 13, 11 };

	}

	switch (scoreP1) {

	case 0:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[0]);

		break;

	case 1:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[1]);

		break;

	case 2:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[2]);

		break;

	case 3:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[3]);

		break;

	case 4:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[4]);

		break;

	case 5:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[5]);

		break;

	case 6:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[6]);

		break;

	case 7:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[7]);

		break;

	case 8:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[8]);

		break;

	case 9:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[9]);

		break;

	case 10:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[0]);

		break;

	case 11:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[1]);

		break;

	case 12:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[2]);

		break;

	case 13:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[3]);

		break;

	case 14:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[4]);

		break;

	case 15:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[5]);

		break;

	case 16:

		App->render->Blit(ScorePanel, 114, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 130, 17, &panelNumbers[6]);

		break;

	}

	switch (scoreP2) {

	case 0:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[0]);

		break;

	case 1:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[1]);

		break;

	case 2:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[2]);

		break;

	case 3:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[3]);

		break;

	case 4:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[4]);

		break;

	case 5:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[5]);

		break;

	case 6:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[6]);

		break;

	case 7:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[7]);

		break;

	case 8:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[8]);

		break;

	case 9:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[0]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[9]);

		break;

	case 10:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[0]);

		break;

	case 11:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[1]);

		break;

	case 12:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[2]);

		break;

	case 13:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[3]);

		break;

	case 14:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[4]);

		break;

	case 15:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[5]);

		break;

	case 16:

		App->render->Blit(ScorePanel, 162, 17, &panelNumbers[1]);
		App->render->Blit(ScorePanel, 178, 17, &panelNumbers[6]);

		break;

	}

	SDL_Rect numbers[10];

	for (int i = 0; i < 10; i++) {

		numbers[i] = { i * 33, 0, 32, 80 };

	}

	if (showScore || showScoreEndSet) {

		App->render->Blit(PurpleScoreBase, 0, 0, NULL);

		switch (scoreP1) {

			case 0:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[0]);

				break;

			case 1:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[1]);

				break;

			case 2:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[2]);

				break;

			case 3:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[3]);

				break;

			case 4:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[4]);

				break;

			case 5:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[5]);

				break;

			case 6:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[6]);

				break;

			case 7:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[7]);

				break;

			case 8:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[8]);

				break;

			case 9:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[9]);

				break;

			case 10:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[0]);

				break;

			case 11:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[1]);

				break;

			case 12:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[2]);

				break;

			case 13:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[3]);

				break;

			case 14:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[4]);

				break;

			case 15:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[5]);

				break;

			case 16:

				App->render->Blit(PurpleScoreNumbers, 72, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 104, 72, &numbers[6]);

				break;

		}

		switch (scoreP2) {

			case 0:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[0]);

				break;

			case 1:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[1]);

				break;

			case 2:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[2]);

				break;

			case 3:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[3]);

				break;

			case 4:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[4]);

				break;

			case 5:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[5]);

				break;

			case 6:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[6]);

				break;

			case 7:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[7]);

				break;

			case 8:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[8]);

				break;

			case 9:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[0]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[9]);

				break;

			case 10:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[0]);

				break;

			case 11:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[1]);

				break;

			case 12:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[2]);

				break;

			case 13:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[3]);

				break;

			case 14:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[4]);

				break;

			case 15:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[5]);

				break;

			case 16:

				App->render->Blit(PurpleScoreNumbers, 168, 72, &numbers[1]);
				App->render->Blit(PurpleScoreNumbers, 200, 72, &numbers[6]);

				break;

		}

	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleScore::CleanUp() {

	App->textures->Unload(PurpleScoreBase);
	App->textures->Unload(PurpleScoreNumbers);
	App->textures->Unload(ScorePanel);

	return true;
}