function zeroArray(n)
{
	var ret = [];
	for (var i = 0; i < n; i++)
		ret.push(0);
	return ret;
}

function linearArray(n)
{
	var ret = [];
	for (var i = 0; i < n; i++)
		ret.push(i);
	return ret;
}

function linearStrArray(n)
{
	var ret = [];
	for (var i = 0; i < n; i++)
		ret.push(i.toString());
	return ret;
}


var scale = 200.0;
function fillRect(context, color, x, y, w, h)
{
	context.beginPath();
	context.rect(x * scale, y * scale, w * scale, h * scale);
	context.fillStyle = color;
	context.fill();
	context.closePath();
}

function drawLine(context, color, x1, y1, x2, y2)
{
	context.beginPath();
	context.moveTo(x1 * scale, y1 * scale);
	context.lineTo(x2 * scale, y2 * scale);
	context.strokeStyle = color;
	context.stroke();
	context.moveTo(0, 0);
}

function fillCircle(context, color, x, y, r)
{
	context.beginPath();
	context.arc(x * scale, y * scale, r * scale, 0, 2.0 * Math.PI);
	context.fillStyle = color;
	context.fill();
	context.closePath();
}



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
		this.prevTime = 0;
		this.prevArc = arc;
		this.prevInverted = inverted;
		this.slot = slot;
	}

	setColor(color)
	{
		this.color = color;
	}

	getTimeRatio()
	{
		/*
		currentTime = SDL_GetTicks();
		float ret = (currentTime - this.prevTime) / sc_MOVE_DURATION;
		if (ret > 1.0) ret = 1.0;
		return ret;
		*/
		return 0.0;
	}

	getCenter()
	{
		var slotCenter = this.slot.getCenter();
		var ret = slotCenter;
		if (this.prevArc != null)
		{
			var t = this.getTimeRatio();
			if (t < 1.0)
			{
				if (this.prevInverted) t = 1.0 - t;
				ret = this.prevArc.getPoint(t);
			}
		}
		return ret;
	}

	move(timeDelta)
	{
	}

	draw()
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

	draw(context)
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
}



class Permutation
{
	constructor(n, color, index)
	{
		this.mapping = linearArray(n);
		this.labels = linearStrArray(n);
		this.color = color;
		this.index = index;
	}

	draw(context, arcList)
	{
		for (var i in arcList)
		{
			var arc = arcList[i];
			if (arc == null) continue;
			arc.draw(context);
		}
	}

	getColor()
	{
		return this.color;
	}

	getMapping()
	{
		return this.mapping;
	}

	getIndex()
	{
		return this.index;
	}

	setCycles(cycles)
	{
		for (var k in cycles)
		{
			var cycle = cycles[k];
			for (var i in cycle)
			{
				var j = (i + 1) % cycle.length;
				this.mapping[cycle[i]] = cycle[j];
			}
		}
	}

	multiply(rhs)
	{
		var ret = new Permutation(this.mapping.length, this.color, this.index);
		for (var i in this.mapping)
			ret.mapping[i] = this.mapping[rhs.mapping[i]];
		
		return ret;
	}

	apply(puzzleData, inverted)
	{
		var arcList = puzzleData.getArcList(this);
		var stickerList = puzzleData.getStickerList();
		var slotList = puzzleData.getSlotList();

		var newStickerList = [];
		for (var i in stickerList)
			newStickerList.push(stickerList[i]);

		for (var i in this.mapping)
		{
			var j = this.mapping[i];

			var a = i;
			var b = j;
			if (inverted) { a = j; b = i; }
			var start = a;
			if (inverted) start = b;

			var sticker = stickerList[a];
			newStickerList[b] = sticker;
			sticker.moveToSlot(slotList[b], arcList[start], inverted);
		}

		puzzleData.setStickerList(newStickerList);
	}

	next(index, inverted=false)
	{
		var ret = this.mapping[index];

		if (inverted)
			for (var i in this.mapping)
				if (this.mappign[i] == index)
					ret = i;
		
		return ret;
	}

	clone()
	{
		var ret = new Permutation(this.mapping.length, this.color, this.index);

		for (var i in this.mapping)
		{
			ret.mapping[i] = this.mapping[i];
			ret.labels[i] = this.labels[i];
		}
		
		return ret;
	}
}



class PuzzleData
{
	constructor(name)
	{
		this.name = name;
		this.permutationList = [];
		this.slotList = [];
		this.stickerList = [];
		this.arcMap = {};
		this.center = new vec2f(0.0, 0.0);
	}

