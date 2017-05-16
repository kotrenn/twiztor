var g_gameCanvas = document.getElementById("gameCanvas");
var windowWidth = window.innerWidth;
var windowHeight = window.innerHeight;
gameCanvas.width = 0.95 * Math.min(windowWidth, windowHeight);
gameCanvas.height = g_gameCanvas.width;

var g_gameContext = g_gameCanvas.getContext("2d");
g_gameContext.font="20px Georgia";

var GRAPHICS_SCALE = 0.45 * Math.min(g_gameCanvas.width, g_gameCanvas.height);
var X_OFFSET = 0.5 * g_gameCanvas.width;
var Y_OFFSET = 0.5 * g_gameCanvas.height;
var RADIUS_SCALE = 2.0;
var LINE_WIDTH = 4.0;

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

function drawString(context, color, msg, x, y)
{
	context.fillStyle = color;
	context.fillText(msg, x, y);
}
