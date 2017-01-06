#include "puzzledata.h"

#include "color.h"

PuzzleData::PuzzleData()
	:m_permutationList(),
	 m_slotList(),
	 m_stickerList(),
	 m_permutationFactory(new PermutationFactory()),
	 m_slotFactory(),
	 m_puzzleRenderer(NULL),
	 m_arcMap()
{
}

void PuzzleData::addPermutation(Permutation *permutation)
{
	m_permutationList.push_back(permutation);
	m_arcMap[permutation] = vector<Arc *>(getSlotListSize(), NULL);

	for (unsigned int i = 0; i < getSlotListSize(); i++)
	{
		Slot *slotU = m_slotList[i];
		Slot *slotV = m_slotList[permutation->next(i)];
		Arc *lineArc = new LineArc(permutation, slotU, slotV);
		setArc(permutation, i, lineArc);
	}
}

void PuzzleData::render() const
{
	if (m_puzzleRenderer == NULL) return;
	
	m_puzzleRenderer->render(*this);
}

void PuzzleData::makeTestLevel()
{
	Color red(      "red", 1.0, 0.0, 0.0);
	Color yellow("yellow", 1.0, 1.0, 0.0);
	Color green(  "green", 0.0, 1.0, 0.0);
	Color blue(    "blue", 0.0, 0.0, 1.0);

	/*
	Slot *slot0 = new Slot(new Sticker(red),    vec2f(0.0, -3.0),  red);
	Slot *slot1 = new Slot(new Sticker(yellow), vec2f(0.0,  0.0),  yellow);
	Slot *slot2 = new Slot(new Sticker(green),  vec2f(-3.0,  3.0), green);
	Slot *slot3 = new Slot(new Sticker(blue),   vec2f(3.0,  3.0),  blue);
	*/

	Slot *slot0 = m_slotFactory.makeSlot(red,    vec2f( 0.0, -3.0));
	Slot *slot1 = m_slotFactory.makeSlot(yellow, vec2f( 0.0,  0.0));
	Slot *slot2 = m_slotFactory.makeSlot(green,  vec2f(-3.0,  3.0));
	Slot *slot3 = m_slotFactory.makeSlot(blue,   vec2f( 3.0,  3.0));

	Slot *slotArray[] = { slot0, slot1, slot2, slot3 };

	for (Slot *slot : slotArray)
	{
		addSlot(slot);
		Sticker *slotSticker = slot->getSticker();
		slotSticker->setSlot(slot);
		addSticker(slotSticker);
	}

	//Permutation *p0 = new Permutation(4, red, 0);
	//Permutation *p1 = new Permutation(4, blue, 1);

	//p0->setCycles({ { 0, 1 }, { 2 }, { 3 } });
	//p1->setCycles({ { 0 }, { 1, 2, 3 } });

	vector<vector<unsigned int>> cycles0({ { 0, 1 }, { 2 }, { 3 } });
	vector<vector<unsigned int>> cycles1({ { 0 }, { 1, 2, 3 } });

	Permutation *p0 = m_permutationFactory->makePermutation(4, red,  0, cycles0);
	Permutation *p1 = m_permutationFactory->makePermutation(4, blue, 1, cycles1);

	addPermutation(p0);
	addPermutation(p1);
}

Arc *PuzzleData::getArc(Permutation *permutation, unsigned int nodeIndex, bool inverted) const
{
	if (m_arcMap.count(permutation) == 0) return NULL;
	const vector<Arc *> &arcList = m_arcMap.at(permutation);
	
	const vector<unsigned int> &mapping = permutation->getMapping();
	unsigned int nextIndex = mapping[nodeIndex];
	if (inverted)
	{
		for (unsigned int i = 0; i < mapping.size(); ++i)
			if (mapping[i] == nodeIndex)
				nextIndex = i;
	}
	
	return arcList[nextIndex];
}
		
void PuzzleData::setArc(Permutation *permutation, unsigned int nodeIndex, Arc *arc)
{
	if (m_arcMap.count(permutation) == 0)
		m_arcMap[permutation] = vector<Arc *>(getSlotListSize(), NULL);
	
	m_arcMap[permutation][nodeIndex] = arc;
}
