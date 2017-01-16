#include "levelselect.h"

#include "inputsystem.h"

LevelSelect::LevelSelect(Camera *camera)
	:Scene(camera),
	 KeyListener(),
	 m_puzzleList(NULL),
	 m_puzzleController(NULL)
{
	InputSystem *inputSystem = InputSystem::getInstance();
	inputSystem->addKeyListener(this);
	
	m_puzzleList = new PuzzleList();
	m_puzzleList->readFromFile("puzzlelist.txt");

	m_puzzleController = new PuzzleController(m_puzzleList->getCurrentPuzzle());
}

LevelSelect::~LevelSelect()
{
	delete m_puzzleList;
}

void LevelSelect::render(GLSystem *glSystem) const
{
	Scene::render(glSystem);

	m_puzzleList->render();
}

void LevelSelect::eventKeyUp(const SDL_KeyboardEvent &key)
{
	switch (key.keysym.sym)
	{
	case SDLK_LEFTBRACKET:  m_puzzleList->prevPuzzle(); break;
	case SDLK_RIGHTBRACKET: m_puzzleList->nextPuzzle(); break;
	case SDLK_HOME:         m_puzzleList->firstPuzzle(); break;
	case SDLK_END:          m_puzzleList->lastPuzzle(); break;
	default: break;
	}

	m_puzzleController->setPuzzleData(m_puzzleList->getCurrentPuzzle());
}
