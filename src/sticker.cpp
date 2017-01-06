#include "sticker.h"

#include <SDL2/SDL.h>
#include "glgraphics.h"

Sticker::Sticker(StickerRenderer *stickerRenderer, const Color &color)
	:m_stickerRenderer(stickerRenderer),
	 m_color(color),
	 m_slot(NULL),
	 m_previousSlot(NULL),
	 m_previousTime(0)
{
}

void Sticker::setSlot(Slot *slot)
{
	m_previousSlot = m_slot;
	m_previousTime = SDL_GetTicks();
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
	float ret = (float)(currentTime - m_previousTime) / sf_MOVE_DURATION;
	if (ret > 1.0) ret = 1.0;
	return ret;
}

vec2f Sticker::getCenter() const
{
	vec2f slotCenter = m_slot->getCenter();
	vec2f ret = slotCenter;
	if (m_previousSlot != NULL)
	{
		vec2f prevCenter = m_previousSlot->getCenter();
		float ratio = getTimeRatio();
		ret = ratio * slotCenter + (1.0 - ratio) * prevCenter;
	}
	return ret;
}
