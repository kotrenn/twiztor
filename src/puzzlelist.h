#ifndef __PUZZLE_LIST_H_
#define __PUZZLE_LIST_H_

#include "puzzledata.h"
#include "puzzlerenderer.h"

class PuzzleList
{
public:
	PuzzleList();
	~PuzzleList();

	void readFromFile(const string &filename);
	
	void render() const;

	void addPuzzleData(PuzzleData *puzzleData);
	unsigned int size() const { return m_puzzleDataList.size(); }
	
	PuzzleData *getCurrentPuzzle() const;
	PuzzleData *getPuzzle(const string &name) const;
	void nextPuzzle();
	void prevPuzzle();
	void firstPuzzle();
	void lastPuzzle();
private:
	vector<PuzzleData *> m_puzzleDataList;
	unsigned int m_currentIndex;
	PuzzleRenderer m_puzzleRenderer;
};

#endif
