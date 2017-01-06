#ifndef __LEVEL_SELECT_H_
#define __LEVEL_SELECT_H_

#include "keylistener.h"
#include "puzzlelist.h"
#include "puzzlecontroller.h"
#include "scene.h"

class LevelSelect : public Scene, KeyListener
{
public:
	LevelSelect(Camera *camera);
	virtual ~LevelSelect();

	void render(GLSystem *glSystem) const;
	
	void eventKeyUp(const SDL_KeyboardEvent &key);
private:
	PuzzleList *m_puzzleList;
	PuzzleController *m_puzzleController;
};

#endif
