var ARC_LINE = 0;
var ARC_CIRCLE = 1;

function NewLineArc(permutation, slotU, slotV)
{
	return new Arc(permutation, slotU, slotV, ARC_LINE);
}

function NewCircleArc(permutation, slotU, slotV, circleRadius, circlePlus, circleInverted)
{
	var ret = new Arc(permutation, slotU, slotV, ARC_CIRCLE);
	
	ret.circleRadius = circleRadius;
	ret.circlePlus = circlePlus;
	ret.circleInverted = circleInverted;

	ret.computeParameters();

	ret.debugEnabled = true;

	return ret;
}

class Arc
{
	constructor(permutation, slotU, slotV, shape)
	{
		this.permutation = permutation;
		this.slotU = slotU;
		this.slotV = slotV;
		this.shape = shape;
		this.startTime = 0;
		this.debugEnabled = false;

		// CircleArc vars
		this.circleRadius = 0.0;
		this.circlePlus = false;
		this.circleInverted = false;
		this.circleCenter = new vec2f(0.0, 0.0);
		this.thetaU = 0.0;
		this.thetaV = 0.0;
		this.dTheta = 0.0;
	}

	draw(context)
	{
		var color = this.permutation.getColor();
		
		if (this.shape == ARC_LINE)
		{
			var v0 = this.slotU.getCenter();
			var v1 = this.slotV.getCenter();

			var color = this.permutation.getColor();

			drawLine(context, color, v0.x, v0.y, v1.x, v1.y);
		}
		else if (this.shape == ARC_CIRCLE)
		{
			var numIntervals = 20;
			if (this.debugEnabled) numIntervals = 5;
			var dt = 1.0 / numIntervals;
			
			for (var i = 0; i < numIntervals; i++)
			{
				var t0 = i * dt;
				var t1 = (i + 1) * dt;

				var p0 = this.getPoint(t0);
				var p1 = this.getPoint(t1);

				drawLine(context, color, p0.x, p0.y, p1.x, p1.y);

				if (this.debugEnabled)
				{
					var r = Math.floor(255 * t0).toString(16);
					while (r.length < 2)
						r = '0' + r;
					var g = '00';
					var b = Math.floor(255 * (1.0 - t0)).toString(16);
					while (b.length < 2)
						b = '0' + b;
					var purple = '#' + r + g + b;
					fillCircle(context, purple, p0.x, p0.y, 3);
				}
			}

			if (this.debugEnabled)
			{
				var green = '#00FF00';
				var x = this.circleCenter.x;
				var y = this.circleCenter.y;
				fillCircle(context, green, x, y, 3);
			}
		}
	}

	getPoint(t)
	{
		var ret = new vec2f(0.0, 0.0);
		
		if (this.shape == ARC_LINE)
		{
			var lhs = this.slotU.getCenter().scale(1.0 - t);
			var rhs = this.slotV.getCenter().scale(t);
			ret = lhs.add(rhs);
		}
		else if (this.shape == ARC_CIRCLE)
		{
			var theta = this.thetaU + t * this.dTheta;

			var p = new vec2f(Math.cos(theta), Math.sin(theta));
			p = p.scale(this.circleRadius).add(this.circleCenter);

			return p;
		}

		return ret;
	}

	computeParameters()
	{
		if (this.shape == ARC_CIRCLE)
		{
			var v0 = this.slotU.getCenter();
			var v1 = this.slotV.getCenter();

			// Calculate the center of the circle;
			var d = v0.sub(v1).norm();
			var r2 = this.circleRadius * this.circleRadius;
			var disc = r2 - d * d / 4.0;
			var minDisc = EPSILON;
			if (disc < minDisc) disc = minDisc;
			var h = Math.sqrt(disc);
			var midpoint = v0.add(v1).scale(0.5);
			var disp = v1.sub(v0).unit();
			var rot = new vec2f(disp.y, -disp.x);
			if (this.circlePlus) rot = rot.scale(-1.0);
			this.circleCenter = midpoint.add(rot.scale(h));

			// Set up interval of angles to iterate along
			var deltaU = v0.sub(this.circleCenter);
			var deltaV = v1.sub(this.circleCenter);

			this.thetaU = Math.atan2(deltaU.y, deltaU.x);
			this.thetaV = Math.atan2(deltaV.y, deltaV.x);

			this.dTheta = this.thetaV - this.thetaU;

			// Put dTheta into the interval [0, 2pi]
			while (this.dTheta < 0)             this.dTheta += 2.0 * Math.PI;
			while (this.dTheta > 2.0 * Math.PI) this.dTheta -= 2.0 * Math.PI;

			// Invert it?
			if (this.circleInverted)
			{
				var tmp = this.thetaU;
				this.thetaU = this.thetaV;
				this.thetaV = tmp;
				this.dTheta = 2.0 * Math.PI - this.dTheta;
			}
		}
	}

	adjustCenter(vec)
	{
	}

	normalize(radius)
	{
		if (this.shape == ARC_CIRCLE)
		{
			this.circleRadius /= radius;
		}
	}
}
