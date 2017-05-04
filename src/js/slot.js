class Slot
{
	constructor(slotRenderer, sticker, center, color)
	{
		this.slotRenderer = slotRenderer;
		this.sticker = sticker;
		this.center = center;
		this.delta = new vec2f(0.0, 0.0);
		this.color = color;
		this.scale = 0.3;
	}

	render()
	{
		if (this.slotRenderer == null) return;

		this.slotRenderer.render(this);
	}
}
