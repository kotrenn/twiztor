MOVE_DURATION = 1200; // 1.2 seconds

class Sticker
{
	constructor(color)
	{
		this.color = color;
		this.slot = null;
		this.prevArc = null;
		this.prevInverted = false;
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

	draw(context)
	{
		var center = this.getCenter();
		fillCircle(context, this.color, center.x, center.y, 4);
	}
}
