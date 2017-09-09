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
		this.easierList = [];
		this.harderList = [];
		this.localMap = [];
	}

	solve()
	{
		for (var i = 0; i < this.stickerList.length; i++)
		{
			var sticker = this.stickerList[i];
			sticker.cloneSlot();
		}
	}

	randomize()
	{
		var numPermutations = this.getPermutationListSize();
		for (var i = 0; i < 1000; i++)
		{
			var randomIndex = randInt(1, numPermutations) - 1;
			var randomInverted = randInt(1, 2) == 1;
			this.activatePermutation(randomIndex, randomInverted);
		}
	}

	activatePermutation(index, inverted)
	{
		if (index >= this.permutationList.length) return;

		var permutation = this.permutationList[index];
		permutation.apply(this, inverted);
	}

	draw(context)
	{
		drawString(context, '#000000', this.name, 5, 20);
		
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

	addEasier(puzzleName)
	{
		this.easierList.push(puzzleName);
	}

	addHarder(puzzleName)
	{
		this.harderList.push(puzzleName);
	}

	addLocalMap(mapStr)
	{
		this.localMap.push(mapStr);
	}

	getEasierList()
	{
		return this.easierList;
	}

	getHarderList()
	{
		return this.harderList;
	}

	getLocalMap()
	{
		return this.localMap;
	}
	
	addPermutation(permutation)
	{
		this.permutationList.push(permutation)
		this.arcMap[permutation.index] = [];

		for (var i = 0; i < this.slotList.length; i++)
		{
			var slotU = this.slotList[i];
			var slotV = this.slotList[permutation.next(i)];
			var lineArc = NewLineArc(permutation, slotU, slotV);
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
