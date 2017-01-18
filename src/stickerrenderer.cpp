#include "stickerrenderer.h"

#include "glgraphics.h"

StickerRenderer::StickerRenderer()
{
}

void StickerRenderer::render(const Sticker &sticker) const
{
	vec2f stickerCenter = sticker.getCenter();
	Color stickerColor = sticker.getColor();

	GLGraphics *glGraphics = GLGraphics::getInstance();

	glGraphics->setColor(stickerColor);
	glGraphics->drawCircle(stickerCenter, 0.04, true);
}
