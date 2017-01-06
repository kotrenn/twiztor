#ifndef __PERMUTATION_RENDERER_H_
#define __PERMUTATION_RENDERER_H_

#include "arc.h"
#include "permutation.h"
#include "slot.h"

class Arc;
class Permutation;

class PermutationRenderer
{
public:
	PermutationRenderer();
	
	void render(const Permutation &permutation,
	            const vector<Slot *> &slotList,
	            const vector<Arc *> &arcList) const;
private:
};

#endif
