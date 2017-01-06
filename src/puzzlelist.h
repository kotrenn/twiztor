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
	void nextPuzzle();
	void prevPuzzle();
private:
	vector<PuzzleData *> m_puzzleDataList;
	unsigned int m_currentIndex;
	PuzzleRenderer m_puzzleRenderer;
};

#endif
