// http://stackoverflow.com/questions/1527803/generating-random-whole-numbers-in-javascript-in-a-specific-range
function randInt(min, max)
{
	return Math.floor(Math.random() * (max - min + 1)) + min;
}
