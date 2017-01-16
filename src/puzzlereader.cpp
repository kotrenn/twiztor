#include "puzzlereader.h"

PuzzleReader::PuzzleReader()
	:m_debugEnabled(false),
	 m_filename(""),
	 m_puzzleData(NULL),
	 m_nodeList(),
	 m_permutationFactory(new PermutationFactory()),
	 m_slotFactory(new SlotFactory()),
	 m_stickerFactory(new StickerFactory()),
	 m_permutationMap(),
	 m_zoomScale(0.1)
{
}

PuzzleReader::~PuzzleReader()
{
	delete m_permutationFactory;
	delete m_slotFactory;
	delete m_stickerFactory;
}

void PuzzleReader::readFromFile(const string &filename)
{
	m_filename = filename;
	m_nodeList.clear();

	FILE *inFile;
	if ((inFile = fopen(filename.c_str(), "r")) == NULL)
	{
		cerr << "Error: Could not open puzzle " << filename << " for reading." << endl;
		return;
	}

	m_puzzleData = new PuzzleData();

	int numPermutations = 0;
	int len = 1200;
	char buf[len + 1];
	string rawLine;
	//while (fscanf(inFile, "%s", buf) > 0)
	while (fgets(buf, len, inFile) != NULL)
	{
		rawLine = string(buf);
		
		if (m_debugEnabled)
			cout << "rawLine = \"" << rawLine << "\"" << endl;

		vector<string> rawLineWords = split(rawLine, ' ');
		if (rawLineWords.size() == 0) continue;
		string header = rawLineWords[0];
		
		if (header == "node")
			readNode(rawLine);
		else if (header == "permutation")
			numPermutations = readPermutation(numPermutations, rawLine);
		else if (header == "arc")
			readArc(rawLine);
	}

	fclose(inFile);

	recenter();
}

void PuzzleReader::readNode(const string &rawLine)
{
	vector<string> values = split(rawLine, ' ');
	string nodeName = values[1];
	Color nodeColor = lookupColor(values[2]);
	float nodeX = m_zoomScale * stoi(values[3]);
	float nodeY = m_zoomScale * stoi(values[4]);
	string nodeSticker = values[5];
	Sticker *newSticker = m_stickerFactory->makeSticker(nodeColor);
	Slot *newSlot = m_slotFactory->makeSlot(nodeColor, vec2f(nodeX, nodeY));
	newSticker->setSlot(newSlot);
	m_puzzleData->addSlot(newSlot);
	m_puzzleData->addSticker(newSticker);
	m_nodeList.push_back(nodeName);
	if (m_debugEnabled)
		cout << "Added node " << nodeName << ": " << nodeColor
		     << " " << nodeX << " " << nodeY << endl;
}

int PuzzleReader::readPermutation(int numPermutations, const string &rawLine)
{
	vector<string> values = split(rawLine, ' ', 3);
	string permutationColor = values[1];
	Color permutationColorName = lookupColor(permutationColor);

	// Now build a cycle
	string cycleList = values[2];
	if (m_debugEnabled)
		cout << "Found cycle list: " << cycleList << endl;
	
	vector<vector<unsigned int>> cycles = buildCycleList(cycleList);
	unsigned int numSlots = m_nodeList.size();
	//Permutation *newPermutation = new Permutation(numSlots, permutationColorName, numPermutations);
	Permutation *newPermutation = m_permutationFactory->makePermutation(numSlots,
	                                                                    permutationColorName,
	                                                                    numPermutations,
	                                                                    cycles);
	numPermutations++;
	//newPermutation->setCycles(cycles);
	m_puzzleData->addPermutation(newPermutation);
	m_permutationMap[permutationColor] = newPermutation;
	
	if (m_debugEnabled)
		cout << "Added permutation: " << permutationColorName << endl;
	
	return numPermutations;
}

void PuzzleReader::readArc(const string &rawLine)
{
	vector<string> values = split(rawLine, ' ');

	if (values[1] == "circle") readCircleArc(values);
}

void PuzzleReader::readCircleArc(const vector<string> &values)
{
	// TODO: PuzzleReader: Remove destination of an arc in the specification (all arc types)
	string arcColor = values[2];
	string nodeU = values[3];
	string nodeV = values[4];
	float circleR = m_zoomScale * stof(values[5]);
	bool circlePlus = values[6][0] == '+';
	bool circleInverted = values[6][1] == '+';

	if (m_debugEnabled)
		cout << "Building circle arc on permutation " << arcColor
		     << " from node " << nodeU << " to " << nodeV
		     << " with radius " << circleR << ", plus = "
		     << boolalpha << circlePlus << ", inverted = "
		     << circleInverted << endl;

	Permutation *permutation = m_permutationMap[arcColor];
	unsigned int indexU = indexOf(nodeU);
	unsigned int indexV = indexOf(nodeV);
	Slot *slotU = m_puzzleData->getSlot(indexU);
	Slot *slotV = m_puzzleData->getSlot(indexV);
	CircleArc *circleArc = new CircleArc(permutation, slotU, slotV,
	                                     circleR, circlePlus, circleInverted);
	m_puzzleData->setArc(permutation, indexU, circleArc);

	if (m_debugEnabled)
	{
		cout << "  indexU = " << indexU << endl;
		cout << "  indexV = " << indexV << endl;
	}
}

