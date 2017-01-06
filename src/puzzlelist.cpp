#include "puzzlelist.h"

#include "puzzlereader.h"

PuzzleList::PuzzleList()
	:m_puzzleDataList(),
	 m_currentIndex(0),
	 m_puzzleRenderer()
{
}

PuzzleList::~PuzzleList()
{
	for (PuzzleData *puzzleData : m_puzzleDataList)
		delete puzzleData;
}

void PuzzleList::readFromFile(const string &filename)
{
	FILE *inFile;
	if ((inFile = fopen(filename.c_str(), "r")) == NULL)
	{
		cerr << "Error: Could not open puzzle list file " << filename << " for reading." << endl;
		return;
	}

	PuzzleReader puzzleReader;

	int len = 120;
	char buf[len + 1];
	string rawLine;
	while (fgets(buf, len, inFile) != NULL)
	{
		rawLine = string(buf);
		rawLine.pop_back(); // Clear out the newline

		cout << "Reading in puzzle " << rawLine << endl;
		//puzzleReader.enableDebug();
		puzzleReader.readFromFile(rawLine);
		PuzzleData *puzzleData = puzzleReader.getPuzzleData();
		puzzleData->setRenderer(&m_puzzleRenderer);
		addPuzzleData(puzzleData);
	}

	fclose(inFile);
}

void PuzzleList::render() const
{
	getCurrentPuzzle()->render();
}

void PuzzleList::addPuzzleData(PuzzleData *puzzleData)
{
	m_puzzleDataList.push_back(puzzleData);
}

PuzzleData *PuzzleList::getCurrentPuzzle() const
{
	return m_puzzleDataList[m_currentIndex];
}

void PuzzleList::nextPuzzle()
{
	if (m_currentIndex == size() - 1) return;
	m_currentIndex++;
}

void PuzzleList::prevPuzzle()
{
	if (m_currentIndex == 0) return;
	m_currentIndex--;
}
