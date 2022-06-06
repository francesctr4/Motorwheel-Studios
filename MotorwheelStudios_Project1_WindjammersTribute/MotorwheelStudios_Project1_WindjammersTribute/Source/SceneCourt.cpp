#include "SceneCourt.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"

SceneCourt::SceneCourt(bool startEnabled) : Module(startEnabled)
{
	for (int i = 0; i < 18; i++) {

		beachUpWall.PushBack({ 0, 20 * i, 245, 20 });

	}
	beachUpWall.loop = false;
	beachUpWall.speed = 0.5f;

	for (int i = 0; i < 17; i++) {

		concreteUpWall.PushBack({ 0, 25 * i, 242, 25 });

	}
	concreteUpWall.loop = false;
	concreteUpWall.speed = 0.5f;

	for (int i = 0; i < 20; i++) {

		stadiumUpWall.PushBack({ 0, 25 * i, 244, 25 });

	}
	stadiumUpWall.loop = false;
	stadiumUpWall.speed = 0.5f;

	for (int i = 0; i < 3; i++) {

		Beach.PushBack({ 304 * i, 0, 304, 224 });

	}
	Beach.loop = true;
	Beach.speed = 0.15f;

	for (int i = 0; i < 3; i++) {

		Concrete.PushBack({ 304 * i, 0, 304, 224 });

	}
	Concrete.loop = true;
	Concrete.speed = 0.15f;

	for (int i = 0; i < 3; i++) {

		Stadium.PushBack({ 304 * i, 0, 304, 224 });

	}
	Stadium.loop = true;
	Stadium.speed = 0.15f;
}

SceneCourt::~SceneCourt()
{

}

// Load assets
bool SceneCourt::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	mapSelection = App->sceneSelectCourt->map;

	activateAnim = false;

	switch (mapSelection) {

		case 0: //Beach

			BeachSpritesheet = App->textures->Load("Assets/Sprites/BeachSpritesheet.png");
			currentAnimation = &Beach;

			BeachWalls = App->textures->Load("Assets/Sprites/BeachWalls.png");
			BeachNet = App->textures->Load("Assets/Sprites/BeachNet.png");

			beachUpWallPNG = App->textures->Load("Assets/Sprites/UpWallBeach.png");
			currentAnimationUpWall = &beachUpWall;

			App->audio->PlayMusic("Assets/Music/08_Flying-Power-Disc-_Beach-Court_.ogg", true, 1.0f);

			//Beach colliders 

			App->collisions->AddCollider({0, 32, 304, 15}, Collider::Type::UPWALL);
			App->collisions->AddCollider({0, 189, 304, 15}, Collider::Type::DOWNWALL);

			App->collisions->AddCollider({0, 47, 8, 47}, Collider::Type::THREEPOINTS_PLAYER2);
			App->collisions->AddCollider({0, 94, 8, 48}, Collider::Type::FIVEPOINTS_PLAYER2);
			App->collisions->AddCollider({0, 142, 8, 47 }, Collider::Type::THREEPOINTS_PLAYER2);

			App->collisions->AddCollider({145, 47, 13, 142}, Collider::Type::NET);

			App->collisions->AddCollider({296, 47, 8, 47 }, Collider::Type::THREEPOINTS_PLAYER1);
			App->collisions->AddCollider({296, 94, 8, 48 }, Collider::Type::FIVEPOINTS_PLAYER1);
			App->collisions->AddCollider({296, 142, 8, 47 }, Collider::Type::THREEPOINTS_PLAYER1);

			break;

		case 1: //Concrete

			ConcreteSpritesheet = App->textures->Load("Assets/Sprites/ConcreteSpritesheet.png");
			currentAnimation = &Concrete;

			ConcreteWalls = App->textures->Load("Assets/Sprites/ConcreteWalls.png");
			ConcreteNet = App->textures->Load("Assets/Sprites/ConcreteNet.png");

			concreteUpWallPNG = App->textures->Load("Assets/Sprites/UpWallConcrete.png");
			currentAnimationUpWall = &concreteUpWall;

			App->audio->PlayMusic("Assets/Music/09_You-Got-a-Power-_Concrete-Court_.ogg", true, 1.0f);

			//Concrete colliders

			App->collisions->AddCollider({ 0, 16, 304, 9 }, Collider::Type::UPWALL);
			App->collisions->AddCollider({ 0, 207, 304, 9 }, Collider::Type::DOWNWALL);

			App->collisions->AddCollider({ 144, 73, 15, 3 }, Collider::Type::CONCRETEPIVOT);
			App->collisions->AddCollider({ 144, 169, 15, 3 }, Collider::Type::CONCRETEPIVOT);

			App->collisions->AddCollider({ 0, 25, 8, 33 }, Collider::Type::FIVEPOINTS_PLAYER2);
			App->collisions->AddCollider({ 0, 58, 8, 116 }, Collider::Type::THREEPOINTS_PLAYER2);
			App->collisions->AddCollider({ 0, 174, 8, 33 }, Collider::Type::FIVEPOINTS_PLAYER2);

			App->collisions->AddCollider({ 140, 25, 24, 182 }, Collider::Type::NET);

			App->collisions->AddCollider({296, 25, 8, 33}, Collider::Type::FIVEPOINTS_PLAYER1);
			App->collisions->AddCollider({296, 58, 8, 116}, Collider::Type::THREEPOINTS_PLAYER1);
			App->collisions->AddCollider({296, 174, 8, 33}, Collider::Type::FIVEPOINTS_PLAYER1);

			break;

		case 2: //Stadium

			StadiumSpritesheet = App->textures->Load("Assets/Sprites/StadiumSpritesheet.png");
			currentAnimation = &Stadium;

			StadiumWalls = App->textures->Load("Assets/Sprites/StadiumWalls.png");
			StadiumNet = App->textures->Load("Assets/Sprites/StadiumNet.png");

			stadiumUpWallPNG = App->textures->Load("Assets/Sprites/UpWallStadium.png");
			currentAnimationUpWall = &stadiumUpWall;

			App->audio->PlayMusic("Assets/Music/11_Break Point Champs (Stadium Court).ogg", true, 1.0f);

			//Stadium colliders

			App->collisions->AddCollider({ 0, 13, 304, 17 }, Collider::Type::UPWALL);
			App->collisions->AddCollider({ 0, 206, 304, 17 }, Collider::Type::DOWNWALL); 

			App->collisions->AddCollider({ 0, 30, 10, 65 }, Collider::Type::THREEPOINTS_PLAYER2);
			App->collisions->AddCollider({ 0, 95, 10, 23 }, Collider::Type::FIVEPOINTS_PLAYER2);
			App->collisions->AddCollider({ 0, 118, 10, 88 }, Collider::Type::THREEPOINTS_PLAYER2);

			App->collisions->AddCollider({ 146, 30, 13, 176 }, Collider::Type::NET);

			App->collisions->AddCollider({ 294, 30, 10, 65 }, Collider::Type::THREEPOINTS_PLAYER1);
			App->collisions->AddCollider({ 294, 95, 10, 23 }, Collider::Type::FIVEPOINTS_PLAYER1);
			App->collisions->AddCollider({ 294, 118, 10, 88 }, Collider::Type::THREEPOINTS_PLAYER1);

			break;

	}

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->particles->Enable();
	App->collisions->Enable();
	App->sceneCourtElements->Enable();
	App->moduleScore->Enable();
	App->sceneGamePhase->Enable();

	return ret;
}

