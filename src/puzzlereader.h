#ifndef __PUZZLE_READER_H_
#define __PUZZLE_READER_H_

#include "common.h"
#include "permutationfactory.h"
#include "puzzledata.h"
#include "slotfactory.h"
#include "stickerfactory.h"

class PuzzleReader
{
public:
	PuzzleReader();
	~PuzzleReader();

	void enableDebug() { m_debugEnabled = true; }
	void readFromFile(const string &filename);

	PuzzleData *getPuzzleData() const { return m_puzzleData; }
private:
	bool m_debugEnabled;
	string m_filename;
	PuzzleData *m_puzzleData;
	vector<string> m_nodeList;
	PermutationFactory *m_permutationFactory;
	SlotFactory *m_slotFactory;
	StickerFactory *m_stickerFactory;
	map<string, Permutation *> m_permutationMap;
	float m_zoomScale;
	
	void readNode(const string &rawLine);
	int readPermutation(int numPermutations, const string &rawLine);
	void readArc(const string &rawLine);
	void readCircleArc(const vector<string> &values);
	
	vector<vector<unsigned int>> buildCycleList(const string &cycleInput);

	void split(const string &s, char delim, vector<string> &elems, unsigned int maxElems) const;
	vector<string> split(const string &s, char delim, unsigned int maxElems = 0) const;

	Color lookupColor(const string &colorName) const;
	void recenter();

	unsigned int indexOf(const string &nodeLabel) const;
};

#endif
