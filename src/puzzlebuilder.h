#ifndef __PUZZLE_BUILDER_H_
#define __PUZZLE_BUILDER_H_

#include "color.h"
#include "permutationfactory.h"
#include "puzzledata.h"
#include "slotfactory.h"
#include "stickerfactory.h"
#include "vec2f.h"

typedef enum
{
	ARC_LINE,
	ARC_CIRCLE
} ArcType;

class PuzzleBuilder
{
public:
	PuzzleBuilder();
	~PuzzleBuilder();

	void beginPuzzle(const string &name);
	PuzzleData *compilePuzzle();

	void addNode(const string &name, const Color &color, const vec2f &center);
	void addPermutation(const Color &color, const vector<vector<string>> &cycleList);

	void makeCircleArc(const Color &color,
	                   const string &src,
	                   const string &dst,
	                   const vec2f &center);
	void makeLineArc(const Color &color,
	                 const string &src,
	                 const string &dst);
private:
	PermutationFactory m_permutationFactory;
	SlotFactory m_slotFactory;
	StickerFactory m_stickerFactory;
	
	PuzzleData *m_puzzleData;
	map<string, unsigned int> m_nodeMap;
};

#endif
