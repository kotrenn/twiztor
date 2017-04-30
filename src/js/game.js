var n = 5;
var mapping = [3, 2, 5, 1, 4];
var colors = ['#FF0000', '#0000FF', '#00FF00', '#FFFF00'];

function readPuzzleData(puzzlefile)
{
	var reader = new FileReader();
	reader.onload = function()
	{
		var text = reader.result;
		alert(text);

	};
	reader.readAsText(puzzlefile);
}

readPuzzleData('AAA.txt');

function Permutation(color, numSlots)
{
	this.color = color;
	this.numSlots = numSlots;
	this.getColor = function()
	{
		return this.color;
	}
}

class Sticker
{
	constructor(color)
	{
		this.color = color;
		this.slot = null;
		this.prevArc = null;
		this.prevInverted = false;
	}

	moveToSlot(slot, arc, inverted)
	{
		this.prevTime = SDL_GetTicks();
		this.prevArc = arc;
		this.prevInverted = inverted;
		this.slot = slot;
	}

	setColor(color)
	{
		this.color = color;
	}

	/*
	getTimeRatio()
	{
		currentTime = SDL_GetTicks();
		float ret = (currentTime - this.prevTime) / sc_MOVE_DURATION;
		if (ret > 1.0) ret = 1.0;
		return ret;
	}
	*/

	getCenter()
	{
		var slotCenter = this.slot.getCenter();
		var ret = slotCenter;
		if (this.prevArc != null)
		{
			var t = this.getTimeRatio();
			if (t < 1.0)
			{
				if (m_prevInverted) t = 1.0 - t;
				ret = m_prevArc.getPoint(t);
			}
		}
		return ret;
	}

	move(timeDelta)
	{
	}

	render()
	{
	}
}

class Slot
{
	constructor(sticker, center, color)
	{
		this.sticker = sticker;
		this.center = center;
		this.delta = (0, 0);
		this.color = color;
		this.scale = 0.3;
	}

	render()
	{
	}

	setSticker(sticker)
	{
		this.sticker = sticker;
	}

	getColor()
	{
		return this.color;
	}

	getCenter()
	{
		return this.center;
	}

	setCenter(center)
	{
		this.center = center;
	}
}

class Employee extends Slot
{
	constructor(name, wage)
	{
		super(name);
		this.wage = wage;
	}
	toString()
	{
		return '${ super.toString() } I earn $${ this.wage }.';
	}
}

var permutation = new Permutation(1, 5);

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
	
	context.beginPath();
	context.rect(50, 50, 50, 50);
	context.fillStyle = colors[permutation.getColor()];
	context.fill();
	context.closePath();
}

function loop()
{
	update();
	draw();
}

document.addEventListener("keydown", keyDown, false);
document.addEventListener("keyup", keyUp, false);

setInterval(loop, 10);
