var g_shiftPressed = false;
var g_showHelp = false;

var g_actionPanel = null;

function testAAA()
{
    var builder = new PuzzleBuilder('puzzles/AAA');

    builder.addNode('lhs', '#ff0000', 1, 1);
    builder.addNode('rhs', '#0000ff', 4, 1);
    builder.addPermutation('#ff0000', [[0, 1]]);
	builder.addCircleArc('#ff0000', 'lhs', 2.2, true, false);
	builder.addCircleArc('#ff0000', 'rhs', 2.2, true, false);
	
	builder.recenter();
	builder.normalize();

    return builder.getPuzzleData();
}

function refreshPuzzle()
{
	if (puzzleIndex <                  0) puzzleIndex = 0;
	if (puzzleIndex >= puzzleList.length) puzzleIndex = puzzleList.length - 1;
	
	puzzleData = puzzleList[puzzleIndex];
	g_actionPanel.setPuzzleData(puzzleData);
}

function previousPuzzle()
{
	--puzzleIndex;
	refreshPuzzle();
}

function nextPuzzle()
{
	++puzzleIndex;
	refreshPuzzle();
}

function keyDown(e)
{
	if (e.keyCode == 16) // SHIFT
		g_shiftPressed = true;
}

function keyUp(e)
{
	var inverted = g_shiftPressed == true;
	if (e.keyCode == 16) // SHIFT
		g_shiftPressed = false;
	if (49 <= e.keyCode && e.keyCode <= 57) // 1, 2, 3, 4, 5, 6, 7, 8, 9
		puzzleData.activatePermutation(e.keyCode - 49, inverted);
	if (e.keyCode == 48) // 0
		puzzleData.activatePermutation(10, inverted);
	if (e.keyCode == 90) // Z
		previousPuzzle();
	if (e.keyCode == 88) // X
		nextPuzzle();
	if (e.keyCode == 72) // H
		g_showHelp = g_showHelp == false;
	if (e.keyCode == 82) // R
		puzzleData.randomize();
	if (e.keyCode == 83) // S
		puzzleData.solve();
	if (e.keyCode == 74) // J
		g_actionPanel.prevAction();
	if (e.keyCode == 76) // L
		g_actionPanel.nextAction();
	if (e.keyCode == 73) // I
		g_actionPanel.activateAction(false);
	if (e.keyCode == 75) // K
		g_actionPanel.activateAction(true);
}

function update()
{
}

function draw()
{
	g_gameContext.clearRect(0, 0, g_gameCanvas.width, g_gameCanvas.height);

	puzzleData.draw(g_gameContext);
	g_actionPanel.drawUI(g_gameContext);

	var controls = [
					'1, 2, 3, 4, 5 - Activate Permutation',
					'6, 7, 8, 9, 0',
					' [Hold] Shift - Reverse Permutation',
		            '            Z - Previous Puzzle',
					'            X - Next Puzzle',
					'            R - Randomize Puzzle',
					'            S - Solve Puzzle',
					'            J - Previous Action',
					'            L - Next Action',
                    '            I - Activate Action',
             		'            K - Activate Action (R)'
	               ];
	var helpMsg  = 'H - Show Help';
	var startY = g_gameCanvas.height - 20 * controls.length - 10;
	if (g_showHelp)
		for (var i = 0; i < controls.length; i++)
			drawString(g_gameContext, '#000000', controls[i], 5, startY + 20 * i);
	drawString(g_gameContext, '#000000', helpMsg, 5, startY + 20 * controls.length);
}

function loop()
{
	update();
	draw();
}

function main()
{
	g_actionPanel = new ActionPanel();
	refreshPuzzle();
	
	document.addEventListener("keydown", keyDown, false);
	document.addEventListener("keyup", keyUp, false);

	setInterval(loop, 10);
}