	draw(context)
	{
		for (var i in this.permutationList)
		{
			var permutation = this.permutationList[i];
			permutation.draw(context, this.getArcList(permutation));
		}

		for (var i in this.slotList)
			this.slotList[i].draw(context);

		for (var i in this.stickerList)
			this.stickerList[i].draw(context);
	}

	addPermutation(permutation)
	{
		this.permutationList.push(permutation)
		this.arcMap[permutation] = [];

		for (var i in this.slotList)
		{
			var slotU = this.slotList[i];
			var slotV = this.slotList[permutation.next(i)];
			var lineArc = new Arc(permutation, slotU, slotV);
			this.setArc(permutation, i, lineArc);
		}
	}

	addSlot(slot)
	{
		this.slotList.push(slot);
	}

	addSticker(sticker)
	{
		this.stickerList.push(sticker);
	}

	clearSlotList()
	{
		this.slotList = [];
	}

	clearStickerList()
	{
		this.stickerList = [];
	}

	getPermutationList()
	{
		return this.permutationList;
	}

	getSlotList()
	{
		return this.slotList;
	}

	getStickerList()
	{
		return this.stickerList;
	}

	setPermutationList(permutationList)
	{
		this.permutationList = permutationList;
	}

	setSlotList(slotList)
	{
		this.slotList = slotList;
	}

	setStickerList(stickerList)
	{
		this.stickerList = stickerList;
	}

	getPermutation(index)
	{
		return this.permutationList[index];
	}

	getSlot(index)
	{
		return this.slotList[index];
	}

	getSticker(index)
	{
		return this.stickerList[index];
	}

	getArc(permutation, nodeIndex, inverted)
	{
		//if (!this.arcMap.contains(permutation))
		if (!(permutation in this.arcMap))
			return null;
		
		var arcList = this.arcMap[permutation];
		var mapping = permutation.getMapping();
		var nextIndex = mapping[nodeIndex];
		if (inverted)
		{
			for (var i in mapping)
				if (mapping[i] == nodeIndex)
					nextIndex = i;
		}

		return arcList[nextIndex];
	}

	setArc(permutation, nodeIndex, arc)
	{
		//if (!this.arcMap.contains(permutation))
		if (!(permutation in this.arcMap))
			this.arcMap[permutation] = [this.getSlotListSize()];

		this.arcMap[permutation][nodeIndex] = arc;
	}

	getArcList(permutation)
	{
		return this.arcMap[permutation];
	}

	getCenter()
	{
		return this.center;
	}

	setCenter(center)
	{
		this.center = center;p
	}
}




class PuzzleBuilder
{
	constructor(name)
	{
		this.name = name;
		this.puzzleData = new PuzzleData();
		this.nodeList = [];
		this.permutationMap = {};
	}

	addNode(nodeName, nodeColor, nodeX, nodeY)
	{
		var newSticker = new Sticker(nodeColor);
		var newSlot = new Slot(nodeColor, new vec2f(nodeX, nodeY));
		newSticker.moveToSlot(newSlot);
		this.puzzleData.addSlot(newSlot);
		this.puzzleData.addSticker(newSticker);
		this.nodeList.push(nodeName);
	}

	addPermutation(color, cycleList)
	{
		var n = this.puzzleData.slotList.length;
		var index = this.puzzleData.length;
		var newPermutation = new Permutation(n, color, index);
		newPermutation.setCycles(cycleList);
		this.puzzleData.addPermutation(newPermutation);
		this.permutationMap[color] = newPermutation;
	}

	getPuzzleData()
	{
		return this.puzzleData;
	}
}



function AAA()
{
	var builder = new PuzzleBuilder('AAA');
	
	builder.addNode('v0', '#FF0000', 0.25, 0.25);
	builder.addNode('v1', '#0000FF', 1.0, 1.0);

	builder.addPermutation('#FF0000', [[0, 1]]);

	return builder.getPuzzleData();
}



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

var puzzleData = AAA();

function update()
{
}

function draw()
{
	context.clearRect(0, 0, canvas.width, canvas.height);

	puzzleData.draw(context);
}

function loop()
{
	update();
	draw();
}

var canvas = document.getElementById("gameCanvas");
var context = canvas.getContext("2d");

document.addEventListener("keydown", keyDown, false);
document.addEventListener("keyup", keyUp, false);

setInterval(loop, 10);
