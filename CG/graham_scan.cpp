/**
 *	Algorithm:  Convex hull, graham scan
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.5.25
 * 	Language:  	C++11
 *
 */

class Point
{
public:
	double x, y;
	bool extreme;
};


/**
 * Calculate the extreme point of S[], which is the point in the convex hull.
 * The extreme porperty is marked in point.extreme value.
 * @param S array of point, which is sorted by x 
 * @param n size of array
 */
void grahamScan(Point S[], int n)
{
	for (int i = 0; i < n; i++)
		S[i].extreme = false;
	int pStack[MAXNUM];
	int p = -1;
	pStack[++p] = 0;
	pStack[++p] = 1;
	for (int i = 2; i < n; i++)
	{
		while (p >= 1 && ToLeft(S[pStack[p - 1]], S[pStack[p]], S[i]))
			p--;
		pStack[++p] = i;
	}
	while (p>=0)
		S[pStack[p--]].extreme = true;

	pStack[++p] = n - 1;
	pStack[++p] = n - 2;
	for (int i = n - 3; i >= 0; i--)
	{
		while (p >= 1 && ToLeft(S[pStack[p - 1]], S[pStack[p]], S[i]))
			p--;
		pStack[++p] = i;
	}
	while (p >= 0)
		S[pStack[p--]].extreme = true;
}