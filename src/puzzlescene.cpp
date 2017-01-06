#include "puzzlescene.h"

PuzzleScene::PuzzleScene(Camera *camera, PuzzleData *puzzleData)
	:Scene(camera),
	 m_puzzleData(puzzleData),
	 m_permutationRenderer(),
	 m_slotRenderer(),
	 m_stickerRenderer(),
	 m_center(0.0, 0.0)
{
}

PuzzleScene::~PuzzleScene()
{
}

void PuzzleScene::move()
{
	Scene::move();

	for (Sticker *sticker : *(m_puzzleData->getStickerList()))
		sticker->move(m_previousTimeDelta);
}

void PuzzleScene::render(GLSystem *glSystem) const
{
	Scene::render(glSystem);

	glSystem->pushMatrix(MAT_MODEL);

	glSystem->translate2fv(m_center);

	/*
	for (Permutation *permutation : *(m_puzzleData->getPermutationList()))
		m_permutationRenderer.render(*permutation, *(m_puzzleData->getSlotList()), m_puzzleData->getArcList(permutation));

	for (Slot *slot : *(m_puzzleData->getSlotList()))
		m_slotRenderer.render(*slot);

	for (Sticker *sticker : *(m_puzzleData->getStickerList()))
		m_stickerRenderer.render(*sticker);
	*/

	glSystem->popMatrix(MAT_MODEL);
}
