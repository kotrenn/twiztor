var shiftPressed = false;

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

function keyDown(e)
{
	if (e.keyCode == 16) // SHIFT
		shiftPressed = true;
}

function keyUp(e)
{
	var inverted = shiftPressed == true;
	if (e.keyCode == 16) // SHIFT
		shiftPressed = false;
	if (e.keyCode == 37 && puzzleIndex > 0) // LEFT
		puzzleData = puzzleList[--puzzleIndex];
	if (e.keyCode == 39 && puzzleIndex + 1 < puzzleList.length) // RIGHT
		puzzleData = puzzleList[++puzzleIndex];
	if (49 <= e.keyCode && e.keyCode <= 57) // 1, 2, 3, 4, 5, 6, 7, 8, 9
		puzzleData.activatePermutation(e.keyCode - 49, inverted);
	if (e.keyCode == 48) // 0
		puzzleData.activatePermutation(10, inverted);
}

function update()
{
}

function draw()
{
	g_gameContext.clearRect(0, 0, g_gameCanvas.width, g_gameCanvas.height);

	puzzleData.draw(g_gameContext);
}

function loop()
{
	update();
	draw();
}

document.addEventListener("keydown", keyDown, false);
document.addEventListener("keyup", keyUp, false);

setInterval(loop, 10);
