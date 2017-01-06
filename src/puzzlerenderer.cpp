#include "puzzlerenderer.h"

#include "glgraphics.h"
#include "glsystem.h"

PuzzleRenderer::PuzzleRenderer()
{
}

void PuzzleRenderer::render(const PuzzleData &puzzleData) const
{
	//glSystem->pushMatrix(MAT_MODEL);

	//glSystem->translate2fv(m_center);

	for (Permutation *permutation : *(puzzleData.getPermutationList()))
		permutation->render(*(puzzleData.getSlotList()), puzzleData.getArcList(permutation));

	for (Slot *slot : *(puzzleData.getSlotList()))
		slot->render();

	for (Sticker *sticker : *(puzzleData.getStickerList()))
		sticker->render();

	//glSystem->popMatrix(MAT_MODEL);
}
