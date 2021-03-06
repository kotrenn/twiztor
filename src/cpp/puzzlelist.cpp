#include "puzzlelist.h"

#include "glgraphics.h"
#include "puzzlereader.h"

PuzzleList::PuzzleList(Camera *camera)
	:m_camera(camera),
	 m_puzzleDataList(),
	 m_currentIndex(0),
	 m_puzzleRenderer()
{
}

PuzzleList::~PuzzleList()
{
	for (PuzzleData *puzzleData : m_puzzleDataList)
		delete puzzleData;
}

void PuzzleList::readPuzzlesFromFile(const string &filename)
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

		//cout << "Reading in puzzle " << rawLine << endl;
		//puzzleReader.enableDebug();
		puzzleReader.readFromFile(rawLine);
		PuzzleData *puzzleData = puzzleReader.getPuzzleData();
		puzzleData->setRenderer(&m_puzzleRenderer);
		addPuzzleData(puzzleData);
	}

	fclose(inFile);
}

void PuzzleList::readWorldFromFile(const string &filename)
{
	FILE *inFile;
	if ((inFile = fopen(filename.c_str(), "r")) == NULL)
	{
		cerr << "Error: Could not open world file " << filename << " for reading." << endl;
		return;
	}

	int len = 120;
	char buf[len + 1];
	string rawLine;
	set<string> visitedPuzzles;
	vec2f maxDist(0.0, 0.0);
	float padding = 2.0;
	while (fgets(buf, len, inFile) != NULL)
	{
		rawLine = string(buf);
		rawLine.pop_back(); // Clear out the newline
		vector<string> values = split(rawLine, ' ');
		string puzzleName = values[0];
		float puzzleX = stof(values[1]);
		float puzzleY = stof(values[2]);
		vec2f puzzleCenter = padding * vec2f(puzzleX, puzzleY);
		PuzzleData *puzzleData = getPuzzle(puzzleName);
		if (puzzleData == NULL) continue;
		puzzleData->setCenter(puzzleCenter);
		visitedPuzzles.insert(puzzleName);
		if (maxDist.getNorm() < puzzleCenter.getNorm())
			maxDist = puzzleCenter;
	}

	fclose(inFile);

	unsigned int curPuzzle = 0;
	vec2f offset = 2.0 * padding * maxDist.getUnit();
	for (PuzzleData *puzzleData : m_puzzleDataList)
	{
		if (visitedPuzzles.count(puzzleData->getName()) == 0)
		{
			curPuzzle++;
			vec2f newCenter = maxDist + curPuzzle * offset;
			puzzleData->setCenter(newCenter);
		}
	}
}

void PuzzleList::render() const
{
	GLGraphics *glGraphics = GLGraphics::getInstance();

	unsigned int count = 0;
	for (PuzzleData *puzzleData : m_puzzleDataList)
		if (inViewingRange(puzzleData))
		{
			puzzleData->render();
			count++;
		}

	PuzzleData *currentPuzzle = getCurrentPuzzle();
	vec2f center = currentPuzzle->getCenter();
	glGraphics->setColor(1.0, 0.0, 0.0);
	glGraphics->drawCircle(center, 1.4);
}

void PuzzleList::addPuzzleData(PuzzleData *puzzleData)
{
	m_puzzleDataList.push_back(puzzleData);
}

PuzzleData *PuzzleList::getCurrentPuzzle() const
{
	return m_puzzleDataList[m_currentIndex];
}

PuzzleData *PuzzleList::getPuzzle(const string &name) const
{
	for (PuzzleData *puzzleData : m_puzzleDataList)
		if (puzzleData->getName() == name)
			return puzzleData;

	return NULL;
}

void PuzzleList::nextPuzzle(unsigned int skip)
{
	if (m_currentIndex >= size() - skip)
		m_currentIndex = size() - 1;
	else
		m_currentIndex += skip;
}

void PuzzleList::prevPuzzle(unsigned int skip)
{
	if (m_currentIndex < skip)
		m_currentIndex = 0;
	else
		m_currentIndex -= skip;
}

void PuzzleList::firstPuzzle()
{
	m_currentIndex = 0;
}

void PuzzleList::lastPuzzle()
{
	m_currentIndex = m_puzzleDataList.size() - 1;
}

void PuzzleList::nearestPuzzle(const vec2f &loc)
{
	if (size() == 0) return;

	m_currentIndex = 0;
	vec2f startCenter = getCurrentPuzzle()->getCenter();
	float minDist = (startCenter - loc).getNorm();
	for (unsigned int i = 1; i < m_puzzleDataList.size(); ++i)
	{
		PuzzleData *puzzleData = m_puzzleDataList[i];
		vec2f center = puzzleData->getCenter();
		float dist = (center - loc).getNorm();
		if (dist < minDist)
		{
			m_currentIndex = i;
			minDist = dist;
		}
	}
}

bool PuzzleList::inViewingRange(PuzzleData *puzzleData) const
{
	vec2f puzzleCenter = puzzleData->getCenter();
	vec2f cameraCenter = m_camera->getCenter();
	float maxDistance = m_camera->getZoomFactor();
	return (puzzleCenter - cameraCenter).getNorm() < maxDistance;
}
