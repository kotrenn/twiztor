function zeroArray(n)
{
	var ret = [];
	for (var i = 0; i < n; i++)
		ret.push(0);
	return ret;
}

function linearArray(n)
{
	var ret = [];
	for (var i = 0; i < n; i++)
		ret.push(i);
	return ret;
}

function linearStrArray(n)
{
	var ret = [];
	for (var i = 0; i < n; i++)
		ret.push(i.toString());
	return ret;
}
