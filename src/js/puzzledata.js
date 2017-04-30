class PuzzleData
{
	constructor()
	{
		this.name = "";
		this.permutationList = [];
		this.slotList = [];
		this.stickerList = [];
		this.center = vec2f(0.0, 0.0);
	}

	function makeTestLevel()
	{
		// Type conversions between 1.0 colorf and 255 colori?
		var red    = colorf('red',    1.0, 0.0, 0.0);
		var yellow = colorf('yellow', 1.0, 1.0, 0.0);
		var green  = colorf('green',  0.0, 1.0, 0.0);
		var blue   = colorf('blue',   0.0, 0.0, 1.0);

		var slot0 = this.slotFactory.makeSlot(red,    new vec2f( 0.0, -3.0));
		var slot1 = this.slotFactory.makeSlot(yellow, new vec2f( 0.0,  0.0));
		var slot2 = this.slotFactory.makeSlot(green,  new vec2f(-3.0,  3.0));
		var slot3 = this.slotFactory.makeSlot(blue,   new vec2f( 3.0,  3.0));

		var slotArray = [ slot0, slot1, slot2, slot3 ];

		for (slot : slotArray)
		{
			addSlot(slot);
			slotSticker = slot.getSticker();
			slotSticker.moveToSlot(slot); // shouldn't this be in factory implementation?
			addSticker(slotSticker);
		}
		
		var cycles0 = [ [ 0, 1 ], [ 2 ], [ 3 ] ];
		var cycles1 = [ [ 0 ], [ 1, 2, 3 ] ];

		var p0 = this.permutationFactory.makePermutation(4, red, 0, cycles0);
		var p1 = this.permutationFactory.makePermutation(4, blue, 1, cycles1);

		addPermutation(p0);
		addPermutation(p1);
	}

	function getArc(permutation, nodeIndex, inverted)
	{
		if (this.arcMap.count(permutation) == 0) return null;
		var varcList = this.arcMap.at(permutation);

		var mapping = permutation.getMapping();
		var nextIndex = mapping[nodeIndex];
		if (inverted)
			for (var i = 0; i < mapping.size(); i++)
				if (mapping[i] == nodeIndex)
					nextIndex = i;

		return arcList[nextIndex];
	}

	function setArc(permutation, nodeIndex, arc)
	{
		if (this.arcMap.count(permutation) == 0)
			this.arcMap[permutation] = [null * getSlotListSize()];

		this.arcMap[permutation][nodeIndex] = arc;
	}
}
