var SLOT_RADIUS = 8;

class Slot
{
	constructor(name, sticker, center, color)
	{
		this.name = name;
		this.sticker = sticker;
		this.center = center;
		this.delta = (0, 0);
		this.color = color;
		this.scale = 0.3;
	}

	draw(context)
	{
		fillCircle(context, this.color, this.center.x, this.center.y, SLOT_RADIUS)
	}

	setSticker(sticker)
	{
		this.sticker = sticker;
	}

	getColor()
	{
		return this.color;
	}

	getCenter()
	{
		return this.center;
	}

	setCenter(center)
	{
		this.center = center;
	}
}