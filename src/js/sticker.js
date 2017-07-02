var MOVE_DURATION = 1200; // 1.2 seconds
var STICKER_RADIUS = 4.20;

class Sticker
{
	constructor(color, shape)
	{
		this.color = color;
		this.slot = null;
		this.prevArc = null;
		this.prevInverted = false;
		this.shape = shape;
	}

	getShape()
	{
		return this.shape;
	}

	getSlot()
	{
		return this.slot;
	}

	moveToSlot(slot, arc, inverted)
	{
		this.prevTime = (new Date()).getTime();
		this.prevArc = arc;
		this.prevInverted = inverted;
		this.slot = slot;
	}

	setColor(color)
	{
		this.color = color;
	}

	getTimeRatio()
	{
		var currentTime = (new Date()).getTime();
		var ret = (currentTime - this.prevTime) / MOVE_DURATION;
		if (ret > 1.0) ret = 1.0;
		return ret;
	}

	getCenter()
	{
		var slotCenter = this.slot.getCenter();
		var ret = slotCenter;
		if (this.prevArc != null)
		{
			var t = this.getTimeRatio();
			if (t < 1.0)
			{
				if (this.prevInverted) t = 1.0 - t;
				ret = this.prevArc.getPoint(t);
			}
		}
		return ret;
	}

	move(timeDelta)
	{
	}

	cloneSlot()
	{
		this.color = this.slot.getColor();
		this.shape = this.slot.getShape();
	}
	
	draw(context)
	{
		var center = this.getCenter();
		//fillCircle(context, this.color, center.x, center.y, STICKER_RADIUS);
		if (g_displayMode == 0)
		{
			fillCircle(context, this.color, center.x, center.y, STICKER_RADIUS);
		}
		else if (g_displayMode == 1)
		{
			fillCircle(context, this.color, center.x, center.y, STICKER_RADIUS);
		}
		else if (g_displayMode == 2)
		{
			var r = STICKER_RADIUS / GRAPHICS_SCALE * RADIUS_SCALE * 1.1;
			var x0 = center.x - r;
			var y0 = center.y - r;
			var x1 = center.x + r;
			var y1 = center.y + r;
			drawLine(context, this.color, x0, center.y, center.x, y0);
			drawLine(context, this.color, x0, center.y, center.x, y1);
			drawLine(context, this.color, x1, center.y, center.x, y0);
			drawLine(context, this.color, x1, center.y, center.x, y1);
		}
		else if (g_displayMode == 3)
		{
			fillShape(context, this.shape, this.color, center.x, center.y, STICKER_RADIUS * 1.1);
		}
	}
}
