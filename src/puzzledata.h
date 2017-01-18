#ifndef __PUZZLE_DATA_H_
#define __PUZZLE_DATA_H_

#include "arc.h"
#include "common.h"
#include "permutation.h"
#include "permutationfactory.h"
#include "puzzlerenderer.h"
#include "slot.h"
#include "slotfactory.h"
#include "sticker.h"

class Arc;
class Permutation;
class PermutationFactory;
class PuzzleRenderer;

class PuzzleData
{
public:
	PuzzleData(const string &name);

	string getName() const { return m_name; }

	void setRenderer(PuzzleRenderer *puzzleRenderer) { m_puzzleRenderer = puzzleRenderer; }
	void render() const;
	
	void addPermutation(Permutation *permutation);
	void addSlot(Slot *slot) { m_slotList.push_back(slot); }
	void addSticker(Sticker *sticker) { m_stickerList.push_back(sticker); }

	void clearSlotList() { m_slotList.clear(); }
	void clearStickerList() { m_stickerList.clear(); }

	const vector<Permutation *> *getPermutationList() const { return &m_permutationList; }
	const vector<Slot *> *getSlotList() const { return &m_slotList; }
	const vector<Sticker *> *getStickerList() const { return &m_stickerList; }

	unsigned int getPermutationListSize() const { return m_permutationList.size(); }
	unsigned int getSlotListSize() const { return m_slotList.size(); }
	unsigned int getStickerListSize() const { return m_stickerList.size(); }

	void setPermutationList(const vector<Permutation *> &permutationList) { m_permutationList = permutationList; }
	void setSlotList(const vector<Slot *> &slotList) { m_slotList = slotList; }
	void setStickerList(const vector<Sticker *> &stickerList) { m_stickerList = stickerList; }

	Permutation *getPermutation(unsigned int index) const { return m_permutationList[index]; }
	Slot *getSlot(unsigned int index) const { return m_slotList[index]; }
	Sticker *getSticker(unsigned int index) const { return m_stickerList[index]; }

	Arc *getArc(Permutation *permutation, unsigned int nodeIndex, bool inverted) const;
	void setArc(Permutation *permutation, unsigned int nodeIndex, Arc *arc);
	vector<Arc *> getArcList(Permutation *permutation) const { return m_arcMap.at(permutation); }

	vec2f getCenter() const { return m_center; }
	void setCenter(const vec2f &center) { m_center = center; }

	void makeTestLevel();
	
private:
	string m_name;
	vector<Permutation *> m_permutationList;
	vector<Slot *> m_slotList;
	vector<Sticker *> m_stickerList;
	PermutationFactory *m_permutationFactory;
	SlotFactory m_slotFactory;
	PuzzleRenderer *m_puzzleRenderer;
	map<Permutation *, vector<Arc *>> m_arcMap;
	vec2f m_center;
};

#endif
