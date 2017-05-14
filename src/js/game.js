var leftPressed = false;
var rightPressed = false;

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
	if (e.keyCode == 39)
	{
		rightPressed = true;
	}
	else if (e.keyCode == 37)
	{
		leftPressed = true;
	}
}

function keyUp(e)
{
	if (e.keyCode == 37 && puzzleIndex > 0)
		puzzleData = puzzleList[--puzzleIndex];
	if (e.keyCode == 39 && puzzleIndex + 1 < puzzleList.length)
		puzzleData = puzzleList[++puzzleIndex];
	if (49 <= e.keyCode && e.keyCode <= 57)
		puzzleData.activatePermutation(e.keyCode - 49, true);
	if (e.keyCode == 48)
		puzzleData.activatePermutation(10, true);
}

function update()
{
}

function draw()
{
	context.clearRect(0, 0, canvas.width, canvas.height);

	puzzleData.draw(context);
}

function loop()
{
	update();
	draw();
}

var canvas = document.getElementById("gameCanvas");
var context = canvas.getContext("2d");

document.addEventListener("keydown", keyDown, false);
document.addEventListener("keyup", keyUp, false);

setInterval(loop, 10);
