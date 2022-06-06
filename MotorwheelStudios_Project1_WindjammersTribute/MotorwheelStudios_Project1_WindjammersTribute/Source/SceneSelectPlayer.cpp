#include "SceneSelectPlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include "SceneTitle.h"

SceneSelectPlayer::SceneSelectPlayer(bool startEnabled) : Module(startEnabled)
{

	for (int i = 0; i < 10; i++) {

		time.PushBack({ 14 * i, 0, 13, 16 });

	}

	time.loop = false;
	time.speed = (1.0f / 60.0f);

}

SceneSelectPlayer::~SceneSelectPlayer()
{

}

// Load assets
bool SceneSelectPlayer::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	timer = App->textures->Load("Assets/Sprites/timerMenu.png");
	currentAnimation = &time;

	bgTexture = App->textures->Load("Assets/Sprites/Menu_Personajes.png");
	playerSelection = App->textures->Load("Assets/Sprites/1P_2P_CPU.png");

	App->audio->PlayMusic("Assets/Music/01_Get-Ready-_Select-Screen_.ogg", true, 1.0f);
	selectFx = App->audio->LoadFx("Assets/Fx/Select.wav");
	moveUI = App->audio->LoadFx("Assets/Fx/moveUI.wav");

	HiromiSelected = App->audio->LoadFx("Assets/Fx/HiromiSelected.wav");
	JordiSelected = App->audio->LoadFx("Assets/Fx/JordiSelected.wav");
	GarySelected = App->audio->LoadFx("Assets/Fx/GarySelected.wav");

	playerSprite1 = { 0,0,20,16 };
	playerSprite2 = { 21,0,23,16 };

	iteratorY[0] = 72;
	iteratorY[1] = 72 + 56;
	iteratorY[2] = 72 + 56 * 2;
	
	characterP1 = 0;
	characterP2 = 0;

	player1_selected = false;
	player2_selected = false;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	both_selected_once = false;

	startTimerPlayerSelection = SDL_GetTicks();

	return ret;
}

Update_Status SceneSelectPlayer::Update()
{
	//Player 1

	if (!player1_selected) {

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_DPAD_UP] == Key_State::KEY_DOWN) {

			App->audio->PlayFx(moveUI);

			if (characterP1 > 0) {

				characterP1--;

			}
			else if (characterP1 == 0) {

				characterP1 = 2;

			}

		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == Key_State::KEY_DOWN) {

			App->audio->PlayFx(moveUI);

			if (characterP1 < 2) {

				characterP1++;

			}
			else if (characterP1 == 2) {

				characterP1 = 0;

			}

		}

		if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN) {

			player1_selected = true;

			if (characterP1 == 0) {

				App->audio->PlayFx(HiromiSelected);

			}
			else if (characterP1 == 1) {

				App->audio->PlayFx(JordiSelected);

			}
			else if (characterP1 == 2) {

				App->audio->PlayFx(GarySelected);

			}

		}

	}

	//Player 2

	if (!player2_selected) {

		if (App->input->keys[SDL_SCANCODE_I] == Key_State::KEY_DOWN || App->input->controllers[1].buttons[SDL_CONTROLLER_BUTTON_DPAD_UP] == Key_State::KEY_DOWN) {

			App->audio->PlayFx(moveUI);

			if (characterP2 > 0) {

				characterP2--;

			}
			else if (characterP2 == 0) {

				characterP2 = 2;

			}

		}

		if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN || App->input->controllers[1].buttons[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == Key_State::KEY_DOWN) {

			App->audio->PlayFx(moveUI);

			if (characterP2 < 2) {

				characterP2++;

			}
			else if (characterP2 == 2) {

				characterP2 = 0;

			}

		}

		if (App->input->keys[SDL_SCANCODE_PERIOD] == Key_State::KEY_DOWN || App->input->controllers[1].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN) {

			player2_selected = true;

			if (characterP2 == 0) {

				App->audio->PlayFx(HiromiSelected);

			}
			else if (characterP2 == 1) {

				App->audio->PlayFx(JordiSelected);

			}
			else if (characterP2 == 2) {

				App->audio->PlayFx(GarySelected);

			}


		}

	}

	if (player1_selected && player2_selected && !both_selected_once) {

		start = SDL_GetTicks();

		both_selected_once = true;
		
	}

	if (both_selected_once) {

		stop = SDL_GetTicks();

		if (stop - start >= 1000) {

			App->fade->FadeToBlack(this, (Module*)App->sceneSelectCourt, 30);

		}
	
	}

	stopTimerPlayerSelection = SDL_GetTicks();

	if (stopTimerPlayerSelection - startTimerPlayerSelection >= 10000) {

		App->fade->FadeToBlack(this, (Module*)App->sceneSelectCourt, 30);

	}

	if (!both_selected_once) {

		currentAnimation->Update();

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneSelectPlayer::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(bgTexture, 0, 0, NULL);

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(timer, 265, 16, &rect);

	if (!player1_selected) {

		if (SDL_GetTicks() % 250 > 150) {

			App->render->Blit(playerSelection, 9, iteratorY[characterP1], &playerSprite1);

		}
		else {


		}

	}
	else {

		App->render->Blit(playerSelection, 9, iteratorY[characterP1], &playerSprite1);

	}
	
	if (!player2_selected) {

		if (SDL_GetTicks() % 250 > 150) {

			App->render->Blit(playerSelection, 33, iteratorY[characterP2], &playerSprite2);

		}
		else {


		}

	}
	else {

		App->render->Blit(playerSelection, 33, iteratorY[characterP2], &playerSprite2);

	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneSelectPlayer::CleanUp() {

	currentAnimation->Reset();

	App->textures->Unload(playerSelection);
	App->textures->Unload(bgTexture);

	App->textures->Unload(timer);

	return true;
}