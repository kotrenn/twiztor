class Button
{
	constructor(permutation, depth, pos)
	{
		this.permutation = permutation;
		this.depth       = depth;
		this.pos         = pos;
		this.buttonSkip  = 10;
		this.buttonW     = 25;
		this.buttonH     = this.buttonW;
		this.buttonX     = g_gameCanvas.width;
		this.buttonX    -= this.pos * (this.buttonW + this.buttonSkip);
		this.buttonY     = this.buttonSkip;
		this.buttonY    += this.depth * (this.buttonH + this.buttonSkip);
		
		var visibleIndex = (this.permutation.getIndex() + 1) % 10;
		this.numStr      = visibleIndex.toString();
		this.numX        = this.buttonX + 0.5 * this.buttonW - 0.25 * FONT_SIZE;
		this.numY        = this.buttonY +       this.buttonH + 1.15 * FONT_SIZE;
	}

	getPermutation()
	{
		return this.permutation;
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
	}

	getMinX()
	{
		return this.buttonX;
	}

	getMinY()
	{
		return this.buttonY;
	}

	getMaxX()
	{
		return this.buttonX + this.buttonW;
	}

	getMaxY()
	{
		return this.buttonY + this.buttonH;
	}
}
