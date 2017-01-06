#include "permutation.h"

#include "glgraphics.h"

Permutation::Permutation()
	:m_permutationRenderer(NULL),
	 m_mapping(),
	 m_labels(),
	 m_color(),
	 m_index(-1)
{
}

Permutation::Permutation(PermutationRenderer *permutationRenderer,
                         unsigned int n, const Color &color, int index)
	:m_permutationRenderer(permutationRenderer),
	 m_mapping(n),
	 m_labels(n),
	 m_color(color),
	 m_index(index)
{
	for (unsigned int i = 0; i < n; ++i)
	{
		m_mapping[i] = i;
		m_labels[i] = "" + (i + 1);
	}
}

void Permutation::render(const vector<Slot *> &slotList, const vector<Arc *> &arcList) const
{
	if (m_permutationRenderer == NULL) return;
	
	m_permutationRenderer->render(*this, slotList, arcList);
}

void Permutation::setCycles(const vector<vector<unsigned int>> &cycles)
{
	for (const vector<unsigned int> &cycle : cycles)
		for (unsigned int i = 0; i < cycle.size(); ++i)
		{
			unsigned int j = (i + 1) % cycle.size();
			m_mapping[cycle[i]] = cycle[j];
		}
}

Permutation Permutation::multiply(const Permutation &rhs)
{
	//assert(m_mapping.size() == rhs.m_mapping.size());

	Permutation ret(m_permutationRenderer, m_mapping.size(), m_color, m_index);
	for (unsigned int i = 0; i < m_mapping.size(); ++i)
		ret.m_mapping[i] = m_mapping[rhs.m_mapping[i]];

	return ret;
}

void Permutation::apply(PuzzleData *puzzleData, bool inverted)
{
	// Previous lists
	const vector<Sticker *> *stickerList = puzzleData->getStickerList();
	const vector<Slot *> *slotList = puzzleData->getSlotList();

	// Buffer list to construct the new list without modifying the old list
	vector<Sticker *> newStickerList(stickerList->begin(), stickerList->end());

	// Reorder newStickerList as necessary
	for (unsigned int i = 0; i < m_mapping.size(); ++i)
	{
		unsigned int j = m_mapping[i];

		// Swap indices around if inverting
		unsigned int a = i;
		unsigned int b = j;
		if (inverted) { a = j; b = i; }

		// Perform the copy
		Sticker *sticker = (*stickerList)[a];
		newStickerList[b] = sticker;
		sticker->setSlot((*slotList)[b]);
	}

	// Copy results into puzzleData
	puzzleData->setStickerList(newStickerList);
}

unsigned int Permutation::next(unsigned int index, bool inverted) const
{
	unsigned int ret = m_mapping[index];
	
	if (inverted)
		for (unsigned int i = 0; i < m_mapping.size(); ++i)
			if (m_mapping[i] == index)
				ret = i;
	
	return ret;
}

Permutation Permutation::clone() const
{
	Permutation ret(m_permutationRenderer, m_mapping.size(), m_color, m_index);

	for (unsigned int i = 0; i < m_mapping.size(); ++i)
	{
		ret.m_mapping[i] = m_mapping[i];
		ret.m_labels[i] = m_labels[i];
	}

	return ret;
}
