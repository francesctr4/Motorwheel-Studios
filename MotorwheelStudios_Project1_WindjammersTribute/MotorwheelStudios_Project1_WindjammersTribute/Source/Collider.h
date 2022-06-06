#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 5

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,

		CONCRETEPIVOT,
		UPWALL,
		DOWNWALL,
		PLAYER_1,
		PLAYER_2,
		PLAYER_SHOT, //DISK
		NET,
		THREEPOINTS_PLAYER1,
		FIVEPOINTS_PLAYER1,
		THREEPOINTS_PLAYER2,
		FIVEPOINTS_PLAYER2,

		ENEMY,
		ENEMY_SHOT,
		
		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__

