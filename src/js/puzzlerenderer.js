class PuzzleRenderer
{
	constructor(graphics)
	{
		this.graphics = graphics;
	}

	function render(puzzleData)
	{
		this.graphics.pushMatrix();
		this.graphics.translate2fv(puzzleData.getCenter());
		
		for (permutation : puzzleData.getPermutationList())
			permutation.render(puzzleData.getSlotList(), puzzleData.getArcList());

		for (slot : puzzleData.getSlotList())
			slot.render();

		for (sticker : puzzleData.getStickerList())
			sticker.render();

		this.graphics.popMatrix();
	}
}
