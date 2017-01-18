#ifndef __LEVEL_SELECT_H_
#define __LEVEL_SELECT_H_

#include "keylistener.h"
#include "puzzlelist.h"
#include "puzzlecontroller.h"
#include "scene.h"

class LevelSelect : public Scene, KeyListener, MouseListener
{
public:
	LevelSelect(Camera *camera);
	virtual ~LevelSelect();

	void update();
	void render(GLSystem *glSystem) const;
	
	void eventKeyUp(const SDL_KeyboardEvent &key);
	void eventMouseButtonUp(const SDL_MouseButtonEvent &mouse);

	void showCursor() { m_showingCursor = true; }
private:
	PuzzleList *m_puzzleList;
	PuzzleController *m_puzzleController;
	Uint32 m_prevCameraTime;
	Uint32 m_moveDuration;
	vec2f m_cameraStartVec;
	vec2f m_cameraGoalVec;
	bool m_showingCursor;

	float getAnimationPercentage() const;
	vec2f interpolate(float t, const vec2f &a, const vec2f &b) const;
	void renderCursor() const;
	void switchPuzzle();
};

#endif
