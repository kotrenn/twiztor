#include "sticker.h"

#include <SDL2/SDL.h>
#include "glgraphics.h"

Sticker::Sticker(StickerRenderer *stickerRenderer, const Color &color)
	:m_stickerRenderer(stickerRenderer),
	 m_color(color),
	 m_slot(NULL),
	 m_prevTime(0),
	 m_prevArc(NULL),
	 m_prevInverted(false)
{
}

void Sticker::moveToSlot(Slot *slot, Arc *arc, bool inverted)
{
	m_prevTime = SDL_GetTicks();
	m_prevArc = arc;
	m_prevInverted = inverted;
	m_slot = slot;
}

void Sticker::move(Uint32)
{
}

void Sticker::render() const
{
	if (m_stickerRenderer == NULL) return;
	
	m_stickerRenderer->render(*this);
}

float Sticker::getTimeRatio() const
{
	Uint32 currentTime = SDL_GetTicks();
	float ret = (float)(currentTime - m_prevTime) / sc_MOVE_DURATION;
	if (ret > 1.0) ret = 1.0;
	return ret;
}

vec2f Sticker::getCenter() const
{
	vec2f slotCenter = m_slot->getCenter();
	vec2f ret = slotCenter;
	if (m_prevArc != NULL)
	{
		float t = getTimeRatio();
		if (t < 1.0)
		{
			if (m_prevInverted) t = 1.0 - t;
			ret = m_prevArc->getPoint(t);
		}
		
	}
	return ret;
}
