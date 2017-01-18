#include "gldata.h"
#include "glgraphics.h"
#include "inputsystem.h"
#include "levelselect.h"
#include "puzzlecontroller.h"
#include "puzzlereader.h"
#include "puzzlescene.h"
#include "singletonmanager.h"

int main(int, char **)
{
	GLData glData;
	GLSystem glSystem;
	if (!glData.init())
	{
		printf("Failed to initialize");
	}
	else
	{
		bool quit = false;
		
		SingletonManager singletonManager();
		InputSystem *inputSystem = InputSystem::getInstance();;
		GLGraphics *glGraphics = GLGraphics::getInstance();
		glGraphics->setGLData(&glData);
		glGraphics->setGLSystem(&glSystem);

		bool testLevel = false;
		PuzzleData *puzzleData = NULL;

		if (testLevel)
		{
			puzzleData = new PuzzleData("test");
			puzzleData->makeTestLevel();
		}
		else
		{
			PuzzleReader puzzleReader;
			//puzzleReader.enableDebug();
			puzzleReader.readFromFile("puzzles/ABJ.txt");
			puzzleData = puzzleReader.getPuzzleData();
		}

		PuzzleRenderer *puzzleRenderer = new PuzzleRenderer();
		puzzleData->setRenderer(puzzleRenderer);
			
		Camera *camera = new Camera();
		//Scene *scene = new PuzzleScene(camera, puzzleData);
		Scene *scene = new LevelSelect(camera);
		if (!scene->init(glData)) quit = true;
		//PuzzleController *puzzleController = new PuzzleController(puzzleData);
		
		//Enable text input
		SDL_StartTextInput();

		//While application is running
		while( !quit )
		{
			quit = inputSystem->processEvents();

			scene->update();

			//Render scene
			glSystem.loadAllIdentities();
			glData.render(scene);
			
			//Update screen
			SDL_GL_SwapWindow( glData.getWindow() );
		}

		delete puzzleRenderer;
		//delete puzzleController;
		delete scene;
		delete camera;
		delete puzzleData;
		
		//Disable text input
		SDL_StopTextInput();
	}

	glData.close();

	return 0;
}
