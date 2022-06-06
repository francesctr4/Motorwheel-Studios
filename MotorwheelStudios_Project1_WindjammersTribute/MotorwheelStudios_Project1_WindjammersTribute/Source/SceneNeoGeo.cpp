#include "SceneNeoGeo.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneNeoGeo::SceneNeoGeo(bool startEnabled) : Module(startEnabled)
{
	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < 6; j++) {

			NeoGeo1.PushBack({ 304 * j, 224 * i, 304, 224 });

		}

	}

	NeoGeo1.loop = false;
	NeoGeo1.speed = 0.35f;

	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 6; j++) {

			NeoGeo2.PushBack({ 304 * j, 224 * i, 304, 224 });

		}

	}

	NeoGeo2.loop = false;
	NeoGeo2.speed = 0.15f;

}

SceneNeoGeo::~SceneNeoGeo()
{

}

// Load assets
bool SceneNeoGeo::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	NeoGeoPNG_1 = App->textures->Load("Assets/Sprites/IntroNeoGeo1.png");
	NeoGeoPNG_2 = App->textures->Load("Assets/Sprites/IntroNeoGeo2.png");
	
	App->audio->PlayMusic("Assets/Music/NeoGeo.ogg", false);

	currentAnimation = &NeoGeo1;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneNeoGeo::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneDataEast, 30);
	}

	currentAnimation->Update();

	if (NeoGeo1.HasFinished()) {

		currentAnimation = &NeoGeo2;
		currentAnimation->Update();

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneNeoGeo::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(NeoGeoPNG_1, 0, 0, &rect);

	if (NeoGeo1.HasFinished()) {

		App->render->Blit(NeoGeoPNG_2, 0, 0, &rect);

	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneNeoGeo::CleanUp() {

	App->textures->Unload(NeoGeoPNG_2);
	App->textures->Unload(NeoGeoPNG_1);

	return true;
}
