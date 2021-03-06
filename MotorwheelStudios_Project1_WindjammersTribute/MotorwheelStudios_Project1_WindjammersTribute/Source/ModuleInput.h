#ifndef __MODULE_INPUT_H__
#define __MODULE_INPUT_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"
#include <math.h>

#define MAX_KEYS 256
#define MAX_CONTROLLERS 2

enum Key_State
{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GameController {

	float j1_x, j1_y, j2_x, j2_y, LT, RT;
	Key_State buttons[SDL_CONTROLLER_BUTTON_MAX];

};

class ModuleInput : public Module
{
public:
	// Constructor
	ModuleInput(bool startEnabled);

	// Destructor
	~ModuleInput();

	// Called on application start.
	// Initializes the SDL system for input detection
	bool Init() override;

	// Called at the beginning of the application loop
	// Updates all input data received from SDL
	Update_Status PreUpdate() override;

	// Called on application exit.
	// Uninitializes the SDL system for input detection
	bool CleanUp() override;

public:
	// An array to fill in the state of all the keyboard keys
	Key_State keys[MAX_KEYS] = { KEY_IDLE };

	SDL_GameController* sdl_controllers[MAX_CONTROLLERS];
	GameController controllers[MAX_CONTROLLERS];
	int num_controllers;

	float reduce_val(bool controllerON, float v1, float min, float clamp_to) {

		if (controllerON) {

			float sign = v1 / fabs(v1);

			float reduced = v1 - ((fabs(v1) > min) ? sign * min : v1);

			float to_1 = reduced / (float)(SDL_MAX_SINT16);

			float reclamped = to_1 * clamp_to;

			return reclamped;

		}
		else {

			return 0;
		}
	}

};

#endif // __ModuleInput_H__