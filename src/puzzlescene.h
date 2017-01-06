#ifndef __PUZZLE_SCENE_H_
#define __PUZZLE_SCENE_H_

#include "permutationrenderer.h"
#include "puzzledata.h"
#include "scene.h"
#include "slotrenderer.h"
#include "stickerrenderer.h"

class PuzzleScene : public Scene
{
public:
	PuzzleScene(Camera *camera, PuzzleData *puzzleData);
	virtual ~PuzzleScene();

	void move();
	void render(GLSystem *gylSystem) const;
private:
	PuzzleData *m_puzzleData;
	PermutationRenderer m_permutationRenderer;
	SlotRenderer m_slotRenderer;
	StickerRenderer m_stickerRenderer;
	vec2f m_center;
};

#endif
