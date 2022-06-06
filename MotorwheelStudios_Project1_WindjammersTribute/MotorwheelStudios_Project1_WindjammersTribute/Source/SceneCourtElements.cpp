#include "SceneCourtElements.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"

SceneCourtElements::SceneCourtElements(bool startEnabled) : Module(startEnabled)
{
	for (int i = 0; i < 21; i++) {

		beachDownWall.PushBack({0, 20 * i, 245, 20 });

	}
	beachDownWall.loop = false;
	beachDownWall.speed = 0.5f;

	for (int i = 0; i < 17; i++) {

		concreteDownWall.PushBack({ 0, 25 * i, 240, 25 });

	}
	concreteDownWall.loop = false;
	concreteDownWall.speed = 0.5f;

	for (int i = 0; i < 19; i++) {

		stadiumDownWall.PushBack({ 0, 25 * i, 242, 25 });

	}
	stadiumDownWall.loop = false;
	stadiumDownWall.speed = 0.5f;

}

SceneCourtElements::~SceneCourtElements()
{

}

// Load assets
bool SceneCourtElements::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	mapSelection = App->sceneSelectCourt->map;

	switch (mapSelection) {

	case 0: //Beach

		beachDownWallPNG = App->textures->Load("Assets/Sprites/DownWallBeach.png");
		currentAnimationDownWall = &beachDownWall;

		goals = App->textures->Load("Assets/Sprites/GoalsBeach.png");

		marcador = App->textures->Load("Assets/Sprites/MarcadorBeach.png");

		arbit = App->textures->Load("Assets/Sprites/ArbitBeach.png");

		break;

	case 1: //Concrete

		concreteDownWallPNG = App->textures->Load("Assets/Sprites/DownWallConcrete.png");
		currentAnimationDownWall = &concreteDownWall;

		goals = App->textures->Load("Assets/Sprites/GoalsConcrete.png");

		marcador = App->textures->Load("Assets/Sprites/MarcadorConcrete.png");

		arbit = App->textures->Load("Assets/Sprites/ArbitConcrete.png");

		break;

	case 2: //Stadium

		stadiumDownWallPNG = App->textures->Load("Assets/Sprites/DownWallStadium.png");
		currentAnimationDownWall = &stadiumDownWall;

		goals = App->textures->Load("Assets/Sprites/GoalsStadium.png");

		marcador = App->textures->Load("Assets/Sprites/MarcadorStadium.png");

		arbit = App->textures->Load("Assets/Sprites/ArbitStadium.png");

		break;

	}

	activateAnim = false;

	arbit_looking_left = false;
	arbit_looking_right = false;

	arbit_hand_player1 = false;
	arbit_hand_player2 = false;

	arbit_throwing_left = false;
	arbit_throwing_right = false;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	startTimerArbit = SDL_GetTicks();

	startTimerArbitThrowing = SDL_GetTicks();

	return ret;
}

