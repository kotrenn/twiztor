class PuzzleBuilder
{
	constructor(name)
	{
		this.name = name;
		this.puzzleData = new PuzzleData(name);
		this.nodeList = [];
		this.permutationMap = {};
	}

	getPuzzleData()
	{
		this.reverseIndexList();
		return this.puzzleData;
	}

	reverseIndexList()
	{
		for (var i = 0; i < this.puzzleData.getPermutationListSize(); i++)
		{
			var j = this.puzzleData.getPermutationListSize() - i - 1;
			this.puzzleData.getPermutation(i).setReverseIndex(j);
		}
	}

	indexOf(nodeName)
	{
		for (var i = 0; i < this.puzzleData.getSlotListSize(); i++)
			if (this.puzzleData.getSlot(i).name == nodeName)
				return i;
		
		return -1;
	}

	addNode(nodeName, nodeColor, nodeShape, nodeX, nodeY)
	{
		var newSticker = new Sticker(nodeColor, nodeShape % NUM_SHAPES);
		var newSlot = new Slot(nodeName, newSticker, new vec2f(nodeX, nodeY), nodeColor);
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

	addCircleArc(arcColor, nodeName, circleR,
				 circlePlus, circleInverted, circleReversed, circleReflected)
	{
		var permutation = this.permutationMap[arcColor];
		var indexU = this.indexOf(nodeName);
		var indexV = permutation.next(indexU);
		var slotU = this.puzzleData.getSlot(indexU);
		var slotV = this.puzzleData.getSlot(indexV);
		var circleArc = NewCircleArc(permutation, slotU, slotV,
									 circleR, circlePlus, circleInverted,
									 circleReversed, circleReflected);
		this.puzzleData.setArc(permutation, indexU, circleArc);
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
