class ButtonPanel
{
	constructor()
	{
		this.buttonList = [];
		this.puzzleData = null;

		this.panelX = 0;
		this.panelY = 0;
		this.panelW = 0;
		this.panelH = 0;

		this.PANEL_COLOR   = '#aaaaaa';
		this.BORDER_LEFT   = 10;
		this.BORDER_RIGHT  = 10;
		this.BORDER_TOP    = 10;
		this.BORDER_BOTTOM = 2 * this.BORDER_TOP + FONT_SIZE;

		this.selectionIndex = -1;

		this.selectionX = 0;
		this.selectionY = 0;
		this.selectionW = 0;
		this.selectionH = 0;

		this.SELECTION_BORDER = 5;
		this.SELECTION_COLOR  = '#000000';
	}

	setPuzzleData(puzzleData)
	{
		this.puzzleData = puzzleData;
		this.buttonList = [];
		this.selectionIndex = -1;
		
		if (this.puzzleData == null) return;
		
		for (var i = 0; i < this.puzzleData.getPermutationListSize(); i++)
		{
			var permutation = this.puzzleData.getPermutation(i);
			this.buttonList.push(new Button(permutation));
		}

		if (this.buttonList.length > 0)
			this.selectionIndex = 0;

		this.refreshUI();
	}

	getSelectedButton()
	{
		if ((this.selectionIndex <  0) ||
		    (this.selectionIndex >= this.buttonList.length))
			return null;
		
		return this.buttonList[this.selectionIndex];
	}

	prevButton()
	{
		if (this.selectionIndex - 1 < 0) return;
		
		this.selectionIndex--;
		this.refreshUI();
	}

	nextButton()
	{
		if (this.selectionIndex + 1 > this.buttonList.length) return;

		this.selectionIndex++;
		this.refreshUI();
	}

	refreshUI()
	{
		var minX = g_gameCanvas.width;
		var minY = g_gameCanvas.height;
		var maxX = -1;
		var maxY = -1;
		
		for (var i = 0; i < this.buttonList.length; i++)
		{
			var button = this.buttonList[i];
			
			var buttonMinX = button.buttonX;
			var buttonMinY = button.buttonY;
			var buttonMaxX = button.buttonX + button.buttonW;
			var buttonMaxY = button.buttonY + button.buttonH;
			
			if (buttonMinX < minX) minX = buttonMinX;
			if (buttonMinY < minY) minY = buttonMinY;
			if (buttonMaxX > maxX) maxX = buttonMaxX;
			if (buttonMaxY > maxY) maxY = buttonMaxY;
		}
		
		this.panelW = maxX - minX + this.BORDER_LEFT + this.BORDER_RIGHT;
		this.panelH = maxY - minY + this.BORDER_TOP  + this.BORDER_BOTTOM;;
		this.panelX = minX - this.BORDER_LEFT;
		this.panelY = minY - this.BORDER_TOP;

		var selectedButton = this.getSelectedButton();
		if (selectedButton == null) return;

		this.selectionX = selectedButton.buttonX -     this.SELECTION_BORDER;
		this.selectionY = selectedButton.buttonY -     this.SELECTION_BORDER;
		this.selectionW = selectedButton.buttonW + 2 * this.SELECTION_BORDER;
		this.selectionH = selectedButton.buttonH + 2 * this.SELECTION_BORDER;
	}

	drawUI(context)
	{
		if (this.puzzleData == null) return;
		if (this.buttonList.length == 0) return;

		// Draw the background
		fillRectUI(context,
				   this.PANEL_COLOR,
				   this.panelX,
				   this.panelY,
				   this.panelW,
				   this.panelH);

		// Highlight the selected button
		fillRectUI(context,
				   this.SELECTION_COLOR,
				   this.selectionX,
				   this.selectionY,
				   this.selectionW,
				   this.selectionH);

		// Draw the buttons
		for (var i = 0; i < this.buttonList.length; i++)
			this.buttonList[i].drawUI(context);
	}
}