Update_Status SceneCourtElements::Update()
{
	stopTimerArbit = SDL_GetTicks();

	stopTimerArbitThrowing = SDL_GetTicks();

	if (stopTimerArbit - startTimerArbit >= 2000) {

		arbit_hand_player1 = false;
		arbit_hand_player2 = false;

	}

	if (stopTimerArbitThrowing - startTimerArbitThrowing >= 200) {

		arbit_throwing_left = false;
		arbit_throwing_right = false;

	}

	if (activateAnim) {

		currentAnimationDownWall->Update();

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneCourtElements::PostUpdate()
{
	// Draw everything --------------------------------------
	SDL_Rect rect = currentAnimationDownWall->GetCurrentFrame();

	SDL_Rect arbit_idle_left = { 60 * 3, 45 * 1, 60, 45 };
	SDL_Rect arbit_idle = {60 * 4, 45 * 1, 60, 45};
	SDL_Rect arbit_idle_right = { 60 * 5, 45 * 1, 60, 45 };

	SDL_Rect arbit_hand_left = { 60 * 3, 45 * 4, 60, 45 };
	SDL_Rect arbit_hand_right = { 60 * 3, 45 * 5, 60, 45 };

	SDL_Rect arbit_gesture_left = { 60 * 4, 45 * 2, 60, 45 };
	SDL_Rect arbit_gesture_right = { 60 * 4, 45 * 3, 60, 45 };

	App->render->Blit(goals, 0, 0, NULL);

	switch (mapSelection) {

	case 0: //Beach

		App->render->Blit(beachDownWallPNG, 30, 184, &rect);

		if (App->player->player1_hasTheDisk) {

			App->render->Blit(arbit, 140, 163, &arbit_idle_left);

		}
		else if (App->player->player2_hasTheDisk) {

			App->render->Blit(arbit, 140, 163, &arbit_idle_right);

		}
		else if (arbit_hand_player1) {

			App->render->Blit(arbit, 125, 163, &arbit_hand_left);

		}
		else if (arbit_hand_player2) {

			App->render->Blit(arbit, 140, 163, &arbit_hand_right);

		}
		else if (arbit_throwing_left) {

			App->render->Blit(arbit, 131, 163, &arbit_gesture_left);

		}
		else if (arbit_throwing_right) {

			App->render->Blit(arbit, 140, 163, &arbit_gesture_right);

		}
		else {

			App->render->Blit(arbit, 140, 163, &arbit_idle);

		}

		break;

	case 1: //Concrete

		App->render->Blit(concreteDownWallPNG, 31, 199, &rect);

		if (App->player->player1_hasTheDisk) {

			App->render->Blit(arbit, 140, 179, &arbit_idle_left);

		}
		else if (App->player->player2_hasTheDisk) {

			App->render->Blit(arbit, 140, 179, &arbit_idle_right);

		}
		else if (arbit_hand_player1) {

			App->render->Blit(arbit, 125, 179, &arbit_hand_left);

		}
		else if (arbit_hand_player2) {

			App->render->Blit(arbit, 140, 179, &arbit_hand_right);

		}
		else if (arbit_throwing_left) {

			App->render->Blit(arbit, 131, 179, &arbit_gesture_left);

		}
		else if (arbit_throwing_right) {

			App->render->Blit(arbit, 140, 179, &arbit_gesture_right);

		}
		else {

			App->render->Blit(arbit, 140, 179, &arbit_idle);

		}

		break;

	case 2: //Stadium

		App->render->Blit(stadiumDownWallPNG, 31, 191, &rect);

		if (App->player->player1_hasTheDisk) {

			App->render->Blit(arbit, 140, 179, &arbit_idle_left);

		}
		else if (App->player->player2_hasTheDisk) {

			App->render->Blit(arbit, 140, 179, &arbit_idle_right);

		}
		else if (arbit_hand_player1) {

			App->render->Blit(arbit, 125, 179, &arbit_hand_left);

		}
		else if (arbit_hand_player2) {

			App->render->Blit(arbit, 140, 179, &arbit_hand_right);

		}
		else if (arbit_throwing_left) {

			App->render->Blit(arbit, 131, 179, &arbit_gesture_left);

		}
		else if (arbit_throwing_right) {

			App->render->Blit(arbit, 140, 179, &arbit_gesture_right);

		}
		else {

			App->render->Blit(arbit, 140, 179, &arbit_idle);

		}

		break;

	}

	App->render->Blit(marcador, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneCourtElements::CleanUp() {

	switch (mapSelection) {

	case 0: //Beach

		App->textures->Unload(beachDownWallPNG);

		break;

	case 1: //Concrete

		App->textures->Unload(concreteDownWallPNG);

		break;

	case 2: //Stadium

		App->textures->Unload(stadiumDownWallPNG);

		break;

	}

	App->textures->Unload(goals);
	App->textures->Unload(marcador);
	App->textures->Unload(arbit);

	return true;
}