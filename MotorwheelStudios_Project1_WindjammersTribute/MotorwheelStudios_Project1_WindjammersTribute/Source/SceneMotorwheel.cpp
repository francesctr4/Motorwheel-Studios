#include "SceneMotorwheel.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneMotorwheel::SceneMotorwheel(bool startEnabled) : Module(startEnabled)
{
	
}

SceneMotorwheel::~SceneMotorwheel()
{

}

// Load assets
bool SceneMotorwheel::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	MotorwheelPNG = App->textures->Load("Assets/Sprites/Motorwheel.png");

	App->audio->PlayMusic(NULL, false);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneMotorwheel::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneNeoGeo, 30);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneMotorwheel::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(MotorwheelPNG, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneMotorwheel::CleanUp() {

	App->textures->Unload(MotorwheelPNG);

	return true;
}