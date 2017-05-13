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
		return Math.sqrt(this.x * this.x + this.y * this.y);
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
		this.prevArc = null;
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

	draw(context)
	{
		var center = this.getCenter();
		fillCircle(context, this.color, center.x, center.y, 4);
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
		fillCircle(context, this.color, this.center.x, this.center.y, 5)
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

	// CircleArc
	computeParameters()
	{
	}

	adjustCenter(vec)
	{
	}

	normalize(flt)
	{
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
		for (var i = 0; i < arcList.length; i++)
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
		for (var k = 0; k < cycles.length; k++)
		{
			var cycle = cycles[k];
			for (var i = 0; i < cycle.length; i++)
			{
				var j = (i + 1) % cycle.length;
				this.mapping[cycle[i]] = cycle[j];
			}
		}
	}

	multiply(rhs)
	{
		var ret = new Permutation(this.mapping.length, this.color, this.index);
		for (var i = 0; i < this.mapping.length; i++)
			ret.mapping[i] = this.mapping[rhs.mapping[i]];
		
		return ret;
	}

	apply(puzzleData, inverted)
	{
		// Arcs for this permutation
		var arcList = puzzleData.getArcList(this);

		// Previous lists
		var stickerList = puzzleData.getStickerList();
		var slotList = puzzleData.getSlotList();

		// Buffer list to construct the new list without modifying the old list
		var newStickerList = [];
		for (var i = 0; i < stickerList.length; i++)
			newStickerList.push(stickerList[i]);

		// Reorder newStickerList as necessary
		for (var i = 0; i < this.mapping.length; i++)
		{
			var j = this.mapping[i];

			// Swap indices around if inverting
			var a = i;
			var b = j;
			if (inverted) { a = j; b = i; }
			var start = a;
			if (inverted) start = b;

			// Perform the copy
			var sticker = stickerList[a];
			newStickerList[b] = sticker;
			sticker.moveToSlot(slotList[b], arcList[start], inverted);
		}

		// Copy results into puzzleData
		puzzleData.setStickerList(newStickerList);
	}

	next(index, inverted=false)
	{
		var ret = this.mapping[index];

		if (inverted)
			for (var i = 0; i < this.mapping.length; i++)
				if (this.mappign[i] == index)
					ret = i;
		
		return ret;
	}

	clone()
	{
		var ret = new Permutation(this.mapping.length, this.color, this.index);

		for (var i = 0; i < this.mapping.length; i++)
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
		this.arcMap = [];
		this.center = new vec2f(0.0, 0.0);
	}

	activatePermutation(index, inverted)
	{
		if (index >= this.permutationList.length) return;

		var permutation = this.permutationList[index];
		permutation.apply(this, inverted);
	}

	draw(context)
	{
		for (var i = 0; i < this.permutationList.length; i++)
		{
			var permutation = this.permutationList[i];
			permutation.draw(context, this.getArcList(permutation));
		}

		for (var i = 0; i < this.slotList.length; i++)
			this.slotList[i].draw(context);

		for (var i = 0; i < this.stickerList.length; i++)
			this.stickerList[i].draw(context);
	}

	addPermutation(permutation)
	{
		this.permutationList.push(permutation)
		this.arcMap[permutation.index] = [];

		for (var i = 0; i < this.slotList.length; i++)
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

	getPermutationListSize()
	{
		return this.permutationList.length;
	}

	getSlotListSize()
	{
		return this.slotList.length;
	}

	getStickerListSize()
	{
		return this.stickerList.length;
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
		if (permutation.index >= this.arcMap.length)
			return null;
		
		var arcList = this.arcMap[permutation.index];
		var mapping = permutation.getMapping();
		var nextIndex = mapping[nodeIndex];
		if (inverted)
		{
			for (var i = 0; i < mapping.length; i++)
				if (mapping[i] == nodeIndex)
					nextIndex = i;
		}

		return arcList[nextIndex];
	}

	setArc(permutation, nodeIndex, arc)
	{
		if (permutation.index >= this.arcMap.length)
			this.arcMap[permutation.index] = zeroArray(this.getSlotListSize());

		this.arcMap[permutation.index][nodeIndex] = arc;
	}

	getArcList(permutation)
	{
		return this.arcMap[permutation.index];
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

	getPuzzleData()
	{
		return this.puzzleData;
	}
	
	addNode(nodeName, nodeColor, nodeX, nodeY)
	{
		var newSticker = new Sticker(nodeColor);
		var newSlot = new Slot(newSticker, new vec2f(nodeX, nodeY), nodeColor);
		newSticker.moveToSlot(newSlot);
		this.puzzleData.addSlot(newSlot);
		this.puzzleData.addSticker(newSticker);
		this.nodeList.push(nodeName);
	}

	addPermutation(color, cycleList)
	{
		var n = this.puzzleData.slotList.length;
		var index = this.puzzleData.getPermutationListSize();
		var newPermutation = new Permutation(n, color, index);
		newPermutation.setCycles(cycleList);
		this.puzzleData.addPermutation(newPermutation);
		this.permutationMap[color] = newPermutation;
	}

	recenter()
	{
		var centerSum = new vec2f(0.0, 0.0);

		for (var i = 0; i < this.puzzleData.getSlotListSize(); i++)
		{
			var slot = this.puzzleData.getSlotList()[i];
			
			var slotCenter = slot.getCenter();
			centerSum = centerSum.add(slotCenter);
		}

		centerSum = centerSum.scale(1.0 / this.puzzleData.getSlotListSize());

		for (var i = 0; i < this.puzzleData.getSlotListSize(); i++)
		{
			var slot = this.puzzleData.getSlotList()[i];

			var slotCenter = slot.getCenter();
			slotCenter = slotCenter.sub(centerSum);
			slot.setCenter(slotCenter);
		}

		for (var i = 0; i < this.puzzleData.getPermutationListSize(); i++)
		{
			var permutation = this.puzzleData.getPermutationList()[i];
			var arcList = this.puzzleData.getArcList(permutation);
			for (var j = 0; j < arcList.length; j++)
			{
				var arc = arcList[j];
				arc.adjustCenter(centerSum);
			}
		}
	}

	normalize()
	{
		var maxRadius = -1.0;

		for (var i = 0; i < this.puzzleData.getSlotListSize(); i++)
		{
			var slot = this.puzzleData.getSlotList()[i];

			var slotCenter = slot.getCenter();
			var radius = slotCenter.norm();
			if (radius > maxRadius)
				maxRadius = radius;
		}

		for (var i = 0; i < this.puzzleData.getSlotListSize(); i++)
		{
			var slot = this.puzzleData.getSlotList()[i];

			var slotCenter = slot.getCenter();
			slotCenter = slotCenter.scale(1.0 / maxRadius);
			slot.setCenter(slotCenter);
		}

		for (var i = 0; i < this.puzzleData.getPermutationListSize(); i++)
		{
			var permutation = this.puzzleData.getPermutationList()[i];
			var arcList = this.puzzleData.getArcList(permutation);
			for (var j = 0; j < arcList.length; j++)
			{
				var arc = arcList[j];
				arc.normalize(maxRadius);
				arc.computeParameters();
			}
		}
	}
}



var leftPressed = false;
var rightPressed = false;

function testAAA()
{
    var builder = new PuzzleBuilder('puzzles/AAA');

    builder.addNode('lhs', '#ff0000', 1, 1);
    builder.addNode('rhs', '#0000ff', 4, 1);
    builder.addPermutation('#ff0000', [[0, 1]]);
	
	builder.recenter();
	builder.normalize();

    return builder.getPuzzleData();
}

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
		puzzleData.activatePermutation(0, true);
	}
	else if (e.keyCode == 37)
	{
		leftPressed = false;
		puzzleData.activatePermutation(1, true);
	}
	//if (37 <= e.keyCode && e.keyCode <= 40)
	//	puzzleData.activatePermutation(e.keyCode - 37, true);
	else if (e.keyCode == 38 && puzzleIndex + 1 < puzzleList.length)
		puzzleData = puzzleList[++puzzleIndex];
	else if (e.keyCode == 40 && puzzleIndex > 0)
		puzzleData = puzzleList[--puzzleIndex];
}

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
