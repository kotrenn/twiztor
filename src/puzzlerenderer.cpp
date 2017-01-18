#include "puzzlerenderer.h"

#include "glgraphics.h"
#include "glsystem.h"

PuzzleRenderer::PuzzleRenderer()
{
}

void PuzzleRenderer::render(const PuzzleData &puzzleData) const
{
	GLSystem *glSystem = GLGraphics::getInstance()->getGLSystem();
	
	glSystem->pushMatrix(MAT_MODEL);
	glSystem->translate2fv(MAT_MODEL, puzzleData.getCenter());

	for (Permutation *permutation : *(puzzleData.getPermutationList()))
		permutation->render(*(puzzleData.getSlotList()), puzzleData.getArcList(permutation));

	for (Slot *slot : *(puzzleData.getSlotList()))
		slot->render();

	for (Sticker *sticker : *(puzzleData.getStickerList()))
		sticker->render();

	glSystem->popMatrix(MAT_MODEL);
}
