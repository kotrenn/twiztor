#ifndef __SLOT_RENDERER_H_
#define __SLOT_RENDERER_H_

#include "slot.h"

class Slot;

class SlotRenderer
{
public:
	SlotRenderer();

	void render(const Slot &slot) const;
private:
};

#endif
