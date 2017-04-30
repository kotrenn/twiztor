// Consider also the method of https://gist.github.com/winduptoy/a1aa09c3499e09edbd33

var EPSILON = 0.0001;

class vec2f
{
	function zero()
	{
		return new vec2f(0, 0);
	}
	
	constructor(x, y)
	{
		this.x = x;
		this.y = y;
	}

	function add(rhs)
	{
		return new vec2f(this.x + rhs.x, this.y + rhs.y);
	}

	function sub(rhs)
	{
		return new vec2f(this.x - rhs.x, this.y - rhs.y);
	}

	function dot(rhs)
	{
		return this.x * rhs.x + this.y * rhs.y;
	}

	function scale(rhs)
	{
		return new vec2f(this.x * rhs, this.y * rhs);
	}

	function norm()
	{
		return math.sqrt(this.x * this.x + this.y * this.y);
	}

	function unit()
	{
		var mag = this.norm();
		if (mag < EPSILON) return vec2f.zero();
		return new vec2f(this.x / mag, this.y / mag);
	}

	function normalize()
	{
		var mag = this.norm();
		if (mag < EPSILON)
			this.x = this.y = 0.0;
		this.x /= mag;
		this.y /= mag;
	}
}
