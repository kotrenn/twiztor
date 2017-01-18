#include "slotrenderer.h"

#include "glgraphics.h"

SlotRenderer::SlotRenderer()
{
}

void SlotRenderer::render(const Slot &slot) const
{
	Color slotColor = slot.getColor();
	vec2f slotCenter = slot.getCenter();

	GLGraphics *glGraphics = GLGraphics::getInstance();

	glGraphics->setColor(slotColor);
	glGraphics->drawCircle(slotCenter, 0.05, true);
}
