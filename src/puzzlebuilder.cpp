#include "puzzlebuilder.h"

PuzzleBuilder::PuzzleBuilder()
	:m_permutationFactory(),
	 m_slotFactory(),
	 m_stickerFactory(),
	 m_puzzleData(NULL),
	 m_nodeMap()
{
}

PuzzleBuilder::~PuzzleBuilder()
{
}

void PuzzleBuilder::beginPuzzle(const string &name)
{
	m_puzzleData = new PuzzleData(name);
}

PuzzleData *PuzzleBuilder::compilePuzzle()
{
	return m_puzzleData;
}

void PuzzleBuilder::addNode(const string &name, const Color &color, const vec2f &center)
{
	Sticker *newSticker = m_stickerFactory.makeSticker(color);
	Slot *newSlot = m_slotFactory.makeSlot(color, center);
	newSticker->moveToSlot(newSlot);

	m_puzzleData->addSlot(newSlot);
	m_puzzleData->addSticker(newSticker);

	if (m_nodeMap.find(name) == m_nodeMap.end())
		m_nodeMap[name] = m_nodeMap.size();
}

void PuzzleBuilder::addPermutation(const Color &color, const vector<vector<string>> &cycleList)
{
	vector<vector<unsigned int>> indexedCycleList;
	
	for (const vector<string> &cycle : cycleList)
	{
		vector<unsigned int> indexedCycle;
		
		for (const string &name : cycle)
		{
			unsigned int index = m_nodeMap[name];
			indexedCycle.push_back(index);
		}
		
		indexedCycleList.push_back(indexedCycle);
	}
	
	m_permutationFactory.makePermutation(m_nodeMap.size(),
	                                     color,
	                                     0,
	                                     indexedCycleList);

	// TODO: PuzzleBuilder::addPermutation() : make a default line arc
}

void PuzzleBuilder::makeCircleArc(const Color &,
                                  const string &,
                                  const string &,
                                  const vec2f &)
{
	// TODO: PuzzleBuilder::makeCircleArc()
}

void PuzzleBuilder::makeLineArc(const Color &,
                                const string &,
                                const string &)
{
	// TODO: PuzzleBuilder::makeLineArc()
}
