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

	void update();
	void render(GLSystem *glSystem) const;
	
	void eventKeyUp(const SDL_KeyboardEvent &key);
private:
	PuzzleList *m_puzzleList;
	PuzzleController *m_puzzleController;
	Uint32 m_prevCameraTime;
	Uint32 m_moveDuration;
	vec2f m_cameraStartVec;
	vec2f m_cameraGoalVec;

	vec2f interpolate(float t, const vec2f &a, const vec2f &b) const;
	void moveCamera();
};

#endif
