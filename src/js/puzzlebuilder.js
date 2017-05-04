class PuzzleBuilder
{
	constructor()
	{
		this.permutationFactory = new PermutationFactory();
		this.slotFactory = new SlotFactory();
		this.stickerFactory = new StickerFactory();
		this.puzzleData = null;
		this.nodeMap = NodeMap();
	}

	function beginPuzzle(name)
	{
		this.puzzleData = new PuzzleData(name);
	}

	function compilePuzzle()
	{
		return this.puzzleData;
	}

	function addNode(name, color, center)
	{
		var newSticker = this.stickerFactory.makeSticker(color);
		var newSlot = this.slotFactory.makeSlot(color, center);
		newSticker.moveToSlot(newSlot);

		this.puzzleData.addSlot(newSlot);
		this.puzzleData.addSticker(newSticker);

		if (this.nodeMap.find(name) == this.nodeMap.end())
			this.nodeMap[name] = this.nodeMap.size();
	}

	function addPermutation(color, cycleList)
	{
		var indexedCycleList;

		for (var cycle : cycleList)
		{
			var indexedCycle;

			for (var name : cycle)
			{
				var index = this.nodeMap[name];
				indexedCycle += [index];
			}

			indexedCycleList += [indexedCycle];
		}

		this.permutationFactory.makePermutation(this.nodeMap.size(),
												color,
												0,
												indexedCycleList);
	}

	function makeCircleArc(color, src, dst, center)
	{
	}

	function makeLineArc(color, src, dst)
	{
	}
}
