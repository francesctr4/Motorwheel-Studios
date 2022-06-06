#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneMotorwheel.h"
#include "SceneNeoGeo.h"
#include "SceneDataEast.h"
#include "SceneTitle.h"
#include "SceneSelectPlayer.h"
#include "SceneSelectCourt.h"
#include "SceneVersus.h"
#include "SceneCourt.h"
#include "SceneGamePhase.h"
#include "SceneCourtElements.h"
#include "ModuleScore.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =				new ModuleWindow(true);
	modules[1] =	input =					new ModuleInput(true);
	modules[2] =	textures =				new ModuleTextures(true);
	modules[3] =	audio =					new ModuleAudio(true);

	modules[4] =	sceneMotorwheel =		new SceneMotorwheel(true);
	modules[5] =	sceneNeoGeo =			new SceneNeoGeo(false);
	modules[6] =	sceneDataEast =			new SceneDataEast(false);
	modules[7] =	sceneTitle =			new SceneTitle(false);
	modules[8] =    sceneSelectPlayer =		new SceneSelectPlayer(false);
	modules[9] =	sceneSelectCourt =		new SceneSelectCourt(false);
	modules[10] =	sceneVersus =			new SceneVersus(false);
	modules[11] =	sceneCourt =			new SceneCourt(false);		//Gameplay scene starts disabled

	modules[12] =	player =				new ModulePlayer(false);	//Player starts disabled

	modules[13] =	particles =				new ModuleParticles(false);
	modules[14] =	sceneCourtElements =	new SceneCourtElements(false);
	modules[15] =	moduleScore =			new ModuleScore(false);
	modules[16] =	sceneGamePhase =		new SceneGamePhase(false);
	modules[17] =	enemies =				new ModuleEnemies(false);	//Enemies start disabled

	modules[18] =	collisions =			new ModuleCollisions(false);
	modules[19] =	fade =					new ModuleFadeToBlack(true);
	modules[20] =	fonts =					new ModuleFonts(true);
	modules[21] =	render =				new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
