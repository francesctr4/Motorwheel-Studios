#include "SceneDataEast.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneDataEast::SceneDataEast(bool startEnabled) : Module(startEnabled)
{
	for (int i = 0; i < 17; i++) {

		DataEast.PushBack({ 304 * i, 0, 304, 224 });

	}
	DataEast.loop = false;
	DataEast.speed = 1.0f;
}

SceneDataEast::~SceneDataEast()
{

}

// Load assets
bool SceneDataEast::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	DataEastPNG = App->textures->Load("Assets/Sprites/IntroDataEast.png");

	App->audio->PlayMusic(NULL, false);

	currentAnimation = &DataEast;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneDataEast::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneTitle, 30);
	}

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneDataEast::PostUpdate()
{
	// Draw everything --------------------------------------

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(DataEastPNG, 0, 0, &rect);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneDataEast::CleanUp() {

	App->textures->Unload(DataEastPNG);

	return true;
}