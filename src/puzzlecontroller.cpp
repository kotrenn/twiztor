#include "puzzlecontroller.h"

#include "inputsystem.h"

PuzzleController::PuzzleController(PuzzleData *puzzleData)
	:KeyListener(),
	 m_puzzleData(puzzleData),
	 m_puzzleActionStorage(new PuzzleActionStorage())
{
	InputSystem *inputSystem = InputSystem::getInstance();
	inputSystem->addKeyListener(this);
}

PuzzleController::~PuzzleController()
{
	delete m_puzzleActionStorage;
}

void PuzzleController::activatePermutation(unsigned int index)
{
	activatePermutation(index, false);
}

void PuzzleController::activatePermutation(unsigned int index, bool inverted)
{
	if (index >= m_puzzleData->getPermutationListSize()) return;

	Permutation *permutation = (*m_puzzleData->getPermutationList())[index];
	permutation->apply(m_puzzleData, inverted);
}

void PuzzleController::solve()
{
	for (Sticker *sticker : *(m_puzzleData->getStickerList()))
		sticker->setColor(sticker->getSlot()->getColor());
}

void PuzzleController::randomize()
{
	unsigned int numPermutations = m_puzzleData->getPermutationListSize();
	for (int i = 0; i < 1000; ++i)
	{
		unsigned int randomIndex = rand() % numPermutations;
		bool randomInverted = rand() % 2;
		activatePermutation(randomIndex, randomInverted);
	}
}

void PuzzleController::eventKeyUp(const SDL_KeyboardEvent &key)
{
	bool inverted = false;
	
	if (key.keysym.mod & KMOD_LSHIFT) inverted = true;
	if (key.keysym.mod & KMOD_RSHIFT) inverted = true;
	
	switch (key.keysym.sym)
	{
	case SDLK_1: activatePermutation(0, inverted); break;
	case SDLK_2: activatePermutation(1, inverted); break;
	case SDLK_3: activatePermutation(2, inverted); break;
	case SDLK_4: activatePermutation(3, inverted); break;
	case SDLK_5: activatePermutation(4, inverted); break;
	case SDLK_6: activatePermutation(5, inverted); break;
	case SDLK_7: activatePermutation(6, inverted); break;
	case SDLK_8: activatePermutation(7, inverted); break;
	case SDLK_9: activatePermutation(8, inverted); break;
	case SDLK_0: activatePermutation(9, inverted); break;
	case SDLK_r: randomize(); break;
	case SDLK_s: solve(); break;
	default: break;
	}
}
