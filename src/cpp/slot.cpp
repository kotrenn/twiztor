#include "slot.h"

#include "glgraphics.h"

Slot::Slot(SlotRenderer *slotRenderer, Sticker *sticker, const vec2f &center, const Color &color)
	:m_slotRenderer(slotRenderer),
	 m_sticker(sticker),
	 m_center(center),
	 m_delta(0.0, 0.0),
	 m_color(color),
	 m_scale(0.3)
{
}

void Slot::render() const
{
	if (m_slotRenderer == NULL) return;
	
	m_slotRenderer->render(*this);
}
