#ifndef __STICKER_RENDERER_H_
#define __STICKER_RENDERER_H_

#include "sticker.h"

class Sticker;

class StickerRenderer
{
public:
	StickerRenderer();

	void render(const Sticker &sticker) const;
private:
};

#endif
