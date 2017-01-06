#include "stickerfactory.h"

StickerFactory::StickerFactory()
	:m_stickerRenderer()
{
}

StickerFactory::~StickerFactory()
{
}

Sticker *StickerFactory::makeSticker(const Color &color)
{
	Sticker *sticker = new Sticker(&m_stickerRenderer, color);
	return sticker;
}
