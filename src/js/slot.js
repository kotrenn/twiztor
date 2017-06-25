var SLOT_RADIUS = 7.40;

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
		this.shape = sticker.getShape();
	}

	draw(context)
	{
		if (g_displayMode == 0)
		{
			fillCircle(context, this.color, this.center.x, this.center.y, SLOT_RADIUS);
		}
		else if (g_displayMode == 1)
		{
			drawCircle(context, this.color, this.center.x, this.center.y, SLOT_RADIUS);
		}
		else if (g_displayMode == 2)
		{
			var r = SLOT_RADIUS / GRAPHICS_SCALE * RADIUS_SCALE * 1.1;
			var x0 = this.center.x - r;
			var y0 = this.center.y - r;
			var x1 = this.center.x + r;
			var y1 = this.center.y + r;
			drawLine(context, this.color, x0, this.center.y, this.center.x, y0);
			drawLine(context, this.color, x0, this.center.y, this.center.x, y1);
			drawLine(context, this.color, x1, this.center.y, this.center.x, y0);
			drawLine(context, this.color, x1, this.center.y, this.center.x, y1);
		}
		else if (g_displayMode == 3)
		{
			drawShape(context, this.shape, this.color, this.center.x, this.center.y, SLOT_RADIUS * 1.1);
		}
	}

	setSticker(sticker)
	{
		this.sticker = sticker;
	}

	getColor()
	{
		return this.color;
	}

	getShape()
	{
		return this.shape;
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
