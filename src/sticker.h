#ifndef __STICKER_H_
#define __STICKER_H_

#include "color.h"
#include "gfx.h"
#include "slot.h"
#include "stickerrenderer.h"

class Slot;
class StickerRenderer;

class Sticker
{
public:
	Sticker(StickerRenderer *stickerRenderer, const Color &color);

	void setSlot(Slot *slot);
	void setColor(const Color &color) { m_color = color; }

	vec2f getCenter() const;
	Color getColor() const { return m_color; }
	Slot *getSlot() const { return m_slot; }
	
	void move(Uint32 timeDelta);
	void render() const;
private:
	float getTimeRatio() const;

	StickerRenderer *m_stickerRenderer;
	Color m_color;
	Slot *m_slot;
	Slot *m_previousSlot;
	Uint32 m_previousTime;
	static const Uint32 sf_MOVE_DURATION = 1200; // 1.2 seconds
};

#endif
