class ActionPanel
{
	constructor()
	{
		this.actionList = [];
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
		this.actionList = [];
		this.selectionIndex = -1;
		
		if (this.puzzleData == null) return;
		
		for (var i = 0; i < this.puzzleData.getPermutationListSize(); i++)
		{
			var permutation = this.puzzleData.getPermutation(i);
			var action = new Action();
			var pos = 0;
			var depth = this.puzzleData.getPermutationListSize() - i;
			action.addPermutation(permutation, pos, depth);
			this.actionList.push(action);
		}

		if (this.actionList.length >= 2)
		{
			var comboAction = new Action();
			var perm0 = this.puzzleData.getPermutation(0);
			var perm1 = this.puzzleData.getPermutation(1);
			var pos   = this.puzzleData.getPermutationListSize() + 1;
			comboAction.addPermutation(perm0, 0, pos);
			comboAction.addPermutation(perm1, 1, pos);
			this.actionList.push(comboAction);
		}

		if (this.actionList.length > 0)
			this.selectionIndex = 0;

		this.refreshUI();
	}

	getSelectedAction()
	{
		if ((this.selectionIndex <  0) ||
		    (this.selectionIndex >= this.actionList.length))
			return null;
		
		return this.actionList[this.selectionIndex];
	}

	prevAction()
	{
		if (this.selectionIndex < 0) return;
		
		this.selectionIndex--;
		this.selectionIndex += this.actionList.length;
		this.selectionIndex %= this.actionList.length;
		this.refreshUI();
	}

	nextAction()
	{
		if (this.selectionIndex < 0) return;
		
		this.selectionIndex++;
		this.selectionIndex %= this.actionList.length;
		this.refreshUI();
	}

	activateAction(inverted)
	{
		var action = this.getSelectedAction();
		action.apply(this.puzzleData, inverted);
	}

	refreshUI()
	{
		var minX = g_gameCanvas.width;
		var minY = g_gameCanvas.height;
		var maxX = -1;
		var maxY = -1;
		
		for (var i = 0; i < this.actionList.length; i++)
		{
			var action = this.actionList[i];
			
			var actionMinX = action.getMinX();
			var actionMinY = action.getMinY();
			var actionMaxX = action.getMaxX();
			var actionMaxY = action.getMaxY();
			
			if (actionMinX < minX) minX = actionMinX;
			if (actionMinY < minY) minY = actionMinY;
			if (actionMaxX > maxX) maxX = actionMaxX;
			if (actionMaxY > maxY) maxY = actionMaxY;
		}
		
		this.panelW = maxX - minX + this.BORDER_LEFT + this.BORDER_RIGHT;
		this.panelH = maxY - minY + this.BORDER_TOP  + this.BORDER_BOTTOM;;
		this.panelX = minX - this.BORDER_LEFT;
		this.panelY = minY - this.BORDER_TOP;

		var selectedAction = this.getSelectedAction();
		if (selectedAction == null) return;

		var actionMinX = selectedAction.getMinX();
		var actionMinY = selectedAction.getMinY();
		var actionMaxX = selectedAction.getMaxX();
		var actionMaxY = selectedAction.getMaxY();
		
		this.selectionX =              actionMinX -     this.SELECTION_BORDER;
		this.selectionY =              actionMinY -     this.SELECTION_BORDER;
		this.selectionW = actionMaxX - actionMinX + 2 * this.SELECTION_BORDER;
		this.selectionH = actionMaxY - actionMinY + 2 * this.SELECTION_BORDER;
	}

	drawUI(context)
	{
		if (this.puzzleData == null) return;
		if (this.actionList.length == 0) return;

		// Draw the background
		fillRectUI(context,
				   this.PANEL_COLOR,
				   this.panelX,
				   this.panelY,
				   this.panelW,
				   this.panelH);

		// Highlight the selected action
		fillRectUI(context,
				   this.SELECTION_COLOR,
				   this.selectionX,
				   this.selectionY,
				   this.selectionW,
				   this.selectionH);

		// Draw the actions
		for (var i = 0; i < this.actionList.length; i++)
			this.actionList[i].drawUI(context);
	}
}
