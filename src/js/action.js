class Action
{
	constructor()
	{
		this.buttonList = [];
	}

	addPermutation(permutation, depth, pos)
	{
		if (this.buttonList.length == 0)
		{
			var n                   = permutation.getSize();
			var color               = permutation.getColor();
			var identityPermutation = new Permutation(n, color, -1);
			var identityButton      = new Button(identityPermutation, 0, pos);
			this.buttonList.push(identityButton);
		}
		
		var button = new Button(permutation, depth, pos);
		this.buttonList.push(button);
	}

	apply(puzzleData, inverted)
	{
		for (var i = 1; i < this.buttonList.length; i++)
		{
			var button = this.buttonList[i];
			var permutation = button.getPermutation();
			permutation.apply(puzzleData, inverted);
		}
	}

	startIndex()
	{
		var ret = 0;
		if (this.buttonList.length == 2)
			ret = 1;

		return ret;
	}

	drawUI(context)
	{
		for (var i = this.startIndex(); i < this.buttonList.length; i++)
			this.buttonList[i].drawUI(context);

		// Draw number
		if (this.buttonList.length == 2)
			drawString(context,
				      '#000000',
				      this.buttonList[1].numStr,
				      this.buttonList[1].numX,
				      this.buttonList[1].numY);
	}

	getMinX()
	{
		var ret = g_gameCanvas.width;
		
		for (var i = this.startIndex(); i < this.buttonList.length; i++)
		{
			var button = this.buttonList[i];
			if (button == null) continue;
			var buttonMinX = button.getMinX();
			if (buttonMinX < ret) ret = buttonMinX;
		}

		return ret;
	}
	
	getMinY()
	{
		var ret = g_gameCanvas.height;
		
		for (var i = this.startIndex(); i < this.buttonList.length; i++)
		{
			var button = this.buttonList[i];
			if (button == null) continue;
			var buttonMinY = button.getMinY();
			if (buttonMinY < ret) ret = buttonMinY;
		}

		return ret;
	}
	
	getMaxX()
	{
		var ret = -1;
		
		for (var i = this.startIndex(); i < this.buttonList.length; i++)
		{
			var button = this.buttonList[i];
			if (button == null) continue;
			var buttonMaxX = button.getMaxX();
			if (buttonMaxX > ret) ret = buttonMaxX;
		}

		return ret;
	}
	
	getMaxY()
	{
		var ret =-1;
		
		for (var i = this.startIndex(); i < this.buttonList.length; i++)
		{
			var button = this.buttonList[i];
			if (button == null) continue;
			var buttonMaxY = button.getMaxY();
			if (buttonMaxY > ret) ret = buttonMaxY;
		}

		return ret;
	}
}
