var g_gameCanvas = document.getElementById("gameCanvas");
var windowWidth = window.innerWidth;
var windowHeight = window.innerHeight;
gameCanvas.width = 0.95 * Math.min(windowWidth, windowHeight);
gameCanvas.height = g_gameCanvas.width;

var g_gameContext = g_gameCanvas.getContext("2d");
var FONT_SIZE = 20;
g_gameContext.font = FONT_SIZE.toString() + 'px Courier';

var GRAPHICS_SCALE = 0.45 * Math.min(g_gameCanvas.width, g_gameCanvas.height);
var X_OFFSET = 0.5 * g_gameCanvas.width;
var Y_OFFSET = 0.5 * g_gameCanvas.height;
var RADIUS_SCALE = 2.0;
var LINE_WIDTH = 4.0;

function drawString(context, color, msg, x, y)
{
	context.fillStyle = color;
	context.fillText(msg, x, y);
}

function adjustPosX(t)
{
	return GRAPHICS_SCALE * t + X_OFFSET;
}

function adjustPosY(t)
{
	return GRAPHICS_SCALE * t + Y_OFFSET;
}

function adjustLen(t)
{
	return GRAPHICS_SCALE * t;
}

function fillRect(context, color, x, y, w, h)
{
	fillRectUI(context,
			   color,
			   adjustPosX(x),
			   adjustPosY(y),
			   adjustLen(w),
			   adjustLenY(h));
}

function fillRectUI(context, color, x, y, w, h)
{
	context.beginPath();
	context.rect(x, y, w, h);
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
	context.lineWidth = LINE_WIDTH;
	context.stroke();
	context.moveTo(0, 0);
}

function fillCircle(context, color, x, y, r)
{
	var radius = RADIUS_SCALE * r;
	context.beginPath();
	context.arc(adjustPosX(x), adjustPosY(y), radius, 0, 2.0 * Math.PI);
	context.fillStyle = color;
	context.fill();
	context.closePath();
}

function drawCircle(context, color, x, y, r)
{
	var radius = RADIUS_SCALE * r;
	context.beginPath();
	context.arc(adjustPosX(x), adjustPosY(y), radius, 0, 2.0 * Math.PI);
	context.strokeStyle = color;
	context.lineWidth = LINE_WIDTH
	context.stroke();
	context.closePath();
}

function drawPolygon(context, color, n, x, y, r)
{
	var radius = (RADIUS_SCALE / GRAPHICS_SCALE) * r;
	context.beginPath();
	context.strokeStyle = color;
	context.moveTo(adjustPosX(x + radius), adjustPosY(y));
	for (var i = 1; i <= n; i++)
	{
		var t0 = (2.0 * Math.PI / n) * (i   );
		var t1 = (2.0 * Math.PI / n) * (i + 1)
		var x0 = radius * Math.cos(t0) + x;
		var y0 = radius * Math.sin(t0) + y;
		var x1 = radius * Math.cos(t1) + x;
		var y1 = radius * Math.sin(t1) + y;
		context.lineTo(adjustPosX(x0), adjustPosY(y0));
	}
	context.stroke();
	context.closePath();
}

function fillPolygon(context, color, n, x, y, r)
{
	var radius = (RADIUS_SCALE / GRAPHICS_SCALE) * r;
	context.beginPath();
	context.fillStyle = color;
	context.moveTo(adjustPosX(x + radius), adjustPosY(y));
	for (var i = 1; i <= n; i++)
	{
		var t0 = (2.0 * Math.PI / n) * (i   );
		var t1 = (2.0 * Math.PI / n) * (i + 1)
		var x0 = radius * Math.cos(t0) + x;
		var y0 = radius * Math.sin(t0) + y;
		var x1 = radius * Math.cos(t1) + x;
		var y1 = radius * Math.sin(t1) + y;
		context.lineTo(adjustPosX(x0), adjustPosY(y0));
	}
	context.fill();
	context.closePath();
}

var NUM_SHAPES = 0;
var SHAPE_CIRCLE = NUM_SHAPES++;
var SHAPE_TRIANGLE = NUM_SHAPES++;
var SHAPE_SQUARE = NUM_SHAPES++;
var SHAPE_PENTAGON = NUM_SHAPES++;
var SHAPE_HEXAGON = NUM_SHAPES++;

function drawShape(context, shape, color, x, y, r)
{
	switch (shape)
	{
		case SHAPE_CIRCLE: drawCircle(context, color, x, y, r); break;
		case SHAPE_TRIANGLE: drawPolygon(context, color, 3, x, y, r); break;
		case SHAPE_SQUARE: drawPolygon(context, color, 4, x, y, r); break;
		case SHAPE_PENTAGON: drawPolygon(context, color, 5, x, y, r); break;
		case SHAPE_HEXAGON: drawPolygon(context, color, 6, x, y, r); break;
	}
}

function fillShape(context, shape, color, x, y, r)
{
	switch (shape)
	{
		case SHAPE_CIRCLE: fillCircle(context, color, x, y, r); break;
		case SHAPE_TRIANGLE: fillPolygon(context, color, 3, x, y, r); break;
		case SHAPE_SQUARE: fillPolygon(context, color, 4, x, y, r); break;
		case SHAPE_PENTAGON: fillPolygon(context, color, 5, x, y, r); break;
		case SHAPE_HEXAGON: fillPolygon(context, color, 6, x, y, r); break;
	}
}
