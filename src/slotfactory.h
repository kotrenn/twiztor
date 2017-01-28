#ifndef __SLOT_FACTORY_H_
#define __SLOT_FACTORY_H_

#include "slot.h"
#include "slotrenderer.h"
#include "stickerfactory.h"

class SlotRenderer;
class StickerFactory;

class SlotFactory
{
public:
	SlotFactory();
	~SlotFactory();

	Slot *makeSlot(const Color &color, const vec2f &center);
private:
	SlotRenderer *m_slotRenderer;
	StickerFactory *m_stickerFactory;
};

#endif
