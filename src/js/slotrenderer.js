class SlotRenderer
{
	constructor(ctx)
	{
		this.graphics = graphics
	}

	function render(slot)
	{
		var slotColor = slot.getColor();
		var slotCenter = slot.getCenter();
		var radius = 20;

		this.graphics.setColor(slotColor);
		this.graphics.drawCircle(slotCenter, radius, true);
	}
}
