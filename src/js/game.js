var n = 5
var mapping = [3, 2, 5, 1, 4];
var colors = ['#FF0000', '#0000FF', '#00FF00', '#FFFF00']

var canvas = document.getElementById("gameCanvas");
var context = canvas.getContext("2d");

var leftPressed = false;
var rightPressed = false;

function keyDown(e)
{
	if (e.keyCode == 39)
	{
		rightPressed = true;
	}
	else if (e.keyCode == 37)
	{
		leftPressed = true;
	}
}

function keyUp(e)
{
	if (e.keyCode == 39)
	{
		rightPressed = false;
	}
	else if (e.keyCode == 37)
	{
		leftPressed = false;
	}
}

function update()
{
}

function draw()
{
	context.clearRect(0, 0, canvas.width, canvas.height);
}

function loop()
{
	update();
	draw();
}

document.addEventListener("keydown", keyDown, false);
document.addEventListener("keyup", keyUp, false);

setInterval(loop, 10);
