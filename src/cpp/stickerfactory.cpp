#include "stickerfactory.h"

StickerFactory::StickerFactory()
	:m_stickerRenderer(new StickerRenderer())
{
}

StickerFactory::~StickerFactory()
{
	delete m_stickerRenderer;
}

Sticker *StickerFactory::makeSticker(const Color &color)
{
	Sticker *sticker = new Sticker(m_stickerRenderer, color);
	return sticker;
}
