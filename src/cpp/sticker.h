#ifndef __STICKER_H_
#define __STICKER_H_

#include "arc.h"
#include "color.h"
#include "gfx.h"
#include "slot.h"
#include "stickerrenderer.h"

class Arc;
class Slot;
class StickerRenderer;

class Sticker
{
public:
	Sticker(StickerRenderer *stickerRenderer, const Color &color);

	void moveToSlot(Slot *slot, Arc *arc=NULL, bool inverted=false);
	void setColor(const Color &color) { m_color = color; }

	vec2f getCenter() const;
	Color getColor() const { return m_color; }
	Slot *getSlot() const { return m_slot; }
	
	void move(Uint32 timeDelta);
	void render() const;
private:
	float getTimeRatio() const;

	static const Uint32 sc_MOVE_DURATION = 1200; // 1.2 seconds
	
	StickerRenderer *m_stickerRenderer;
	Color m_color;
	Slot *m_slot;
	Uint32 m_prevTime;
	Arc *m_prevArc;
	bool m_prevInverted;
};

#endif
