#include "SceneTitle.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

SceneTitle::SceneTitle(bool startEnabled) : Module(startEnabled)
{
	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 6; j++) {

			Windjammers1.PushBack({ 304 * j, 224 * i, 304, 224 });

		}

	}

	Windjammers1.loop = false;
	Windjammers1.speed = 0.9f;

	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 6; j++) {

			Windjammers2.PushBack({ 304 * j, 224 * i, 304, 224 });

		}

	}

	Windjammers2.loop = false;
	Windjammers2.speed = 0.3f;

	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 6; j++) {

			Windjammers3.PushBack({ 304 * j, 224 * i, 304, 224 });

		}

	}

	Windjammers3.loop = false;
	Windjammers3.speed = 0.3f;

	for (int i = 0; i < 2; i++) {

		for (int j = 0; j < 6; j++) {

			Windjammers4.PushBack({ 304 * j, 224 * i, 304, 224 });

		}

	}

	Windjammers4.loop = false;
	Windjammers4.speed = 0.3f;
}

SceneTitle::~SceneTitle()
{

}

// Load assets
bool SceneTitle::Start()
{
	LOG("Loading background assets");

	App->input->Enable();

	bool ret = true;

	WindjammersPNG_1 = App->textures->Load("Assets/Sprites/IntroWindjammers1.png");
	WindjammersPNG_2 = App->textures->Load("Assets/Sprites/IntroWindjammers2.png");
	WindjammersPNG_3 = App->textures->Load("Assets/Sprites/IntroWindjammers3.png");
	WindjammersPNG_4 = App->textures->Load("Assets/Sprites/IntroWindjammers4.png");

	App->audio->PlayMusic(NULL, false);

	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,“”’?!_#$%()+-/:;<=>[*]^{|}~ ©" };

	scoreFont = App->fonts->Load("Assets/Fonts/WindjammersFont.png", lookupTable, 1);

	currentAnimation = &Windjammers1;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneTitle::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneSelectPlayer, 30);
	}

	currentAnimation->Update();

	if (Windjammers1.HasFinished()) {

		currentAnimation = &Windjammers2;
		currentAnimation->Update();

	}

	if (Windjammers2.HasFinished()) {

		currentAnimation = &Windjammers3;
		currentAnimation->Update();

	}

	if (Windjammers3.HasFinished()) {

		currentAnimation = &Windjammers4;
		currentAnimation->Update();

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneTitle::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(WindjammersPNG_1, 0, 0, &rect);

	if (Windjammers1.HasFinished()) {

		App->render->Blit(WindjammersPNG_2, 0, 0, &rect);

	}

	if (Windjammers2.HasFinished()) {

		App->render->Blit(WindjammersPNG_3, 0, 0, &rect);

	}

	if (Windjammers3.HasFinished()) {

		App->render->Blit(WindjammersPNG_4, 0, 0, &rect);

	}

	App->fonts->BlitText(116, 180, scoreFont, "DATA EAST");

	App->fonts->BlitText(26, 200, scoreFont, "© 1994 DATA EAST CORPORATION");


	return Update_Status::UPDATE_CONTINUE;
}

bool SceneTitle::CleanUp() {

	App->textures->Unload(WindjammersPNG_4);
	App->textures->Unload(WindjammersPNG_3);
	App->textures->Unload(WindjammersPNG_2);
	App->textures->Unload(WindjammersPNG_1);

	return true;
}