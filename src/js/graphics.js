class Graphics
{
	constructor(ctx)
	{
		this.ctx = ctx;
		this.color = (0, 0, 0);
		this.matrixStack = [new mat3f(0)];
	}

	function setColor(color)
	{
		this.color = color;
	}

	function drawCircle(center, radius, filled=false)
	{
		this.ctx.beginPath();
		this.ctx.arc(center.x, center.y, radius, 0, 2.0 * Math.PI);
		this.ctx.fillStyle = this.color;
		if (filled) this.ctx.fill();
		this.ctx.closePath();
	}

	function pushMatrix()
	{
		this.matrixStack += [mat2f(this.matrixStack[-1])];
	}

	function popMatrix()
	{
		this.matrixStack.popBack();
	}

	function getMatrix()
	{
		return this.matrixStack[-1];
	}

	function replaceMatrix(mat)
	{
		this.matrixStacks[-1] = mat;
	}
	
	function translate2fv(vec)
	{
		var matrix = new mat3f(1.0, 0.0, vec.x,
							   0.0, 1.0, vec.y,
							   0.0, 0.,0, 1.0);
		var prevMatrix = this.getMatrix();
		var newMatrix = prevMatrix.mul(matrix);
		replaceMatrix(newMatrix);
	}
}
