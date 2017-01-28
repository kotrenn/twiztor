#include "slotfactory.h"

SlotFactory::SlotFactory()
	:m_slotRenderer(new SlotRenderer()),
	 m_stickerFactory(new StickerFactory())
{
}

SlotFactory::~SlotFactory()
{
	delete m_slotRenderer;
	delete m_stickerFactory;
}

Slot *SlotFactory::makeSlot(const Color &color, const vec2f &center)
{
	Sticker *sticker = m_stickerFactory->makeSticker(color);
	Slot *slot = new Slot(m_slotRenderer, sticker, center, color);
	sticker->moveToSlot(slot);
	return slot;
}
