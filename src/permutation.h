#ifndef __PERMUTATION_H_
#define __PERMUTATION_H_

#include "color.h"
#include "common.h"
#include "permutationrenderer.h"
#include "puzzledata.h"
#include "slot.h"
#include "sticker.h"

class PermutationRenderer;
class PuzzleData;

class Permutation
{
public:
	Permutation();
	Permutation(PermutationRenderer *permutationRenderer,
	            unsigned int n, const Color &color, int index);

	void render(const vector<Slot *> &slotList, const vector<Arc *> &arcList) const;

	Color getColor() const { return m_color; }
	const vector<unsigned int> &getMapping() const { return m_mapping; }
	int getIndex() const { return m_index; }

	void setCycles(const vector<vector<unsigned int>> &cycles);
	Permutation multiply(const Permutation &rhs);
	void apply(PuzzleData *puzzleData, bool inverted);
	Permutation clone() const;

	unsigned int next(unsigned int index, bool inverted = false) const;
	
private:
	PermutationRenderer *m_permutationRenderer;
	vector<unsigned int> m_mapping;
	vector<string> m_labels;
	Color m_color;
	int m_index;
};

#endif
