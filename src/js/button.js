class Button
{
	constructor(permutation)
	{
		this.permutation = permutation;
	}

	drawUI(context)
	{
		var buttonPos = this.permutation.getReverseIndex() + 1;
		var buttonSkip = 10;
		var buttonW = 25;
		var buttonH = buttonW;
		var buttonX = g_gameCanvas.width;
		buttonX -= buttonPos * (buttonW + buttonSkip);
		var buttonY = buttonSkip;
		
		var visibleIndex = (this.permutation.getIndex() + 1) % 10;
		var numStr = visibleIndex.toString();
		var numX = buttonX + 0.5 * buttonW - 0.25 * FONT_SIZE;
		var numY = buttonY +       buttonH + 1.15 * FONT_SIZE;
		
		// Draw button
		fillRectUI(context,
				   this.permutation.getColor(),
				   buttonX,
				   buttonY,
				   buttonW,
				   buttonH);

		// Draw number
		drawString(context,
				   '#000000',
				   numStr,
				   numX,
				   numY);
	}
}
