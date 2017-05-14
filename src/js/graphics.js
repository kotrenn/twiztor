var scaleConst = 100;
var yConst = scaleConst;
var xConst = 2 * yConst;

function adjustPosX(t)
{
	return scaleConst * t + xConst;
}

function adjustPosY(t)
{
	return scaleConst * t + yConst;
}

function adjustLen(t)
{
	return scaleConst * t;
}

function fillRect(context, color, x, y, w, h)
{
	context.beginPath();
	context.rect(adjustPosX(x), adjustPosY(y), adjustLen(w), adjustLenY(h));
	context.fillStyle = color;
	context.fill();
	context.closePath();
}

function drawLine(context, color, x1, y1, x2, y2)
{
	context.beginPath();
	context.moveTo(adjustPosX(x1), adjustPosY(y1));
	context.lineTo(adjustPosX(x2), adjustPosY(y2));
	context.strokeStyle = color;
	context.stroke();
	context.moveTo(0, 0);
}

function fillCircle(context, color, x, y, r)
{
	context.beginPath();
	context.arc(adjustPosX(x), adjustPosY(y), r, 0, 2.0 * Math.PI);
	context.fillStyle = color;
	context.fill();
	context.closePath();
}
