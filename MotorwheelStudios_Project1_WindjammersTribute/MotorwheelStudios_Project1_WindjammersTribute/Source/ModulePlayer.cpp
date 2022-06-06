#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL.h"

#include <stdio.h>
#include <math.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
		// -- HIROMI MITA --

	// Disk possession

		// Beach left

	for (int i = 0; i < 4; i++) {

		HiromiMita_idleDiskBeachAnim_left.PushBack({ 50 * (0 + i), 60 * 0, 50, 60 });

	}
	HiromiMita_idleDiskBeachAnim_left.loop = true;
	HiromiMita_idleDiskBeachAnim_left.speed = 0.1f;

		// Concrete left

	for (int i = 0; i < 4; i++) {

		HiromiMita_idleDiskConcreteAnim_left.PushBack({ 50 * (0 + i), 60 * 1, 50, 60 });

	}
	HiromiMita_idleDiskConcreteAnim_left.loop = true;
	HiromiMita_idleDiskConcreteAnim_left.speed = 0.1f;

		// Stadium left

	for (int i = 0; i < 4; i++) {

		HiromiMita_idleDiskStadiumAnim_left.PushBack({ 50 * (0 + i), 60 * 2, 50, 60 });

	}
	HiromiMita_idleDiskStadiumAnim_left.loop = true;
	HiromiMita_idleDiskStadiumAnim_left.speed = 0.1f;

		// Beach right

	for (int i = 0; i < 4; i++) {

		HiromiMita_idleDiskBeachAnim_right.PushBack({ 50 * (0 + i), 60 * 0, 50, 60 });

	}
	HiromiMita_idleDiskBeachAnim_right.loop = true;
	HiromiMita_idleDiskBeachAnim_right.speed = 0.1f;

		// Concrete right

	for (int i = 0; i < 4; i++) {

		HiromiMita_idleDiskConcreteAnim_right.PushBack({ 50 * (0 + i), 60 * 1, 50, 60 });

	}
	HiromiMita_idleDiskConcreteAnim_right.loop = true;
	HiromiMita_idleDiskConcreteAnim_right.speed = 0.1f;

		// Stadium right

	for (int i = 0; i < 4; i++) {

		HiromiMita_idleDiskStadiumAnim_right.PushBack({ 50 * (0 + i), 60 * 2, 50, 60 });

	}
	HiromiMita_idleDiskStadiumAnim_right.loop = true;
	HiromiMita_idleDiskStadiumAnim_right.speed = 0.1f;

	// Idle animation

	for (int i = 0; i < 8; i++) {

		HiromiMita_idleAnim_left.PushBack({ 50 * (0 + i), 60 * 3, 50, 60 });

	}
	HiromiMita_idleAnim_left.loop = true;
	HiromiMita_idleAnim_left.speed = 0.1f;

	for (int i = 0; i < 8; i++) {

		HiromiMita_idleAnim_right.PushBack({ 50 * (0 + i), 60 * 3, 50, 60 });

	}
	HiromiMita_idleAnim_right.loop = true;
	HiromiMita_idleAnim_right.speed = 0.1f;

	// Upwards animation

	for (int i = 0; i < 6; i++) {

		HiromiMita_upAnim_left.PushBack({ 50 * (6 + i), 60 * 5, 50, 60 });

	}
	HiromiMita_upAnim_left.loop = true;
	HiromiMita_upAnim_left.speed = 0.1f;

	for (int i = 0; i < 6; i++) {

		HiromiMita_upAnim_right.PushBack({ 50 * (6 + i), 60 * 5, 50, 60 });

	}
	HiromiMita_upAnim_right.loop = true;
	HiromiMita_upAnim_right.speed = 0.1f;

	// Move right animation

	for (int i = 0; i < 6; i++) {

		HiromiMita_rightAnim_left.PushBack({ 50 * (0 + i), 60 * 4, 50, 60 });

	}
	HiromiMita_rightAnim_left.loop = true;
	HiromiMita_rightAnim_left.speed = 0.1f;

	for (int i = 0; i < 6; i++) {

		HiromiMita_rightAnim_right.PushBack({ 50 * (0 + i), 60 * 5, 50, 60 });

	}
	HiromiMita_rightAnim_right.loop = true;
	HiromiMita_rightAnim_right.speed = 0.1f;

	// Move left animation

	for (int i = 0; i < 6; i++) {

		HiromiMita_leftAnim_left.PushBack({ 50 * (0 + i), 60 * 5, 50, 60 });

	}
	HiromiMita_leftAnim_left.loop = true;
	HiromiMita_leftAnim_left.speed = 0.1f;

	for (int i = 0; i < 6; i++) {

		HiromiMita_leftAnim_right.PushBack({ 50 * (0 + i), 60 * 4, 50, 60 });

	}
	HiromiMita_leftAnim_right.loop = true;
	HiromiMita_leftAnim_right.speed = 0.1f;

	// Downwards animation

	for (int i = 0; i < 6; i++) {

		HiromiMita_downAnim_left.PushBack({ 50 * (6 + i), 60 * 4, 50, 60 });

	}
	HiromiMita_downAnim_left.loop = true;
	HiromiMita_downAnim_left.speed = 0.1f;

	for (int i = 0; i < 6; i++) {

		HiromiMita_downAnim_right.PushBack({ 50 * (6 + i), 60 * 4, 50, 60 });

	}
	HiromiMita_downAnim_right.loop = true;
	HiromiMita_downAnim_right.speed = 0.1f;

		// -- JORDI COSTA --

	// Disk possession
	
		// Beach left

	for (int i = 0; i < 4; i++) {

		JordiCosta_idleDiskBeachAnim_left.PushBack({ 80 * (0 + i), 80 * 0, 80, 80 });

	}
	JordiCosta_idleDiskBeachAnim_left.loop = true;
	JordiCosta_idleDiskBeachAnim_left.speed = 0.1f;

		// Concrete left

	for (int i = 0; i < 4; i++) {

		JordiCosta_idleDiskConcreteAnim_left.PushBack({ 80 * (0 + i), 80 * 1, 80, 80 });

	}
	JordiCosta_idleDiskConcreteAnim_left.loop = true;
	JordiCosta_idleDiskConcreteAnim_left.speed = 0.1f;

		// Stadium left

	for (int i = 0; i < 4; i++) {

		JordiCosta_idleDiskStadiumAnim_left.PushBack({ 80 * (0 + i), 80 * 2, 80, 80 });

	}
	JordiCosta_idleDiskStadiumAnim_left.loop = true;
	JordiCosta_idleDiskStadiumAnim_left.speed = 0.1f;

		// Beach right

	for (int i = 0; i < 4; i++) {

		JordiCosta_idleDiskBeachAnim_right.PushBack({ 80 * (0 + i), 80 * 0, 80, 80 });

	}
	JordiCosta_idleDiskBeachAnim_right.loop = true;
	JordiCosta_idleDiskBeachAnim_right.speed = 0.1f;

		// Concrete right

	for (int i = 0; i < 4; i++) {

		JordiCosta_idleDiskConcreteAnim_right.PushBack({ 80 * (0 + i), 80 * 1, 80, 80 });

	}
	JordiCosta_idleDiskConcreteAnim_right.loop = true;
	JordiCosta_idleDiskConcreteAnim_right.speed = 0.1f;

		// Stadium right

	for (int i = 0; i < 4; i++) {

		JordiCosta_idleDiskStadiumAnim_right.PushBack({ 80 * (0 + i), 80 * 2, 80, 80 });

	}
	JordiCosta_idleDiskStadiumAnim_right.loop = true;
	JordiCosta_idleDiskStadiumAnim_right.speed = 0.1f;
	
	// Idle animation

	for (int i = 0; i < 8; i++) {

		JordiCosta_idleAnim_left.PushBack({ 80 * (0 + i), 80 * 3, 80, 80 });

	}
	JordiCosta_idleAnim_left.loop = true;
	JordiCosta_idleAnim_left.speed = 0.15f;

	for (int i = 0; i < 8; i++) {

		JordiCosta_idleAnim_right.PushBack({ 80 * (0 + i), 80 * 3, 80, 80 });

	}
	JordiCosta_idleAnim_right.loop = true;
	JordiCosta_idleAnim_right.speed = 0.15f;

	// Upwards animation
	
	for (int i = 0; i < 6; i++) {

		JordiCosta_upAnim_left.PushBack({ 80 * (6 + i), 80 * 5, 80, 80 });

	}
	JordiCosta_upAnim_left.loop = true;
	JordiCosta_upAnim_left.speed = 0.15f;

	for (int i = 0; i < 6; i++) {

		JordiCosta_upAnim_right.PushBack({ 80 * (6 + i), 80 * 5, 80, 80 });

	}
	JordiCosta_upAnim_right.loop = true;
	JordiCosta_upAnim_right.speed = 0.15f;

	// Move right
	
	for (int i = 0; i < 6; i++) {

		JordiCosta_rightAnim_left.PushBack({ 80 * (0 + i), 80 * 4, 80, 80 });

	}
	JordiCosta_rightAnim_left.loop = true;
	JordiCosta_rightAnim_left.speed = 0.15f;

	for (int i = 0; i < 6; i++) {

		JordiCosta_rightAnim_right.PushBack({ 80 * (0 + i), 80 * 5, 80, 80 });

	}
	JordiCosta_rightAnim_right.loop = true;
	JordiCosta_rightAnim_right.speed = 0.15f;
	
	// Move left
	
	for (int i = 0; i < 6; i++) {

		JordiCosta_leftAnim_left.PushBack({ 80 * (0 + i), 80 * 5, 80, 80 });

	}
	JordiCosta_leftAnim_left.loop = true;
	JordiCosta_leftAnim_left.speed = 0.15f;

	for (int i = 0; i < 6; i++) {

		JordiCosta_leftAnim_right.PushBack({ 80 * (0 + i), 80 * 4, 80, 80 });

	}
	JordiCosta_leftAnim_right.loop = true;
	JordiCosta_leftAnim_right.speed = 0.15f;
	
	// Downwards animation

	for (int i = 0; i < 6; i++) {

		JordiCosta_downAnim_left.PushBack({ 80 * (6 + i), 80 * 4, 80, 80 });

	}
	JordiCosta_downAnim_left.loop = true;
	JordiCosta_downAnim_left.speed = 0.15f;

	for (int i = 0; i < 6; i++) {

		JordiCosta_downAnim_right.PushBack({ 80 * (6 + i), 80 * 4, 80, 80 });

	}
	JordiCosta_downAnim_right.loop = true;
	JordiCosta_downAnim_right.speed = 0.15f;

		// -- GARY SCOTT --

	// Disk possession
	
			// Beach left

	for (int i = 0; i < 4; i++) {

		GaryScott_idleDiskBeachAnim_left.PushBack({ 80 * (0 + i), 80 * 0, 80, 80 });

	}
	GaryScott_idleDiskBeachAnim_left.loop = true;
	GaryScott_idleDiskBeachAnim_left.speed = 0.1f;

		// Concrete left

	for (int i = 0; i < 4; i++) {

		GaryScott_idleDiskConcreteAnim_left.PushBack({ 80 * (0 + i), 80 * 1, 80, 80 });

	}
	GaryScott_idleDiskConcreteAnim_left.loop = true;
	GaryScott_idleDiskConcreteAnim_left.speed = 0.1f;

		// Stadium left

	for (int i = 0; i < 4; i++) {

		GaryScott_idleDiskStadiumAnim_left.PushBack({ 80 * (0 + i), 80 * 2, 80, 80 });

	}
	GaryScott_idleDiskStadiumAnim_left.loop = true;
	GaryScott_idleDiskStadiumAnim_left.speed = 0.1f;

		// Beach right

	for (int i = 0; i < 4; i++) {

		GaryScott_idleDiskBeachAnim_right.PushBack({ 80 * (0 + i), 80 * 0, 80, 80 });

	}
	GaryScott_idleDiskBeachAnim_right.loop = true;
	GaryScott_idleDiskBeachAnim_right.speed = 0.1f;

		// Concrete right

	for (int i = 0; i < 4; i++) {

		GaryScott_idleDiskConcreteAnim_right.PushBack({ 80 * (0 + i), 80 * 1, 80, 80 });

	}
	GaryScott_idleDiskConcreteAnim_right.loop = true;
	GaryScott_idleDiskConcreteAnim_right.speed = 0.1f;

		// Stadium right

	for (int i = 0; i < 4; i++) {

		GaryScott_idleDiskStadiumAnim_right.PushBack({ 80 * (0 + i), 80 * 2, 80, 80 });

	}
	GaryScott_idleDiskStadiumAnim_right.loop = true;
	GaryScott_idleDiskStadiumAnim_right.speed = 0.1f;
	
	// Idle animation
	
	for (int i = 0; i < 7; i++) {

		GaryScott_idleAnim_left.PushBack({ 80 * (0 + i), 80 * 3, 80, 80 });

	}
	GaryScott_idleAnim_left.loop = true;
	GaryScott_idleAnim_left.speed = 0.15f;

	for (int i = 0; i < 7; i++) {

		GaryScott_idleAnim_right.PushBack({ 80 * (0 + i), 80 * 3, 80, 80 });

	}
	GaryScott_idleAnim_right.loop = true;
	GaryScott_idleAnim_right.speed = 0.15f;

	// Upwards animation
	
	for (int i = 0; i < 6; i++) {

		GaryScott_upAnim_left.PushBack({ 80 * (6 + i), 80 * 4, 80, 80 });

	}
	GaryScott_upAnim_left.loop = true;
	GaryScott_upAnim_left.speed = 0.15f;

	for (int i = 0; i < 6; i++) {

		GaryScott_upAnim_right.PushBack({ 80 * (6 + i), 80 * 4, 80, 80 });

	}
	GaryScott_upAnim_right.loop = true;
	GaryScott_upAnim_right.speed = 0.15f;
	
	// Move right
	
	for (int i = 0; i < 6; i++) {

		GaryScott_rightAnim_left.PushBack({ 80 * (0 + i), 80 * 4, 80, 80 });

	}
	GaryScott_rightAnim_left.loop = true;
	GaryScott_rightAnim_left.speed = 0.15f;

	for (int i = 0; i < 6; i++) {

		GaryScott_rightAnim_right.PushBack({ 80 * (0 + i), 80 * 4, 80, 80 });

	}
	GaryScott_rightAnim_right.loop = true;
	GaryScott_rightAnim_right.speed = 0.15f;
	
	// Move left
	
	for (int i = 0; i < 6; i++) {

		GaryScott_leftAnim_left.PushBack({ 80 * (0 + i), 80 * 5, 80, 80 });

	}
	GaryScott_leftAnim_left.loop = true;
	GaryScott_leftAnim_left.speed = 0.15f;

	for (int i = 0; i < 6; i++) {

		GaryScott_leftAnim_right.PushBack({ 80 * (0 + i), 80 * 5, 80, 80 });

	}
	GaryScott_leftAnim_right.loop = true;
	GaryScott_leftAnim_right.speed = 0.15f;
	
	// Downwards animation

	for (int i = 0; i < 6; i++) {

		GaryScott_downAnim_left.PushBack({ 80 * (6 + i), 80 * 5, 80, 80 });

	}
	GaryScott_downAnim_left.loop = true;
	GaryScott_downAnim_left.speed = 0.15f;

	for (int i = 0; i < 6; i++) {

		GaryScott_downAnim_right.PushBack({ 80 * (6 + i), 80 * 5, 80, 80 });

	}
	GaryScott_downAnim_right.loop = true;
	GaryScott_downAnim_right.speed = 0.15f;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	score_player1 = 0;
	score_player2 = 0;

	player1_hasTheDisk = false;
	player2_hasTheDisk = false;

	flag = App->textures->Load("Assets/Sprites/Flags.png");

	mapSelection = App->sceneSelectCourt->map;

	player1_selection = App->sceneSelectPlayer->characterP1;
	player2_selection = App->sceneSelectPlayer->characterP2;

	switch (player1_selection) {

		case 0: // Hiromi Mita (left)

			texture_player1 = App->textures->Load("Assets/Sprites/H.Mita.png");
			currentAnimation_player1 = &HiromiMita_idleAnim_left;
			break;

		case 1: // Jordi Costa (left)

			texture_player1 = App->textures->Load("Assets/Sprites/J.Costa.png");
			currentAnimation_player1 = &JordiCosta_idleAnim_left;
			break;

		case 2: // Gary Scott (left)

			texture_player1 = App->textures->Load("Assets/Sprites/G.Scott.png");
			currentAnimation_player1 = &GaryScott_idleAnim_left;
			break;
	}

	switch (player2_selection) {

		case 0: // Hiromi Mita (right)

			texture_player2 = App->textures->Load("Assets/Sprites/H.Mita2.png");
			currentAnimation_player2 = &HiromiMita_idleAnim_right;
			break;

		case 1: // Jordi Costa (right)

			texture_player2 = App->textures->Load("Assets/Sprites/J.Costa2.png");
			currentAnimation_player2 = &JordiCosta_idleAnim_right;
			break;


		case 2: // Gary Scott (right)

			texture_player2 = App->textures->Load("Assets/Sprites/G.Scott2.png");
			currentAnimation_player2 = &GaryScott_idleAnim_right;
			break;
	}

	if (player1_selection == 0 || player2_selection == 0) {

		hiromiFx = App->audio->LoadFx("Assets/Fx/HiromiHit.wav");

	}

	if (player1_selection == 1 || player2_selection == 1) {

		jordiFx = App->audio->LoadFx("Assets/Fx/JordiHit.wav");

	}

	if (player1_selection == 2 || player2_selection == 2) {

		garyFx = App->audio->LoadFx("Assets/Fx/GaryHit.wav");

	}

	position_player1.x = 31;
	position_player1.y = 78;

	position_player2.x = SCREEN_WIDTH - position_player1.x - 23;
	position_player2.y = position_player1.y;

	collider_player1 = App->collisions->AddCollider({ position_player1.x, position_player1.y + 24, 23, 36 }, Collider::Type::PLAYER_1, this);
	collider_player2 = App->collisions->AddCollider({ position_player2.x, position_player2.y + 24, 23, 36 }, Collider::Type::PLAYER_2, this);

	// WINDJAMMERS FONT

	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,“”’?!_#$%()+-/:;<=>[*]^{|}~ ©" };

	scoreFont = App->fonts->Load("Assets/Fonts/WindjammersFont.png", lookupTable, 1);

	throwdisk_normal = App->audio->LoadFx("Assets/Fx/ThrowDiskNormal.wav");
	throwdisk_fast_Hiromi = App->audio->LoadFx("Assets/Fx/SupersonicHiromi.wav");
	
	stop = 0;

	playersCanMove = false;
	playersCanMoveScore = true;

	return ret;
}

