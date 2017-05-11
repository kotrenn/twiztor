// Consider also the method of https://gist.github.com/winduptoy/a1aa09c3499e09edbd33

var EPSILON = 0.0001;

class vec2f
{
	zero()
	{
		return new vec2f(0, 0);
	}
	
	constructor(x, y)
	{
		this.x = x;
		this.y = y;
	}

	add(rhs)
	{
		return new vec2f(this.x + rhs.x, this.y + rhs.y);
	}

	sub(rhs)
	{
		return new vec2f(this.x - rhs.x, this.y - rhs.y);
	}

	dot(rhs)
	{
		return this.x * rhs.x + this.y * rhs.y;
	}

	scale(rhs)
	{
		return new vec2f(this.x * rhs, this.y * rhs);
	}

	norm()
	{
		return math.sqrt(this.x * this.x + this.y * this.y);
	}

	unit()
	{
		var mag = this.norm();
		if (mag < EPSILON) return vec2f.zero();
		return new vec2f(this.x / mag, this.y / mag);
	}

	normalize()
	{
		var mag = this.norm();
		if (mag < EPSILON)
			this.x = this.y = 0.0;
		this.x /= mag;
		this.y /= mag;
	}
}
