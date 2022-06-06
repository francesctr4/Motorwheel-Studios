#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::UPWALL][Collider::Type::UPWALL] = false;
	matrix[Collider::Type::UPWALL][Collider::Type::DOWNWALL] = false;
	matrix[Collider::Type::UPWALL][Collider::Type::CONCRETEPIVOT] = false;
	matrix[Collider::Type::UPWALL][Collider::Type::PLAYER_1] = true;
	matrix[Collider::Type::UPWALL][Collider::Type::PLAYER_2] = true;
	matrix[Collider::Type::UPWALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::UPWALL][Collider::Type::NET] = false;
	matrix[Collider::Type::UPWALL][Collider::Type::THREEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::UPWALL][Collider::Type::FIVEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::UPWALL][Collider::Type::THREEPOINTS_PLAYER2] = false;
	matrix[Collider::Type::UPWALL][Collider::Type::FIVEPOINTS_PLAYER2] = false;

	matrix[Collider::Type::DOWNWALL][Collider::Type::DOWNWALL] = false;
	matrix[Collider::Type::DOWNWALL][Collider::Type::UPWALL] = false;
	matrix[Collider::Type::DOWNWALL][Collider::Type::CONCRETEPIVOT] = false;
	matrix[Collider::Type::DOWNWALL][Collider::Type::PLAYER_1] = true;
	matrix[Collider::Type::DOWNWALL][Collider::Type::PLAYER_2] = true;
	matrix[Collider::Type::DOWNWALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::DOWNWALL][Collider::Type::NET] = false;
	matrix[Collider::Type::DOWNWALL][Collider::Type::THREEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::DOWNWALL][Collider::Type::FIVEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::DOWNWALL][Collider::Type::THREEPOINTS_PLAYER2] = false;
	matrix[Collider::Type::DOWNWALL][Collider::Type::FIVEPOINTS_PLAYER2] = false;

	matrix[Collider::Type::PLAYER_1][Collider::Type::UPWALL] = true;
	matrix[Collider::Type::PLAYER_1][Collider::Type::DOWNWALL] = true;
	matrix[Collider::Type::PLAYER_1][Collider::Type::CONCRETEPIVOT] = true;
	matrix[Collider::Type::PLAYER_1][Collider::Type::PLAYER_1] = false;
	matrix[Collider::Type::PLAYER_1][Collider::Type::PLAYER_2] = false;
	matrix[Collider::Type::PLAYER_1][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::PLAYER_1][Collider::Type::NET] = true;
	matrix[Collider::Type::PLAYER_1][Collider::Type::THREEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::PLAYER_1][Collider::Type::FIVEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::PLAYER_1][Collider::Type::THREEPOINTS_PLAYER2] = true;
	matrix[Collider::Type::PLAYER_1][Collider::Type::FIVEPOINTS_PLAYER2] = true;

	matrix[Collider::Type::PLAYER_2][Collider::Type::UPWALL] = true;
	matrix[Collider::Type::PLAYER_2][Collider::Type::DOWNWALL] = true;
	matrix[Collider::Type::PLAYER_2][Collider::Type::CONCRETEPIVOT] = true;
	matrix[Collider::Type::PLAYER_2][Collider::Type::PLAYER_1] = false;
	matrix[Collider::Type::PLAYER_2][Collider::Type::PLAYER_2] = false;
	matrix[Collider::Type::PLAYER_2][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::PLAYER_2][Collider::Type::NET] = true;
	matrix[Collider::Type::PLAYER_2][Collider::Type::THREEPOINTS_PLAYER1] = true;
	matrix[Collider::Type::PLAYER_2][Collider::Type::FIVEPOINTS_PLAYER1] = true;
	matrix[Collider::Type::PLAYER_2][Collider::Type::THREEPOINTS_PLAYER2] = false;
	matrix[Collider::Type::PLAYER_2][Collider::Type::FIVEPOINTS_PLAYER2] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::UPWALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::DOWNWALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::CONCRETEPIVOT] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_1] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_2] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::NET] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::THREEPOINTS_PLAYER1] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::FIVEPOINTS_PLAYER1] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::THREEPOINTS_PLAYER2] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::FIVEPOINTS_PLAYER2] = true;

	matrix[Collider::Type::NET][Collider::Type::UPWALL] = false;
	matrix[Collider::Type::NET][Collider::Type::DOWNWALL] = false;
	matrix[Collider::Type::NET][Collider::Type::CONCRETEPIVOT] = false;
	matrix[Collider::Type::NET][Collider::Type::PLAYER_1] = true;
	matrix[Collider::Type::NET][Collider::Type::PLAYER_2] = true;
	matrix[Collider::Type::NET][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::NET][Collider::Type::NET] = false;
	matrix[Collider::Type::NET][Collider::Type::THREEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::NET][Collider::Type::FIVEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::NET][Collider::Type::THREEPOINTS_PLAYER2] = false;
	matrix[Collider::Type::NET][Collider::Type::FIVEPOINTS_PLAYER2] = false; 

	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::UPWALL] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::DOWNWALL] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::CONCRETEPIVOT] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::PLAYER_1] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::PLAYER_2] = true;
	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::NET] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::THREEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::FIVEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::THREEPOINTS_PLAYER2] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER1][Collider::Type::FIVEPOINTS_PLAYER2] = false; 

	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::UPWALL] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::DOWNWALL] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::CONCRETEPIVOT] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::PLAYER_1] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::PLAYER_2] = true;
	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::NET] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::THREEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::FIVEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::THREEPOINTS_PLAYER2] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER1][Collider::Type::FIVEPOINTS_PLAYER2] = false; 

	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::UPWALL] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::DOWNWALL] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::CONCRETEPIVOT] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::PLAYER_1] = true;
	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::PLAYER_2] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::NET] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::THREEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::FIVEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::THREEPOINTS_PLAYER2] = false;
	matrix[Collider::Type::THREEPOINTS_PLAYER2][Collider::Type::FIVEPOINTS_PLAYER2] = false; 

	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::UPWALL] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::DOWNWALL] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::CONCRETEPIVOT] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::PLAYER_1] = true;
	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::PLAYER_2] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::NET] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::THREEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::FIVEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::THREEPOINTS_PLAYER2] = false;
	matrix[Collider::Type::FIVEPOINTS_PLAYER2][Collider::Type::FIVEPOINTS_PLAYER2] = false; 

	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::CONCRETEPIVOT] = false;
	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::UPWALL] = false;
	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::DOWNWALL] = false;
	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::PLAYER_1] = true;
	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::PLAYER_2] = true;
	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::NET] = false;
	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::THREEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::FIVEPOINTS_PLAYER1] = false;
	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::THREEPOINTS_PLAYER2] = false;
	matrix[Collider::Type::CONCRETEPIVOT][Collider::Type::FIVEPOINTS_PLAYER2] = false;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);
				
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debug = !debug;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::UPWALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::DOWNWALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::CONCRETEPIVOT: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::PLAYER_1: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::PLAYER_2: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::NET: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::THREEPOINTS_PLAYER1: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::THREEPOINTS_PLAYER2: // yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case Collider::Type::PLAYER_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::FIVEPOINTS_PLAYER1: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
			case Collider::Type::FIVEPOINTS_PLAYER2: // black
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
				break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}