class Arc
{
	constructor(permutation, slotU, slotV)
	{
		this.permutation = permutation;
		this.slotU = slotU;
		this.slotV = slotV;
		this.startTime = 0;
	}

	getPoint(t)
	{
		var lhs = this.slotU.getCenter().scale(1.0 - t);
		var rhs = this.slotV.getCenter().scale(t);
		return lhs.add(rhs);
	}

	draw(context)
	{
		var v0 = this.slotU.getCenter();
		var v1 = this.slotV.getCenter();

		var color = this.permutation.getColor();

		drawLine(context, color, v0.x, v0.y, v1.x, v1.y);
	}

	// CircleArc
	computeParameters()
	{
	}

	adjustCenter(vec)
	{
	}

	normalize(flt)
	{
	}
}
