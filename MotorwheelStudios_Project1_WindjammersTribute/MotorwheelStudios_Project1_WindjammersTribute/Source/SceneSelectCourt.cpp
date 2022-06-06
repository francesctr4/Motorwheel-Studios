#include "SceneSelectCourt.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

SceneSelectCourt::SceneSelectCourt(bool startEnabled) : Module(startEnabled)
{

	for (int i = 0; i < 10; i++) {

		time.PushBack({ 14 * i, 0, 13, 16 });

	}

	time.loop = false;
	time.speed = (1.0f / 60.0f);

}

SceneSelectCourt::~SceneSelectCourt()
{

}

// Load assets
bool SceneSelectCourt::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	selectFx = App->audio->LoadFx("Assets/Fx/Select.wav");
	moveUI = App->audio->LoadFx("Assets/Fx/moveUI.wav");

	timer = App->textures->Load("Assets/Sprites/timerMenu.png");

	currentAnimation = &time;

	beach = App->textures->Load("Assets/Sprites/BeachSelection.png");
	concrete = App->textures->Load("Assets/Sprites/ConcreteSelection.png");
	stadium = App->textures->Load("Assets/Sprites/StadiumSelection.png");
	titulos = App->textures->Load("Assets/Sprites/Titulos_Mapa.png");

	iterator[0] = beach;
	iterator[1] = concrete;
	iterator[2] = stadium;

	map = 0;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	start = 0;
	stop = 0;

	map_selected = false;

	startTimerMapSelection = SDL_GetTicks();

	return ret;
}

Update_Status SceneSelectCourt::Update()
{
	if (!map_selected) {

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_DPAD_UP] == Key_State::KEY_DOWN)
		{
			App->audio->PlayFx(moveUI);

			if (map > 0) {

				map--;

			}
			else if (map == 0) {

				map = 2;

			}

		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == Key_State::KEY_DOWN)
		{
			App->audio->PlayFx(moveUI);

			if (map < 2) {

				map++;

			}
			else if (map == 2) {

				map = 0;

			}

		}

	}

	if ((App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN) && !map_selected) {

		App->audio->PlayFx(selectFx);

		start = SDL_GetTicks();

		map_selected = true;

	}

	if (map_selected) {

		stop = SDL_GetTicks();

		if (stop - start >= 1500) {

			App->fade->FadeToBlack(this, (Module*)App->sceneVersus, 30);

		}

	}

	stopTimerMapSelection = SDL_GetTicks();

	if (stopTimerMapSelection - startTimerMapSelection >= 10000) {

		App->fade->FadeToBlack(this, (Module*)App->sceneVersus, 30);

	}

	if (!map_selected) {

		currentAnimation->Update();

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneSelectCourt::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(iterator[map], 0, 0, NULL);
	App->render->Blit(titulos, 0, 0, NULL);

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(timer, 265, 16, &rect);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneSelectCourt::CleanUp() {

	currentAnimation->Reset();

	App->textures->Unload(titulos);
	App->textures->Unload(stadium);
	App->textures->Unload(concrete);
	App->textures->Unload(beach);

	App->textures->Unload(timer);

	return true;
}