Update_Status ModulePlayer::Update()
{

	// """God Mode"""

	/*if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN) {

		player1_hasTheDisk = true;
		player2_hasTheDisk = true;
	
	}*/

	// Arbit function

	/*if (!player1_hasTheDisk && !player2_hasTheDisk) {

		if ((App->input->keys[SDL_SCANCODE_O] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == Key_State::KEY_DOWN) && playersCanMove && playersCanMoveScore) {

			App->particles->start = SDL_GetTicks();

			player1_hasTheDisk = true;
		}

		if ((App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN || App->input->controllers[1].buttons[SDL_CONTROLLER_BUTTON_START] == Key_State::KEY_DOWN) && playersCanMove && playersCanMoveScore) {

			App->particles->start = SDL_GetTicks();

			player2_hasTheDisk = true;
		}

	}*/

		// -- PLAYER 1 CONTROLS --

	if (!player1_hasTheDisk) {

		if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2) < 0) && playersCanMove && playersCanMoveScore)
		{
			position_player1.x -= speed * 2;

			switch (player1_selection) {

				case 0: // Hiromi Mita (left)

					if (currentAnimation_player1 != &HiromiMita_leftAnim_left)
					{
						HiromiMita_leftAnim_left.Reset();
						currentAnimation_player1 = &HiromiMita_leftAnim_left;
					}
				
					break;

				case 1: // Jordi Costa (left)

					if (currentAnimation_player1 != &JordiCosta_leftAnim_left)
					{
						JordiCosta_leftAnim_left.Reset();
						currentAnimation_player1 = &JordiCosta_leftAnim_left;
					}
				
					break;

				case 2: // Gary Scott (left)

					if (currentAnimation_player1 != &GaryScott_leftAnim_left)
					{
						GaryScott_leftAnim_left.Reset();
						currentAnimation_player1 = &GaryScott_leftAnim_left;
					}
			
					break;
			}

		}

		if ((App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2) > 0) && playersCanMove && playersCanMoveScore)
		{
			position_player1.x += speed * 2;

			switch (player1_selection) {

				case 0: // Hiromi Mita (left)

					if (currentAnimation_player1 != &HiromiMita_rightAnim_left)
					{
						HiromiMita_rightAnim_left.Reset();
						currentAnimation_player1 = &HiromiMita_rightAnim_left;
					}

					break;

				case 1: // Jordi Costa (left)

					if (currentAnimation_player1 != &JordiCosta_rightAnim_left)
					{
						JordiCosta_rightAnim_left.Reset();
						currentAnimation_player1 = &JordiCosta_rightAnim_left;
					}

					break;

				case 2: // Gary Scott (left)

					if (currentAnimation_player1 != &GaryScott_rightAnim_left)
					{
						GaryScott_rightAnim_left.Reset();
						currentAnimation_player1 = &GaryScott_rightAnim_left;
					}

					break;
			}

		}

		if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT || App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) > 0) && playersCanMove && playersCanMoveScore)
		{
			position_player1.y += speed * 2;

			switch (player1_selection) {

				case 0: // Hiromi Mita (left)

					if (currentAnimation_player1 != &HiromiMita_downAnim_left)
					{
						HiromiMita_downAnim_left.Reset();
						currentAnimation_player1 = &HiromiMita_downAnim_left;
					}

					break;

				case 1: // Jordi Costa (left)

					if (currentAnimation_player1 != &JordiCosta_downAnim_left)
					{
						JordiCosta_downAnim_left.Reset();
						currentAnimation_player1 = &JordiCosta_downAnim_left;
					}

					break;

				case 2: // Gary Scott (left)

					if (currentAnimation_player1 != &GaryScott_downAnim_left)
					{
						GaryScott_downAnim_left.Reset();
						currentAnimation_player1 = &GaryScott_downAnim_left;
					}

					break;
			}

		}

		if ((App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT || App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) < 0) && playersCanMove && playersCanMoveScore)
		{
			position_player1.y -= speed * 2;

			switch (player1_selection) {

				case 0: // Hiromi Mita (left)

					if (currentAnimation_player1 != &HiromiMita_upAnim_left)
					{
						HiromiMita_upAnim_left.Reset();
						currentAnimation_player1 = &HiromiMita_upAnim_left;
					}

					break;

				case 1: // Jordi Costa (left)

					if (currentAnimation_player1 != &JordiCosta_upAnim_left)
					{
						JordiCosta_upAnim_left.Reset();
						currentAnimation_player1 = &JordiCosta_upAnim_left;
					}

					break;

				case 2: // Gary Scott (left)

					if (currentAnimation_player1 != &GaryScott_upAnim_left)
					{
						GaryScott_upAnim_left.Reset();
						currentAnimation_player1 = &GaryScott_upAnim_left;
					}

					break;
			}

		}

		// DASH PROTOTYPE

		/*if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			if (currentAnimation_player1 != &HiromiMita_dashUpRightAnim_left)
			{
				HiromiMita_dashUpRightAnim_left.Reset();
				currentAnimation_player1 = &HiromiMita_dashUpRightAnim_left;
			}
		}*/

	}

	if (player1_hasTheDisk) {

		if (((App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) || (App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN && App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) == 0)) && playersCanMove && playersCanMoveScore)
		{

			stop = SDL_GetTicks();
			
			if (stop - App->particles->start < 150) {
				
				// SUPERSONIC PROTOTYPE

				/*App->particles->AddParticle(App->particles->supersonic, position_player1.x + 20, position_player1.y + 5 + 24, Collider::Type::PLAYER_SHOT);
				player1_hasTheDisk = false;
				App->audio->PlayFx(throwdisk_fast_Hiromi);*/

				App->particles->AddParticle(App->particles->disk_straightRightThrow, position_player1.x + 20, position_player1.y + 5 + 24, Collider::Type::PLAYER_SHOT);
				player1_hasTheDisk = false;
				App->audio->PlayFx(throwdisk_normal);

			}
			else {

				App->particles->AddParticle(App->particles->disk_straightRightThrow, position_player1.x + 20, position_player1.y + 5 + 24, Collider::Type::PLAYER_SHOT);
				player1_hasTheDisk = false;
				App->audio->PlayFx(throwdisk_normal);

			}

		}
		else if (((App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT) || (App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN && App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) < 0)) && playersCanMove && playersCanMoveScore)
		{

			App->particles->AddParticle(App->particles->disk_upRightThrow, position_player1.x + 20, position_player1.y + 5 + 24, Collider::Type::PLAYER_SHOT);
			player1_hasTheDisk = false;
			App->audio->PlayFx(throwdisk_normal);


		}
		else if (((App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) || (App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN && App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) > 0)) && playersCanMove && playersCanMoveScore)
		{

			App->particles->AddParticle(App->particles->disk_downRightThrow, position_player1.x + 20, position_player1.y + 5 + 24, Collider::Type::PLAYER_SHOT);
			player1_hasTheDisk = false;
			App->audio->PlayFx(throwdisk_normal);

		}
		else if (((App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE) || (App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_IDLE && App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) == 0)) && playersCanMove && playersCanMoveScore) {

			stop = SDL_GetTicks();

			if (stop - App->particles->start >= 1500) {

				App->particles->AddParticle(App->particles->disk_straightRightThrow, position_player1.x + 20, position_player1.y + 5 + 24, Collider::Type::PLAYER_SHOT);
				player1_hasTheDisk = false;
				App->audio->PlayFx(throwdisk_normal);

			}

		}

		// LOB PROTOTYPE

		/*if (App->input->keys[SDL_SCANCODE_V] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE)
		{
			App->particles->AddParticle(App->particles->lob, position_player1.x + 20, position_player1.y, Collider::Type::PLAYER_SHOT);
			player1_hasTheDisk = false;
			App->audio->PlayFx(hiromiFx);
		}*/

	}

		// -- PLAYER 2 CONTROLS --

	if (!player2_hasTheDisk) {

		if ((App->input->keys[SDL_SCANCODE_J] == Key_State::KEY_REPEAT || (App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_x, 10000, 2) < 0)) && playersCanMove && playersCanMoveScore)
		{
			position_player2.x -= speed * 2;

			switch (player2_selection) {

				case 0: // Hiromi Mita (right)

					if (currentAnimation_player2 != &HiromiMita_leftAnim_right)
					{
						HiromiMita_leftAnim_right.Reset();
						currentAnimation_player2 = &HiromiMita_leftAnim_right;
					}
				
					break;

				case 1: // Jordi Costa (right)

					if (currentAnimation_player2 != &JordiCosta_leftAnim_right)
					{
						JordiCosta_leftAnim_right.Reset();
						currentAnimation_player2 = &JordiCosta_leftAnim_right;
					}
				
					break;


				case 2: // Gary Scott (right)

					if (currentAnimation_player2 != &GaryScott_leftAnim_right)
					{
						GaryScott_leftAnim_right.Reset();
						currentAnimation_player2 = &GaryScott_leftAnim_right;
					}
				
					break;
			}

		}

		if ((App->input->keys[SDL_SCANCODE_L] == Key_State::KEY_REPEAT || (App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_x, 10000, 2) > 0)) && playersCanMove && playersCanMoveScore)
		{
			position_player2.x += speed * 2;

			switch (player2_selection) {

				case 0: // Hiromi Mita (right)

					if (currentAnimation_player2 != &HiromiMita_rightAnim_right)
					{
						HiromiMita_rightAnim_right.Reset();
						currentAnimation_player2 = &HiromiMita_rightAnim_right;
					}

					break;

				case 1: // Jordi Costa (right)

					if (currentAnimation_player2 != &JordiCosta_rightAnim_right)
					{
						JordiCosta_rightAnim_right.Reset();
						currentAnimation_player2 = &JordiCosta_rightAnim_right;
					}

					break;

				case 2: // Gary Scott (right)

					if (currentAnimation_player2 != &GaryScott_rightAnim_right)
					{
						GaryScott_rightAnim_right.Reset();
						currentAnimation_player2 = &GaryScott_rightAnim_right;
					}

					break;
			}

		}

		if ((App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_REPEAT || (App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_y, 10000, 2) > 0)) && playersCanMove && playersCanMoveScore)
		{
			position_player2.y += speed * 2;

			switch (player2_selection) {

				case 0: // Hiromi Mita (right)

					if (currentAnimation_player2 != &HiromiMita_downAnim_right)
					{
						HiromiMita_downAnim_right.Reset();
						currentAnimation_player2 = &HiromiMita_downAnim_right;
					}

					break;

				case 1: // Jordi Costa (right)

					if (currentAnimation_player2 != &JordiCosta_downAnim_right)
					{
						JordiCosta_downAnim_right.Reset();
						currentAnimation_player2 = &JordiCosta_downAnim_right;
					}

					break;

				case 2: // Gary Scott (right)

					if (currentAnimation_player2 != &GaryScott_downAnim_right)
					{
						GaryScott_downAnim_right.Reset();
						currentAnimation_player2 = &GaryScott_downAnim_right;
					}

					break;
			}

		}

		if ((App->input->keys[SDL_SCANCODE_I] == Key_State::KEY_REPEAT || (App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_y, 10000, 2) < 0)) && playersCanMove && playersCanMoveScore)
		{
			position_player2.y -= speed * 2;

			switch (player2_selection) {

				case 0: // Hiromi Mita (right)

					if (currentAnimation_player2 != &HiromiMita_upAnim_right)
					{
						HiromiMita_upAnim_right.Reset();
						currentAnimation_player2 = &HiromiMita_upAnim_right;
					}

					break;

				case 1: // Jordi Costa (right)

					if (currentAnimation_player2 != &JordiCosta_upAnim_right)
					{
						JordiCosta_upAnim_right.Reset();
						currentAnimation_player2 = &JordiCosta_upAnim_right;
					}

					break;

				case 2: // Gary Scott (right)

					if (currentAnimation_player2 != &GaryScott_upAnim_right)
					{
						GaryScott_upAnim_right.Reset();
						currentAnimation_player2 = &GaryScott_upAnim_right;
					}

					break;
			}

		}

		/*if (App->input->keys[SDL_SCANCODE_PERIOD] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_I] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_L] == Key_State::KEY_REPEAT)
		{
			if (currentAnimation_player1 != &HiromiMita_dashUpRightAnim_left)
			{
				HiromiMita_dashUpRightAnim_left.Reset();
				currentAnimation_player1 = &HiromiMita_dashUpRightAnim_left;
			}
		}*/

	}

	if (player2_hasTheDisk) {

		if (((App->input->keys[SDL_SCANCODE_PERIOD] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_I] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_IDLE) || (App->input->controllers[1].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN && App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_y, 10000, 2) == 0)) && playersCanMove && playersCanMoveScore)
		{
			App->particles->AddParticle(App->particles->disk_straightLeftThrow, position_player2.x - 14, position_player2.y + 5 + 24, Collider::Type::PLAYER_SHOT);
			player2_hasTheDisk = false;
			App->audio->PlayFx(throwdisk_normal);
		}
		else if (((App->input->keys[SDL_SCANCODE_PERIOD] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_I] == Key_State::KEY_REPEAT) || (App->input->controllers[1].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN && App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_y, 10000, 2) < 0)) && playersCanMove && playersCanMoveScore)
		{
			App->particles->AddParticle(App->particles->disk_upLeftThrow, position_player2.x - 14, position_player2.y + 5 + 24, Collider::Type::PLAYER_SHOT);
			player2_hasTheDisk = false;
			App->audio->PlayFx(throwdisk_normal);
		}
		else if (((App->input->keys[SDL_SCANCODE_PERIOD] == Key_State::KEY_DOWN && App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_REPEAT) || (App->input->controllers[1].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN && App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_y, 10000, 2) > 0)) && playersCanMove && playersCanMoveScore)
		{
			App->particles->AddParticle(App->particles->disk_downLeftThrow, position_player2.x - 14, position_player2.y + 5 + 24, Collider::Type::PLAYER_SHOT);
			player2_hasTheDisk = false;
			App->audio->PlayFx(throwdisk_normal);
		}
		else if (((App->input->keys[SDL_SCANCODE_PERIOD] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_I] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_IDLE) || (App->input->controllers[1].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_IDLE && App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_y, 10000, 2) == 0)) && playersCanMove && playersCanMoveScore) {

			stop = SDL_GetTicks();

			if (stop - App->particles->start >= 1500) {

				App->particles->AddParticle(App->particles->disk_straightLeftThrow, position_player2.x - 14, position_player2.y + 5 + 24, Collider::Type::PLAYER_SHOT);
				player2_hasTheDisk = false;
				App->audio->PlayFx(throwdisk_normal);

			}

		}

		// LOB THROW: SDL_SCANCODE_V , SDL_SCANCODE_SLASH

	}

	// If no movement detected, set the current animation back to idle:

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE && App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2) == 0 && App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) == 0 && !player1_hasTheDisk) {

		switch (player1_selection) {

		case 0: // Hiromi Mita (left)

			currentAnimation_player1 = &HiromiMita_idleAnim_left;
			break;

		case 1: // Jordi Costa (left)

			currentAnimation_player1 = &JordiCosta_idleAnim_left;
			break;

		case 2: // Gary Scott (left)

			currentAnimation_player1 = &GaryScott_idleAnim_left;
			break;
		}

	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE && App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2) == 0 && App->input->reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) == 0 && player1_hasTheDisk) {

		switch (player1_selection) {

		case 0: // Hiromi Mita (left)

			switch (mapSelection) {

			case 0: //Beach

				currentAnimation_player1 = &HiromiMita_idleDiskBeachAnim_left;
				break;

			case 1: //Concrete

				currentAnimation_player1 = &HiromiMita_idleDiskConcreteAnim_left;
				break;

			case 2: //Stadium

				currentAnimation_player1 = &HiromiMita_idleDiskStadiumAnim_left;
				break;

			}

			break;

		case 1: // Jordi Costa (left)

			switch (mapSelection) {

			case 0: //Beach

				currentAnimation_player1 = &JordiCosta_idleDiskBeachAnim_left;
				break;

			case 1: //Concrete

				currentAnimation_player1 = &JordiCosta_idleDiskConcreteAnim_left;
				break;

			case 2: //Stadium

				currentAnimation_player1 = &JordiCosta_idleDiskStadiumAnim_left;
				break;

			}

			break;

		case 2: // Gary Scott (left)

			switch (mapSelection) {

			case 0: //Beach

				currentAnimation_player1 = &GaryScott_idleDiskBeachAnim_left;
				break;

			case 1: //Concrete

				currentAnimation_player1 = &GaryScott_idleDiskConcreteAnim_left;
				break;

			case 2: //Stadium

				currentAnimation_player1 = &GaryScott_idleDiskStadiumAnim_left;
				break;

			}

			break;
		}

	}

	if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_I] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_L] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_J] == Key_State::KEY_IDLE && App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_x, 10000, 2) == 0 && App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_y, 10000, 2) == 0 && !player2_hasTheDisk) {

		switch (player2_selection) {

		case 0: // Hiromi Mita (right)

			currentAnimation_player2 = &HiromiMita_idleAnim_right;
			break;

		case 1: // Jordi Costa (right)

			currentAnimation_player2 = &JordiCosta_idleAnim_right;
			break;


		case 2: // Gary Scott (right)

			currentAnimation_player2 = &GaryScott_idleAnim_right;
			break;
		}

	}

	if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_I] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_L] == Key_State::KEY_IDLE && App->input->keys[SDL_SCANCODE_J] == Key_State::KEY_IDLE && App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_x, 10000, 2) == 0 && App->input->reduce_val(SDL_IsGameController(1), App->input->controllers[1].j1_y, 10000, 2) == 0 && player2_hasTheDisk) {

		switch (player2_selection) {

		case 0: // Hiromi Mita (right)

			switch (mapSelection) {

			case 0: //Beach

				currentAnimation_player2 = &HiromiMita_idleDiskBeachAnim_right;
				break;

			case 1: //Concrete

				currentAnimation_player2 = &HiromiMita_idleDiskConcreteAnim_right;
				break;

			case 2: //Stadium

				currentAnimation_player2 = &HiromiMita_idleDiskStadiumAnim_right;
				break;

			}
	
			break;

		case 1: // Jordi Costa (right)

			switch (mapSelection) {

			case 0: //Beach

				currentAnimation_player2 = &JordiCosta_idleDiskBeachAnim_right;
				break;

			case 1: //Concrete

				currentAnimation_player2 = &JordiCosta_idleDiskConcreteAnim_right;
				break;

			case 2: //Stadium

				currentAnimation_player2 = &JordiCosta_idleDiskStadiumAnim_right;
				break;

			}

			break;


		case 2: // Gary Scott (right)

			switch (mapSelection) {

			case 0: //Beach

				currentAnimation_player2 = &GaryScott_idleDiskBeachAnim_right;
				break;

			case 1: //Concrete

				currentAnimation_player2 = &GaryScott_idleDiskConcreteAnim_right;
				break;

			case 2: //Stadium

				currentAnimation_player2 = &GaryScott_idleDiskStadiumAnim_right;
				break;

			}

			break;
		}

	}

	collider_player1->SetPos(position_player1.x, position_player1.y + 24);
	collider_player2->SetPos(position_player2.x, position_player2.y + 24);

	currentAnimation_player1->Update();
	currentAnimation_player2->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	// PLAYER 1 BLIT

	SDL_Rect rect_player1 = currentAnimation_player1->GetCurrentFrame();

	switch (player1_selection) {

		case 0: // Hiromi Mita (left)

			if (currentAnimation_player1 == &HiromiMita_idleDiskBeachAnim_left || currentAnimation_player1 == &HiromiMita_idleDiskConcreteAnim_left || currentAnimation_player1 == &HiromiMita_idleDiskStadiumAnim_left) {

				App->render->Blit(texture_player1, position_player1.x - 10, position_player1.y, &rect_player1);

			}
			else if (currentAnimation_player1 == &HiromiMita_rightAnim_left) {

				App->render->Blit(texture_player1, position_player1.x - 18, position_player1.y, &rect_player1);

			}
			else {

				App->render->Blit(texture_player1, position_player1.x, position_player1.y, &rect_player1);

			}
		
			break;

		case 1: // Jordi Costa (left)

			if (currentAnimation_player1 == &JordiCosta_idleDiskBeachAnim_left || currentAnimation_player1 == &JordiCosta_idleDiskConcreteAnim_left || currentAnimation_player1 == &JordiCosta_idleDiskStadiumAnim_left) {

				App->render->Blit(texture_player1, position_player1.x - 18, position_player1.y - 14, &rect_player1);

			}
			else if (currentAnimation_player1 == &JordiCosta_rightAnim_left) {

				App->render->Blit(texture_player1, position_player1.x - 12, position_player1.y - 14, &rect_player1);

			}
			else if (currentAnimation_player1 == &JordiCosta_upAnim_left || currentAnimation_player1 == &JordiCosta_downAnim_left) {

				App->render->Blit(texture_player1, position_player1.x - 8, position_player1.y - 14, &rect_player1);

			}
			else {

				App->render->Blit(texture_player1, position_player1.x, position_player1.y - 14, &rect_player1);

			}
		
			break;

		case 2: // Gary Scott (left)

			if (currentAnimation_player1 == &GaryScott_rightAnim_left) {

				App->render->Blit(texture_player1, position_player1.x - 12, position_player1.y - 20, &rect_player1);

			}
			else {

				App->render->Blit(texture_player1, position_player1.x, position_player1.y - 20, &rect_player1);

			}

			break;
	}

	// PLAYER 2 BLIT

	SDL_Rect rect_player2 = currentAnimation_player2->GetCurrentFrame();

	switch (player2_selection) {

		case 0: // Hiromi Mita (right)

			if (currentAnimation_player2 == &HiromiMita_idleDiskBeachAnim_right || currentAnimation_player2 == &HiromiMita_idleDiskConcreteAnim_right || currentAnimation_player2 == &HiromiMita_idleDiskStadiumAnim_right) {

				App->render->Blit(texture_player2, position_player2.x - 10, position_player2.y, &rect_player2);

			}
			else if (currentAnimation_player2 == &HiromiMita_rightAnim_right) {

				App->render->Blit(texture_player2, position_player2.x - 18, position_player2.y, &rect_player2);

			}
			else {

				App->render->Blit(texture_player2, position_player2.x, position_player2.y, &rect_player2);

			}

			break;

		case 1: // Jordi Costa (right)
			
			if (currentAnimation_player2 == &JordiCosta_leftAnim_right) {

				App->render->Blit(texture_player2, position_player2.x - 6 + 2, position_player2.y - 14, &rect_player2);

			}
			else {

				App->render->Blit(texture_player2, position_player2.x - 6, position_player2.y - 14, &rect_player2);

			}

			break;


		case 2: // Gary Scott (right)

			if (currentAnimation_player2 == &GaryScott_leftAnim_right) {

				App->render->Blit(texture_player2, position_player2.x - 4, position_player2.y - 20, &rect_player2);

			}
			else {

				App->render->Blit(texture_player2, position_player2.x - 9, position_player2.y - 20, &rect_player2);

			}

			break;
	}

	// Draw Flag

	SDL_Rect Japan = { 0,0,15,9 };
	SDL_Rect Spain = { 15,0,15,9 };
	SDL_Rect USA = { 30,0,15,9 };

	switch (player1_selection) {

		case 0: // Japan
		
			App->render->Blit(flag, 34, 9, &Japan);
			break;

		case 1: // Spain

			App->render->Blit(flag, 34, 9, &Spain);
			break;

		case 2: // USA

			App->render->Blit(flag, 34, 9, &USA);
			break;

	}

	switch (player2_selection) {

		case 0: // Japan

			App->render->Blit(flag, SCREEN_WIDTH - 77, 9, &Japan);
			break;

		case 1: // Spain

			App->render->Blit(flag, SCREEN_WIDTH - 77, 9, &Spain);
			break;

		case 2: // USA

			App->render->Blit(flag, SCREEN_WIDTH - 77, 9, &USA);
			break;

	}

	// Draw UI (score) --------------------------------------

	sprintf_s(scoreText_player1, 10, "%7d", score_player1 * 100);
	sprintf_s(scoreText_player2, 10, "%7d", score_player2 * 100);

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	// -- COLLIDERS ON ALL THE MAPS --

	switch (mapSelection) {

	case 0: // Colliders Beach

		// Player 1

		if (c1->type == Collider::Type::PLAYER_1 && c2->type == Collider::Type::NET) {

			position_player1.x = 122;

		}

		if (c1->type == Collider::Type::PLAYER_1 && c2->type == Collider::Type::UPWALL && position_player1.y < 112) {

			position_player1.y = 23;

		}

		if (c1->type == Collider::Type::PLAYER_1 && c2->type == Collider::Type::DOWNWALL && position_player1.y > 112) {

			position_player1.y = 129;

		}

		if (c1->type == Collider::Type::PLAYER_1 && (c2->type == Collider::Type::THREEPOINTS_PLAYER2 || c2->type == Collider::Type::FIVEPOINTS_PLAYER2)) {

			position_player1.x = 8;

		}

		// Player 2

		if (c1->type == Collider::Type::PLAYER_2 && c2->type == Collider::Type::NET) {

			position_player2.x = SCREEN_WIDTH - 122 - 23;

		}

		if (c1->type == Collider::Type::PLAYER_2 && c2->type == Collider::Type::UPWALL && position_player2.y < 112) {

			position_player2.y = 23;

		}

		if (c1->type == Collider::Type::PLAYER_2 && c2->type == Collider::Type::DOWNWALL && position_player2.y > 112) {

			position_player2.y = 129;

		}

		if (c1->type == Collider::Type::PLAYER_2 && (c2->type == Collider::Type::THREEPOINTS_PLAYER1 || c2->type == Collider::Type::FIVEPOINTS_PLAYER1)) {

			position_player2.x = SCREEN_WIDTH - 8 - 23;

		}

		break;

	case 1: // Colliders Concrete

		// Player 1

		if (c1->type == Collider::Type::PLAYER_1 && c2->type == Collider::Type::NET) {

			position_player1.x = 118;

		}

		if (c1->type == Collider::Type::PLAYER_1 && c2->type == Collider::Type::UPWALL && position_player1.y < 112) {

			position_player1.y = 1;

		}

		if (c1->type == Collider::Type::PLAYER_1 && c2->type == Collider::Type::DOWNWALL && position_player1.y > 112) {

			position_player1.y = 147;

		}

		if (c1->type == Collider::Type::PLAYER_1 && (c2->type == Collider::Type::THREEPOINTS_PLAYER2 || c2->type == Collider::Type::FIVEPOINTS_PLAYER2)) {

			position_player1.x = 8;

		}

		// Player 2

		if (c1->type == Collider::Type::PLAYER_2 && c2->type == Collider::Type::NET) {

			position_player2.x = SCREEN_WIDTH - 118 - 23;

		}

		if (c1->type == Collider::Type::PLAYER_2 && c2->type == Collider::Type::UPWALL && position_player2.y < 112) {

			position_player2.y = 1;

		}

		if (c1->type == Collider::Type::PLAYER_2 && c2->type == Collider::Type::DOWNWALL && position_player2.y > 112) {

			position_player2.y = 147;

		}

		if (c1->type == Collider::Type::PLAYER_2 && (c2->type == Collider::Type::THREEPOINTS_PLAYER1 || c2->type == Collider::Type::FIVEPOINTS_PLAYER1)) {

			position_player2.x = SCREEN_WIDTH - 8 - 23;

		}

		break;

	case 2: // Colliders Stadium

		// Player 1

		if (c1->type == Collider::Type::PLAYER_1 && c2->type == Collider::Type::NET) {

			position_player1.x = 123;

		}

		if (c1->type == Collider::Type::PLAYER_1 && c2->type == Collider::Type::UPWALL && position_player1.y < 112) {

			position_player1.y = 6;

		}

		if (c1->type == Collider::Type::PLAYER_1 && c2->type == Collider::Type::DOWNWALL && position_player1.y > 112) {

			position_player1.y = 146;

		}

		if (c1->type == Collider::Type::PLAYER_1 && (c2->type == Collider::Type::THREEPOINTS_PLAYER2 || c2->type == Collider::Type::FIVEPOINTS_PLAYER2)) {

			position_player1.x = 10;

		}

		// Player 2

		if (c1->type == Collider::Type::PLAYER_2 && c2->type == Collider::Type::NET) {

			position_player2.x = SCREEN_WIDTH - 123 - 23;

		}

		if (c1->type == Collider::Type::PLAYER_2 && c2->type == Collider::Type::UPWALL && position_player2.y < 112) {

			position_player2.y = 6;

		}

		if (c1->type == Collider::Type::PLAYER_2 && c2->type == Collider::Type::DOWNWALL && position_player2.y > 112) {

			position_player2.y = 146;

		}

		if (c1->type == Collider::Type::PLAYER_2 && (c2->type == Collider::Type::THREEPOINTS_PLAYER1 || c2->type == Collider::Type::FIVEPOINTS_PLAYER1)) {

			position_player2.x = SCREEN_WIDTH - 10 - 23;

		}

		break;
	}

}

bool ModulePlayer::CleanUp() {

	App->textures->Unload(flag);
	App->textures->Unload(texture_player1);
	App->textures->Unload(texture_player2);

	return true;
}