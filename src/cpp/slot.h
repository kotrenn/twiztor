#ifndef __SLOT_H_
#define __SLOT_H_

#include "color.h"
#include "gfx.h"
#include "slotrenderer.h"
#include "sticker.h"

class SlotRenderer;
class Sticker;

class Slot
{
public:
	Slot(SlotRenderer *slotRenderer, Sticker *sticker, const vec2f &center, const Color &color);

	void render() const;

	void setSticker(Sticker *sticker) { m_sticker = sticker; }
	Sticker *getSticker() const { return m_sticker; }

	Color getColor() const { return m_color; }
	vec2f getCenter() const { return m_center; }

	void setCenter(const vec2f &center) { m_center = center; }
private:
	SlotRenderer *m_slotRenderer;
	Sticker *m_sticker;
	vec2f m_center;
	vec2f m_delta;
	Color m_color;
	float m_scale;
};

#endif
