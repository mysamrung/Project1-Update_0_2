// Including the needed files
#include "all.h"

int curScene = SCENE_NONE;
int nextScene = SCENE_TITLE;
#include "TestMap.h"
// WinMain
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	// Initializing the Game Library
	// (L"[something]") is the name displayed on the toolbar, after that, those 2 numbers are the ratio
	GameLib::init(L"�����Ńv���W�F�N�g���쐬", SCREEN_W, SCREEN_H, true);

	// GameLoop
	while (GameLib::gameLoop())
	{
		// Scene change process
		if (curScene != nextScene)
		{
			// The process following the current scene
			switch (curScene)
			{
			case SCENE_TITLE:
				test_deinit();;
				break;
			case SCENE_GAME:
				//game_deinit();
				break;
			}
			// Initialization following the next scene
			switch (nextScene)
			{
			case SCENE_TITLE:
				test_init();
				break;
			case SCENE_GAME:
				//game_init();
				break;
			}
			// Making curScene equal to nextScene
			curScene = nextScene;
		}
		
		// Input update
		input::update();

		//// Title update
		//title_update();
		//
		//// Title render
		//title_render();
		
		// Rendering and updating according to the current scene
		switch (curScene)
		{
		case SCENE_TITLE:
			test_update();
			test_render();
			break;
		//case SCENE_GAME:
		//	game_update();
		//	game_render();
		//	break;
		}
		// debug display
		debug::display(1, 1, 1, 1, 1);
		// Display
		GameLib::present(1, 0);

	}
	// Deinitialization process
	switch (curScene)
	{
	case SCENE_TITLE:
		test_deinit();
		break;
	//case SCENE_GAME:
	//	game_deinit();
	//	break;
	}
	// GameLib end process
	GameLib::uninit();
	// Return value to 0
	return 0;
}