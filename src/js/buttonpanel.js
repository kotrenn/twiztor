class ButtonPanel
{
	constructor()
	{
		this.buttonList = [];
		this.puzzleData = null;
	}

	setPuzzleData(puzzleData)
	{
		this.puzzleData = puzzleData;
		this.buttonList = [];
		
		if (this.puzzleData == null) return;
		
		for (var i = 0; i < this.puzzleData.getPermutationListSize(); i++)
		{
			var permutation = this.puzzleData.getPermutation(i);
			this.buttonList.push(new Button(permutation));
		}
	}

	drawUI(context)
	{
		for (var i = 0; i < this.buttonList.length; i++)
			this.buttonList[i].drawUI(context);
	}
}
