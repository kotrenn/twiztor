#ifndef __STICKER_FACTORY_H_
#define __STICKER_FACTORY_H_

#include "sticker.h"

class Sticker;
class StickerRenderer;

class StickerFactory
{
public:
	StickerFactory();
	~StickerFactory();

	Sticker *makeSticker(const Color &color);
private:
	StickerRenderer *m_stickerRenderer;
};

#endif
