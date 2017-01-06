#include "slotfactory.h"

SlotFactory::SlotFactory()
	:m_slotRenderer(),
	 m_stickerFactory()
{
}

SlotFactory::~SlotFactory()
{
}

Slot *SlotFactory::makeSlot(const Color &color, const vec2f &center)
{
	Sticker *sticker = m_stickerFactory.makeSticker(color);
	Slot *slot = new Slot(&m_slotRenderer, sticker, center, color);
	sticker->setSlot(slot);
	return slot;
}
