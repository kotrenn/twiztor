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
		this.prevTime = 0;
		this.prevArc = arc;
		this.prevArc = null;
		this.prevInverted = inverted;
		this.slot = slot;
	}

	setColor(color)
	{
		this.color = color;
	}

	getTimeRatio()
	{
		/*
		currentTime = SDL_GetTicks();
		float ret = (currentTime - this.prevTime) / sc_MOVE_DURATION;
		if (ret > 1.0) ret = 1.0;
		return ret;
		*/
		return 0.0;
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