vector<vector<unsigned int>> PuzzleReader::buildCycleList(const string &cycleInput)
{
	vector<vector<unsigned int>> cycleList;
	vector<unsigned int> currentCycle;
	int bracketCount = 0;
	for (unsigned int i = 0; i < cycleInput.size(); ++i)
	{
		char curChar = cycleInput[i];
		if (curChar == '[')
		{
			if (m_debugEnabled)
				cout << "Found [ @" << i << endl;

			bracketCount++;
			if (bracketCount > 1) currentCycle.clear();
		}
		else if (curChar == ']')
		{
			if (m_debugEnabled)
				cout << "Found ]" << endl;

			bracketCount--;
			if (bracketCount > 0)
			{
				/*
				unsigned int cycleArray[] = currentCycle.stream().mapToInt(j -> j).toArray();
				cycleList.push_back(cycleArray);
				*/
				cycleList.push_back(currentCycle);
				
				if (m_debugEnabled)
				{
					string cycleStr = "";
					for (unsigned int val : currentCycle)
						cycleStr += to_string(val) + " ";
					cout << "Added basic cycle " << cycleStr << endl;
				}
				
				currentCycle.clear();
			}
		}
		else if (curChar != ' ' && curChar != '\n')
		{
			if (bracketCount == 1) continue;

			string currentLabel = "";
			while (cycleInput[i] != ',' && cycleInput[i] != ']')
			{
				currentLabel += cycleInput[i];
				i++;
			}

			unsigned int index = indexOf(currentLabel);
			currentCycle.push_back(index);

			if (m_debugEnabled)
			{
				cout << "Added node " << currentLabel << " @" << index << endl;
				cout << "i = " << i << endl;
				cout << "str[i] = " << cycleInput[i] << endl;
			}

			if (cycleInput[i] == ']') i--;
		}
	}

	return cycleList;
}

unsigned int PuzzleReader::indexOf(const string &nodeLabel) const
{
	unsigned int index = m_nodeList.size() * 2;
	for (unsigned int j = 0; j < m_nodeList.size(); ++j)
		if (m_nodeList[j] == nodeLabel)
			index = j;
	if (index > m_nodeList.size()) cerr << "Warning: index = " << index << endl;
	return index;
}

// http://stackoverflow.com/a/236803
void PuzzleReader::split(const string &s,
                         char delim,
                         vector<string> &elems,
                         unsigned int maxElems) const
{
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
		if (maxElems > 0 && elems.size() + 1 == maxElems)
			delim = '|';
	}
}

// http://stackoverflow.com/a/236803
vector<string> PuzzleReader::split(const string &s,
                                   char delim,
                                   unsigned int maxElems) const
{
	//cout << "split(\"" << s << "\", " << maxElems << ")" << endl;
	vector<string> elems;
	split(s, delim, elems, maxElems);
	//for (string tok : elems)
	//	cout << "  elem: \"" << tok << "\"" << endl;
	return elems;
}

Color PuzzleReader::lookupColor(const string &colorName) const
{
	Color ret(colorName, 1.0, 1.0, 1.0);
	if (colorName == "red")                 ret.setRGB(1.0, 0.0, 0.0);
	else if (colorName == "orange")         ret.setRGB(1.0, 0.5, 0.0);
	else if (colorName == "yellow")         ret.setRGB(1.0, 1.0, 0.0);
	else if (colorName == "green")          ret.setRGB(0.0, 1.0, 0.0);
	else if (colorName == "cyan")           ret.setRGB(0.0, 1.0, 1.0);
	else if (colorName == "blue")           ret.setRGB(0.0, 0.0, 1.0);
	else if (colorName == "magenta")        ret.setRGB(1.0, 0.0, 1.0);
	else if (colorName == "purple")         ret.setRGB(0.5, 0.0, 0.5);
	else if (colorName == "gray")           ret.setRGB(0.5, 0.5, 0.5);
	else if (colorName == "grey")           ret.setRGB(0.5, 0.5, 0.5);
	else if (colorName == "black")          ret.setRGB(0.0, 0.0, 0.0);
	else if (colorName == "white")          ret.setRGB(1.0, 1.0, 1.0);
	else if (colorName == "darkred")        ret.setRGB(0.5, 0.0, 0.0);
	else if (colorName == "darkgreen")      ret.setRGB(0.0, 0.5, 0.0);
	else if (colorName == "darkblue")       ret.setRGB(0.0, 0.0, 0.5);
	else if (colorName == "cornflowerblue") ret.setRGB(0.392, 0.584, 0.929);
	else if (colorName == "brown")          ret.setRGB(0.647, 0.165, 0.165);
	else if (colorName == "darkseagreen")   ret.setRGB(0.561, 0.737, 0.561);
	else if (colorName == "darkorchid")     ret.setRGB(0.600, 0.196, 0.800);
	else if (colorName == "yellowgreen")    ret.setRGB(0.604, 0.804, 0.196);
	else if (colorName == "turquoise4")     ret.setRGB(0.000, 0.525, 0.545);
	else if (colorName == "violet")         ret.setRGB(0.933, 0.510, 0.933);
	else if (colorName == "violetred")      ret.setRGB(0.816, 0.125, 0.565);
	else if (colorName == "violetred4")     ret.setRGB(0.545, 0.133, 0.322);
	return ret;
}

void PuzzleReader::recenter()
{
	vec2f centerSum(0.0, 0.0);
	
	for (Slot *slot : *(m_puzzleData->getSlotList()))
	{
		vec2f slotCenter = slot->getCenter();
		centerSum += slotCenter;
	}

	centerSum /= m_puzzleData->getSlotListSize();

	for (Slot *slot : *(m_puzzleData->getSlotList()))
	{
		vec2f slotCenter = slot->getCenter();
		slotCenter -= centerSum;
		slot->setCenter(slotCenter);
	}

	for (Permutation *permutation : *(m_puzzleData->getPermutationList()))
		for (Arc *arc : m_puzzleData->getArcList(permutation))
			arc->adjustCenter(centerSum);
}