Update_Status SceneCourt::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_BACK] == Key_State::KEY_DOWN)
	{

		App->fade->FadeToBlack((Module*)App->sceneCourt, (Module*)App->sceneTitle, 30);
	}

	currentAnimation->Update();

	if (activateAnim) {

		currentAnimationUpWall->Update();

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneCourt::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	SDL_Rect rect1 = currentAnimationUpWall->GetCurrentFrame();

	switch (mapSelection) {

	case 0: //Beach

		App->render->Blit(BeachSpritesheet, 0, 0, &rect);

		App->render->Blit(BeachWalls, 0, 0, NULL);


		App->render->Blit(beachUpWallPNG, 30, 36, &rect1);


		App->render->Blit(BeachNet, 0, 0, NULL);

		break;

	case 1: //Concrete

		App->render->Blit(ConcreteSpritesheet, 0, 0, &rect);

		App->render->Blit(ConcreteWalls, 0, 0, NULL);


		App->render->Blit(concreteUpWallPNG, 30, 17, &rect1);


		App->render->Blit(ConcreteNet, 0, 0, NULL);

		break;

	case 2: //Stadium

		App->render->Blit(StadiumSpritesheet, 0, 0, &rect);

		App->render->Blit(StadiumWalls, 0, 0, NULL);


		App->render->Blit(stadiumUpWallPNG, 31, 16, &rect1);


		App->render->Blit(StadiumNet, 0, 0, NULL);

		break;

	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneCourt::CleanUp()
{
	App->sceneGamePhase->Disable();
	App->moduleScore->Disable();
	App->sceneCourtElements->Disable();
	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();

	switch (mapSelection) {

	case 0: //Beach

		App->textures->Unload(BeachSpritesheet);
		App->textures->Unload(BeachWalls);
		App->textures->Unload(BeachNet);
		App->textures->Unload(beachUpWallPNG);

		break;

	case 1: //Concrete

		App->textures->Unload(ConcreteSpritesheet);
		App->textures->Unload(ConcreteWalls);
		App->textures->Unload(ConcreteNet);
		App->textures->Unload(concreteUpWallPNG);

		break;

	case 2: //Stadium

		App->textures->Unload(StadiumSpritesheet);
		App->textures->Unload(StadiumWalls);
		App->textures->Unload(StadiumNet);
		App->textures->Unload(stadiumUpWallPNG);

		break;

	}

	return true;
}