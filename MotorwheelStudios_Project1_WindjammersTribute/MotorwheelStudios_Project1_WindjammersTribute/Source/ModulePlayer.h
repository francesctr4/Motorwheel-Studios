#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SceneSelectPlayer.h"
#include "SceneSelectCourt.h"
#include "Application.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp() override;

public:
	// Position of the player in the map
	iPoint position_player1;
	iPoint position_player2;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// Flag texture
	SDL_Texture* flag = nullptr;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture_player1 = nullptr;
	SDL_Texture* texture_player2 = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation_player1 = nullptr;
	Animation* currentAnimation_player2 = nullptr;

	// A set of animations

		// -- HIROMI MITA --

	Animation HiromiMita_idleAnim_left;
	Animation HiromiMita_upAnim_left;
	Animation HiromiMita_rightAnim_left;
	Animation HiromiMita_leftAnim_left;
	Animation HiromiMita_downAnim_left;

	Animation HiromiMita_idleDiskBeachAnim_left;
	Animation HiromiMita_idleDiskBeachAnim_right;

	Animation HiromiMita_idleDiskConcreteAnim_left;
	Animation HiromiMita_idleDiskConcreteAnim_right;

	Animation HiromiMita_idleDiskStadiumAnim_left;
	Animation HiromiMita_idleDiskStadiumAnim_right;

	Animation HiromiMita_idleAnim_right;
	Animation HiromiMita_upAnim_right;
	Animation HiromiMita_rightAnim_right;
	Animation HiromiMita_leftAnim_right;
	Animation HiromiMita_downAnim_right;

		// -- JORDI COSTA --

	Animation JordiCosta_idleAnim_left;
	Animation JordiCosta_upAnim_left;
	Animation JordiCosta_rightAnim_left;
	Animation JordiCosta_leftAnim_left;
	Animation JordiCosta_downAnim_left;

	Animation JordiCosta_idleDiskBeachAnim_left;
	Animation JordiCosta_idleDiskBeachAnim_right;

	Animation JordiCosta_idleDiskConcreteAnim_left;
	Animation JordiCosta_idleDiskConcreteAnim_right;

	Animation JordiCosta_idleDiskStadiumAnim_left;
	Animation JordiCosta_idleDiskStadiumAnim_right;

	Animation JordiCosta_idleAnim_right;
	Animation JordiCosta_upAnim_right;
	Animation JordiCosta_rightAnim_right;
	Animation JordiCosta_leftAnim_right;
	Animation JordiCosta_downAnim_right;

		// -- GARY SCOTT --

	Animation GaryScott_idleAnim_left;
	Animation GaryScott_upAnim_left;
	Animation GaryScott_rightAnim_left;
	Animation GaryScott_leftAnim_left;
	Animation GaryScott_downAnim_left;

	Animation GaryScott_idleDiskBeachAnim_left;
	Animation GaryScott_idleDiskBeachAnim_right;

	Animation GaryScott_idleDiskConcreteAnim_left;
	Animation GaryScott_idleDiskConcreteAnim_right;

	Animation GaryScott_idleDiskStadiumAnim_left;
	Animation GaryScott_idleDiskStadiumAnim_right;

	Animation GaryScott_idleAnim_right;
	Animation GaryScott_upAnim_right;
	Animation GaryScott_rightAnim_right;
	Animation GaryScott_leftAnim_right;
	Animation GaryScott_downAnim_right;

	// The player's collider

	Collider* collider_player1 = nullptr;
	Collider* collider_player2 = nullptr;

	// Sound effects indices

	uint hiromiFx = 0;
	uint jordiFx = 0;
	uint garyFx = 0;

	uint throwdisk_normal = 0;
	uint throwdisk_fast_Hiromi = 0;

	Uint32 stop;

	// Font score index

	uint score_player1;
	uint score_player2;

	int scoreFont = -1;

	char scoreText_player1[10] = { "\0" };
	char scoreText_player2[10] = { "\0" };

	// Character Selection

	int player1_selection;
	int player2_selection;

	// Disk management

	bool player1_hasTheDisk;
	bool player2_hasTheDisk;

	// Map Selection

	int mapSelection;

	bool playersCanMove;
	bool playersCanMoveScore;

};

#endif //!__MODULE_PLAYER_H__