class StickerRenderer
{
	constructor(graphics)
	{
		this.graphics = graphics
	}

	function render(sticker)
	{
		var stickerColor = sticker.getColor();
		var stickerCenter = sticker.getCenter();
		var radius = 16;

		this.graphics.setColor(stickerColor);
		this.graphics.drawCircle(stickerCenter, radius, true);
	}
}
