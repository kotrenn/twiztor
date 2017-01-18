#ifndef __PUZZLE_LIST_H_
#define __PUZZLE_LIST_H_

#include "puzzledata.h"
#include "puzzlerenderer.h"

class PuzzleList
{
public:
	PuzzleList();
	~PuzzleList();

	void readPuzzlesFromFile(const string &filename);
	void readWorldFromFile(const string &filename);
	
	void render() const;

	void addPuzzleData(PuzzleData *puzzleData);
	unsigned int size() const { return m_puzzleDataList.size(); }
	
	PuzzleData *getCurrentPuzzle() const;
	PuzzleData *getPuzzle(const string &name) const;

	void nextPuzzle(unsigned int skip=1);
	void prevPuzzle(unsigned int skip=1);
	void firstPuzzle();
	void lastPuzzle();
	void nearestPuzzle(const vec2f &loc);
private:
	vector<PuzzleData *> m_puzzleDataList;
	unsigned int m_currentIndex;
	PuzzleRenderer m_puzzleRenderer;
};

#endif
