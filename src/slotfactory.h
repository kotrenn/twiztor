#ifndef __SLOT_FACTORY_H_
#define __SLOT_FACTORY_H_

#include "slot.h"
#include "stickerfactory.h"

class SlotFactory
{
public:
	SlotFactory();
	~SlotFactory();

	Slot *makeSlot(const Color &color, const vec2f &center);
private:
	SlotRenderer m_slotRenderer;
	StickerFactory m_stickerFactory;
};

#endif
