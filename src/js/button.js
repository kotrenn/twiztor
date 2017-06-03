class Button
{
	constructor(permutation)
	{
		this.permutation = permutation;
		this.buttonPos   = this.permutation.getReverseIndex() + 1;
		this.buttonSkip  = 10;
		this.buttonW     = 25;
		this.buttonH     = this.buttonW;
		this.buttonX     = g_gameCanvas.width;
		this.buttonX    -= this.buttonPos * (this.buttonW + this.buttonSkip);
		this.buttonY     = this.buttonSkip;
		
		var visibleIndex = (this.permutation.getIndex() + 1) % 10;
		this.numStr      = visibleIndex.toString();
		this.numX        = this.buttonX + 0.5 * this.buttonW - 0.25 * FONT_SIZE;
		this.numY        = this.buttonY +       this.buttonH + 1.15 * FONT_SIZE;
	}

	drawUI(context)
	{
		// Draw button
		fillRectUI(context,
				   this.permutation.getColor(),
				   this.buttonX,
				   this.buttonY,
				   this.buttonW,
				   this.buttonH);

		// Draw number
		drawString(context,
				   '#000000',
				   this.numStr,
				   this.numX,
				   this.numY);
	}
}
