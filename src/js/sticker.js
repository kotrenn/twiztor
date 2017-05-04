class Sticker
{
	var sc_MOVE_DURATION = 1200;
	
	constructor(stickerRenderer, color)
	{
		this.stickerRenderer = stickerRenderer;
		this.color = color;
		this.slot = null;
		this.prevTime = 0;
		this.prevArc = null;
		this.prevInverted = false;
	}

	moveToSlot(slot, arc=null, bool inverted=false)
	{
		this.prevTime = SDL_GetTIcks(); // Replace
		this.prevArc = arc;
		this.prevInverted = inverted;
		this.slot = slot;
	}

	move(timeDelta)
	{
	}

	render()
	{
	}

	getTimeRatio()
	{
		var currentTime = SDL_GetTicks(); // Replace
		var ret = float(currentTime - this.prevTime) / this.sc_MOVE_DURATION;
		if (ret > 1.0) ret = 1.0;
		return ret;
	}
	
	getCenter()
	{
		var slotCenter = this.slot.getCenter();
		var ret = slotCenter;
		if (this.arc != null)
		{
			var t = getTimeRatio();
			if (t < 1.0)
			{
				if (this.prevInverted) t = 1.0 - t;
				ret = this.prevArc.getPoint();
			}
		}
		return ret;
	}
}
