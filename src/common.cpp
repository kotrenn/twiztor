#include "common.h"

// http://stackoverflow.com/a/236803
void split(const string &s,
           char delim,
           vector<string> &elems,
           unsigned int maxElems)
{
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
		if (maxElems > 0 && elems.size() + 1 == maxElems)
			delim = '|';
	}
}

// http://stackoverflow.com/a/236803
vector<string> split(const string &s,
                     char delim,
                     unsigned int maxElems)
{
	//cout << "split(\"" << s << "\", " << maxElems << ")" << endl;
	vector<string> elems;
	split(s, delim, elems, maxElems);
	//for (string tok : elems)
	//	cout << "  elem: \"" << tok << "\"" << endl;
	return elems;
}
