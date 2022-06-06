#include "SceneVersus.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneVersus::SceneVersus(bool startEnabled) : Module(startEnabled)
{

	for (int i = 0; i < 6; i++) {

		Versus.PushBack({304*i, 0, 304, 224 });

	}
	Versus.loop = true;
	Versus.speed = 0.4f;
}

SceneVersus::~SceneVersus()
{

}

// Load assets
bool SceneVersus::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	player1_selection = App->sceneSelectPlayer->characterP1;
	player2_selection = App->sceneSelectPlayer->characterP2;

	switch (player1_selection) {

	case 0: // Hiromi Mita (left)

		HiromiMitaVS_left = App->textures->Load("Assets/Sprites/HiromiMitaVS_left.png");
		JapanVS_left = App->textures->Load("Assets/Sprites/JapanVS_left.png");
		break;

	case 1: // Jordi Costa (left)

		JordiCostaVS_left = App->textures->Load("Assets/Sprites/JordiCostaVS_left.png");
		SpainVS_left = App->textures->Load("Assets/Sprites/SpainVS_left.png");
		break;

	case 2: // Gary Scott (left)

		GaryScottVS_left = App->textures->Load("Assets/Sprites/GaryScottVS_left.png");
		UsaVS_left = App->textures->Load("Assets/Sprites/UsaVS_left.png");
		break;
	}

	switch (player2_selection) {

	case 0: // Hiromi Mita (right)

		HiromiMitaVS_right = App->textures->Load("Assets/Sprites/HiromiMitaVS_right.png");
		JapanVS_right = App->textures->Load("Assets/Sprites/JapanVS_right.png");
		break;

	case 1: // Jordi Costa (right)

		JordiCostaVS_right = App->textures->Load("Assets/Sprites/JordiCostaVS_right.png");
		SpainVS_right = App->textures->Load("Assets/Sprites/SpainVS_right.png");
		break;


	case 2: // Gary Scott (right)

		GaryScottVS_right = App->textures->Load("Assets/Sprites/GaryScottVS_right.png");
		UsaVS_right = App->textures->Load("Assets/Sprites/UsaVS_right.png");
		break;
	}

	VersusVS = App->textures->Load("Assets/Sprites/FondoVS.png");
	currentAnimation = &Versus;

	VS = App->textures->Load("Assets/Sprites/VS.png");

	App->audio->PlayMusic("Assets/Music/02_Go-for-Broke_-_Round-Start_.ogg", false, 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneVersus::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneCourt, 30);
	}

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneVersus::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(VersusVS, 0, 0, &rect);

	switch (player1_selection) {

	case 0: // Hiromi Mita (left)

		App->render->Blit(HiromiMitaVS_left, 0, 0, NULL);
		App->render->Blit(JapanVS_left, 0, 0, NULL);
		break;

	case 1: // Jordi Costa (left)

		App->render->Blit(JordiCostaVS_left, 0, 0, NULL);
		App->render->Blit(SpainVS_left, 0, 0, NULL);
		break;

	case 2: // Gary Scott (left)

		App->render->Blit(GaryScottVS_left, 0, 0, NULL);
		App->render->Blit(UsaVS_left, 0, 0, NULL);
		break;
	}

	switch (player2_selection) {

	case 0: // Hiromi Mita (right)

		App->render->Blit(HiromiMitaVS_right, 0, 0, NULL);
		App->render->Blit(JapanVS_right, 0, 0, NULL);
		break;

	case 1: // Jordi Costa (right)

		App->render->Blit(JordiCostaVS_right, 0, 0, NULL);
		App->render->Blit(SpainVS_right, 0, 0, NULL);
		break;


	case 2: // Gary Scott (right)

		App->render->Blit(GaryScottVS_right, 0, 0, NULL);
		App->render->Blit(UsaVS_right, 0, 0, NULL);
		break;
	}

	App->render->Blit(VS, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneVersus::CleanUp() {

	App->textures->Unload(VS);
	App->textures->Unload(VersusVS);

	switch (player2_selection) {

	case 0: // Hiromi Mita (right)

		App->textures->Unload(JapanVS_right);
		App->textures->Unload(HiromiMitaVS_right);
		break;

	case 1: // Jordi Costa (right)

		App->textures->Unload(SpainVS_right);
		App->textures->Unload(JordiCostaVS_right);
		break;


	case 2: // Gary Scott (right)

		App->textures->Unload(UsaVS_right);
		App->textures->Unload(GaryScottVS_right);
		break;
	}

	switch (player1_selection) {

	case 0: // Hiromi Mita (left)

		App->textures->Unload(JapanVS_left);
		App->textures->Unload(HiromiMitaVS_left);
		break;

	case 1: // Jordi Costa (left)

		App->textures->Unload(SpainVS_left);
		App->textures->Unload(JordiCostaVS_left);
		break;

	case 2: // Gary Scott (left)

		App->textures->Unload(UsaVS_left);
		App->textures->Unload(GaryScottVS_left);
		break;
	}

	return true;
}