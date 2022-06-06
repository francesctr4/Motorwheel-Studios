#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

#define DISK_SPEED 3
#define DISK_SPEED_STRAIGHT 4

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");

	mapSelection = App->sceneSelectCourt->map;

	switch (mapSelection) {

	case 0: //Beach

		diskPNG = App->textures->Load("Assets/Sprites/DiscosBeach.png");

		break;

	case 1: //Concrete

		diskPNG = App->textures->Load("Assets/Sprites/DiscoConcrete.png");

		break;

	case 2: //Stadium

		diskPNG = App->textures->Load("Assets/Sprites/DiscoStadium.png");

		break;

	}

	// Player 1 throw

	/*lob.anim.PushBack({0,8,17,29});
	lob.anim.PushBack({18,7,25,31});
	lob.anim.PushBack({44,6,36,34});
	lob.anim.PushBack({81,5,28,36});
	lob.anim.PushBack({110,4,21,38});
	lob.anim.PushBack({132,2,3,39});
	lob.anim.PushBack({136,2,23,41});
	lob.anim.PushBack({160,2,33,42});
	lob.anim.PushBack({194,0,43,44});
	lob.anim.pingpong = true;
	lob.speed.x = DISK_SPEED_STRAIGHT - 1;
	lob.lifetime = 180;
	lob.anim.speed = 0.3f;*/

	/*for (int i = 0; i < 17; i++) {
		lob.anim.PushBack({ 60 * i, 64, 60, 60 });
	}
	for (int i = 0; i < 17; i++) {
		lob.anim.PushBack({ 60 * i, 124, 60, 60 });
	}
	for (int i = 0; i < 17; i++) {
		lob.anim.PushBack({ 60 * i, 184, 60, 60 });
	}
	for (int i = 0; i < 11; i++) {
		lob.anim.PushBack({ 60 * i, 248, 60, 60 });
	}
	lob.speed.x = DISK_SPEED_STRAIGHT - 1;
	lob.lifetime = 180;
	lob.anim.speed = 1.0f;*/

	//SUPERSONIC RECTO

	/*supersonic.anim.PushBack({244,0,16,16});

	supersonic.anim.PushBack({261,0,25,16});
	supersonic.anim.PushBack({287,0,25,16});

	supersonic.anim.PushBack({313,0,43,16});
	supersonic.anim.PushBack({357,0,43,16});

	supersonic.anim.PushBack({401,0,61,16});
	supersonic.anim.PushBack({463,0,61,16});

	supersonic.anim.PushBack({525,0,70,16});
	supersonic.anim.PushBack({596,0,70,16});

	supersonic.anim.PushBack({667,0,70,16});
	supersonic.anim.PushBack({738,0,70,16});

	supersonic.anim.PushBack({809,0,70,16 });
	supersonic.anim.PushBack({880,0,70,16 });

	supersonic.anim.PushBack({809,0,70,16 });
	supersonic.anim.PushBack({880,0,70,16 });

	supersonic.anim.PushBack({809,0,70,16 });
	supersonic.anim.PushBack({880,0,70,16 });

	supersonic.anim.PushBack({809,0,70,16 });
	supersonic.anim.PushBack({880,0,70,16 });

	supersonic.anim.loop = false;
	supersonic.speed.x = DISK_SPEED_STRAIGHT * 1.5;
	supersonic.lifetime = 180;
	supersonic.anim.speed = 0.5f;*/

	//SUPERSONIC UP RIGHT

	/*supersonic_upRightThrow.anim.PushBack({244,0,16,16});

	supersonic_upRightThrow.anim.PushBack({ 261,0,25,16 });
	supersonic_upRightThrow.anim.PushBack({ 287,0,25,16 });

	supersonic_upRightThrow.anim.PushBack({ 313,0,43,16 });
	supersonic_upRightThrow.anim.PushBack({ 357,0,43,16 });

	supersonic_upRightThrow.anim.PushBack({ 401,0,61,16 });
	supersonic_upRightThrow.anim.PushBack({ 463,0,61,16 });

	supersonic_upRightThrow.anim.PushBack({ 525,0,70,16 });
	supersonic_upRightThrow.anim.PushBack({ 596,0,70,16 });

	supersonic_upRightThrow.anim.PushBack({ 667,0,70,16 });
	supersonic_upRightThrow.anim.PushBack({ 738,0,70,16 });

	supersonic_upRightThrow.anim.PushBack({ 809,0,70,16 });
	supersonic_upRightThrow.anim.PushBack({ 880,0,70,16 });

	supersonic_upRightThrow.anim.PushBack({ 809,0,70,16 });
	supersonic_upRightThrow.anim.PushBack({ 880,0,70,16 });

	supersonic_upRightThrow.anim.PushBack({ 809,0,70,16 });
	supersonic_upRightThrow.anim.PushBack({ 880,0,70,16 });

	supersonic_upRightThrow.anim.PushBack({ 809,0,70,16 });
	supersonic_upRightThrow.anim.PushBack({ 880,0,70,16 });

	supersonic_upRightThrow.anim.loop = false;
	supersonic_upRightThrow.speed.x = DISK_SPEED * 1.5;
	supersonic_upRightThrow.speed.y = DISK_SPEED * -1 * 1.5;
	supersonic_upRightThrow.lifetime = 180;
	supersonic_upRightThrow.anim.speed = 0.5f;*/

	//SUPERSONIC DOWN RIGHT

	/*supersonic_downRightThrow.anim.PushBack({244,0,16,16});

	supersonic_downRightThrow.anim.PushBack({ 261,0,25,16 });
	supersonic_downRightThrow.anim.PushBack({ 287,0,25,16 });

	supersonic_downRightThrow.anim.PushBack({ 313,0,43,16 });
	supersonic_downRightThrow.anim.PushBack({ 357,0,43,16 });

	supersonic_downRightThrow.anim.PushBack({ 401,0,61,16 });
	supersonic_downRightThrow.anim.PushBack({ 463,0,61,16 });

	supersonic_downRightThrow.anim.PushBack({ 525,0,70,16 });
	supersonic_downRightThrow.anim.PushBack({ 596,0,70,16 });

	supersonic_downRightThrow.anim.PushBack({ 667,0,70,16 });
	supersonic_downRightThrow.anim.PushBack({ 738,0,70,16 });

	supersonic_downRightThrow.anim.PushBack({ 809,0,70,16 });
	supersonic_downRightThrow.anim.PushBack({ 880,0,70,16 });

	supersonic_downRightThrow.anim.PushBack({ 809,0,70,16 });
	supersonic_downRightThrow.anim.PushBack({ 880,0,70,16 });

	supersonic_downRightThrow.anim.PushBack({ 809,0,70,16 });
	supersonic_downRightThrow.anim.PushBack({ 880,0,70,16 });

	supersonic_downRightThrow.anim.PushBack({ 809,0,70,16 });
	supersonic_downRightThrow.anim.PushBack({ 880,0,70,16 });

	supersonic_downRightThrow.anim.loop = false;
	supersonic_downRightThrow.speed.x = DISK_SPEED * 1.5;
	supersonic_downRightThrow.speed.y = DISK_SPEED * 1.5;
	supersonic_downRightThrow.lifetime = 180;
	supersonic_downRightThrow.anim.speed = 0.5f;*/

	for (int i = 82; i < 82 + 32 * 4; i += 32) {

		disk_straightRightThrow.anim.PushBack({ i, 48, 16, 16 });

	}
	disk_straightRightThrow.anim.loop = true;
	disk_straightRightThrow.speed.x = DISK_SPEED_STRAIGHT;
	disk_straightRightThrow.lifetime = 180;
	disk_straightRightThrow.anim.speed = 0.4f;

	for (int i = 82; i < 82 + 32 * 4; i += 32) {

		disk_upRightThrow.anim.PushBack({ i, 48, 16, 16 });

	}
	disk_upRightThrow.anim.loop = true;
	disk_upRightThrow.speed.x = DISK_SPEED;
	disk_upRightThrow.speed.y = DISK_SPEED * -1;
	disk_upRightThrow.lifetime = 180;
	disk_upRightThrow.anim.speed = 0.4f;

	for (int i = 82; i < 82 + 32 * 4; i += 32) {

		disk_downRightThrow.anim.PushBack({ i, 48, 16, 16 });

	}
	disk_downRightThrow.anim.loop = true;
	disk_downRightThrow.speed.x = DISK_SPEED;
	disk_downRightThrow.speed.y = DISK_SPEED;
	disk_downRightThrow.lifetime = 180;
	disk_downRightThrow.anim.speed = 0.4f;

	// Player 2 throw

	for (int i = 82 + 32 * 3; i >= 82; i -= 32) {

		disk_straightLeftThrow.anim.PushBack({ i, 48, 16, 16 });

	}
	disk_straightLeftThrow.anim.loop = true;
	disk_straightLeftThrow.speed.x = DISK_SPEED_STRAIGHT * -1;
	disk_straightLeftThrow.lifetime = 180;
	disk_straightLeftThrow.anim.speed = 0.4f;

	for (int i = 82 + 32 * 3; i >= 82; i -= 32) {

		disk_upLeftThrow.anim.PushBack({ i, 48, 16, 16 });

	}
	disk_upLeftThrow.anim.loop = true;
	disk_upLeftThrow.speed.x = DISK_SPEED * -1;
	disk_upLeftThrow.speed.y = DISK_SPEED * -1;
	disk_upLeftThrow.lifetime = 180;
	disk_upLeftThrow.anim.speed = 0.4f;

	for (int i = 82 + 32 * 3; i >= 82; i -= 32) {

		disk_downLeftThrow.anim.PushBack({ i, 48, 16, 16 });

	}
	disk_downLeftThrow.anim.loop = true;
	disk_downLeftThrow.speed.x = DISK_SPEED * -1;
	disk_downLeftThrow.speed.y = DISK_SPEED;
	disk_downLeftThrow.lifetime = 180;
	disk_downLeftThrow.anim.speed = 0.4f;

	WallSound = App->audio->LoadFx("Assets/Fx/WallSound.wav");
	ReceiveDisk = App->audio->LoadFx("Assets/Fx/ReceiveSound.wav");

	ThreePoints = App->audio->LoadFx("Assets/Fx/ThreePoints.wav");
	FivePoints = App->audio->LoadFx("Assets/Fx/FivePoints.wav");

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	App->textures->Unload(diskPNG);

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide

		if (particles[i] != nullptr && particles[i]->collider == c1 && (c2->type == Collider::Type::PLAYER_1 || c2->type == Collider::Type::PLAYER_2 || c2->type == Collider::Type::THREEPOINTS_PLAYER1 || c2->type == Collider::Type::FIVEPOINTS_PLAYER1 || c2->type == Collider::Type::THREEPOINTS_PLAYER2 || c2->type == Collider::Type::FIVEPOINTS_PLAYER2))
		{
			
			if (c2->type == Collider::Type::PLAYER_1) {
				
				start = SDL_GetTicks();

				App->audio->PlayFx(ReceiveDisk);
				App->player->player1_hasTheDisk = true;
				

			}

			if (c2->type == Collider::Type::PLAYER_2) {

				start = SDL_GetTicks();

				App->audio->PlayFx(ReceiveDisk);
				App->player->player2_hasTheDisk = true;
				
			}

			if (c2->type == Collider::Type::THREEPOINTS_PLAYER1) {

				App->audio->PlayFx(ThreePoints);
				App->player->score_player1 += 3;
				App->moduleScore->scoreP1 += 3;

				App->sceneCourtElements->startTimerArbit = SDL_GetTicks();
				App->sceneCourtElements->arbit_hand_player1 = true;

				App->moduleScore->arbit_throw_disk_player2 = true;
				
			}

			if (c2->type == Collider::Type::FIVEPOINTS_PLAYER1) {

				App->audio->PlayFx(FivePoints);
				App->player->score_player1 += 5;
				App->moduleScore->scoreP1 += 5;

				App->sceneCourtElements->startTimerArbit = SDL_GetTicks();
				App->sceneCourtElements->arbit_hand_player1 = true;

				App->moduleScore->arbit_throw_disk_player2 = true;

			}

			if (c2->type == Collider::Type::THREEPOINTS_PLAYER2) {

				App->audio->PlayFx(ThreePoints);
				App->player->score_player2 += 3;
				App->moduleScore->scoreP2 += 3;

				App->sceneCourtElements->startTimerArbit = SDL_GetTicks();
				App->sceneCourtElements->arbit_hand_player2 = true;

				App->moduleScore->arbit_throw_disk_player2 = false;

			}

			if (c2->type == Collider::Type::FIVEPOINTS_PLAYER2) {

				App->audio->PlayFx(FivePoints);
				App->player->score_player2 += 5;
				App->moduleScore->scoreP2 += 5;

				App->sceneCourtElements->startTimerArbit = SDL_GetTicks();
				App->sceneCourtElements->arbit_hand_player2 = true;

				App->moduleScore->arbit_throw_disk_player2 = false;

			}

			if (c2->type == Collider::Type::THREEPOINTS_PLAYER1 || c2->type == Collider::Type::FIVEPOINTS_PLAYER1 || c2->type == Collider::Type::THREEPOINTS_PLAYER2 || c2->type == Collider::Type::FIVEPOINTS_PLAYER2) {

				App->moduleScore->startTimerScore = SDL_GetTicks();
				App->moduleScore->scored = true;

			}

			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}

		if (particles[i] != nullptr && particles[i]->collider == c1 && (c2->type == Collider::Type::UPWALL || c2->type == Collider::Type::DOWNWALL || c2->type == Collider::Type::CONCRETEPIVOT))
		{
			App->audio->PlayFx(WallSound);
			particles[i]->speed.y *= -1;

			if (c2->type == Collider::Type::UPWALL) {

				App->sceneCourt->activateAnim = true;
				App->sceneCourt->currentAnimationUpWall->Reset();

				switch (mapSelection) {

					case 0: // Beach

						App->sceneCourt->currentAnimationUpWall = &App->sceneCourt->beachUpWall;

						break;

					case 1: // Concrete

						App->sceneCourt->currentAnimationUpWall = &App->sceneCourt->concreteUpWall;

						break;

					case 2: // Stadium

						App->sceneCourt->currentAnimationUpWall = &App->sceneCourt->stadiumUpWall;

						break;

				}

			}

			if (c2->type == Collider::Type::DOWNWALL) {

				App->sceneCourtElements->activateAnim = true;
				App->sceneCourtElements->currentAnimationDownWall->Reset();

				switch (mapSelection) {

					case 0: // Beach

						App->sceneCourtElements->currentAnimationDownWall = &App->sceneCourtElements->beachDownWall;

						break;

					case 1: // Concrete

						App->sceneCourtElements->currentAnimationDownWall = &App->sceneCourtElements->concreteDownWall;

						break;

					case 2: // Stadium

						App->sceneCourtElements->currentAnimationDownWall = &App->sceneCourtElements->stadiumDownWall;

						break;
	
				}

			}
				
			break;
		}

	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

      	if (particle != nullptr && particle->isAlive) {

			App->render->Blit(diskPNG, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));

		}

	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}