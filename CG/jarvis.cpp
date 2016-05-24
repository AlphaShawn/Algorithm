/**
 *	Algorithm:  Convex hull, jarvis
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
	int succ;
};

/**
 * Lowest then leftmost point in point array S[]
 * @param  S [description]
 * @param  n [description]
 * @return   the index of the point
 */
int LTL(Point S[], int n)
{
	int ans = 0;
	for (int i = 1; i < n; i++)
		if (S[i].y < S[ans].y || (fabs(S[i].y - S[ans].y) < 1e-7 && S[i].x < S[ans].x))
			ans = i;
	return ans;
}

/**
 * [Jarvis description]
 * @param S array of point, do not need sorted
 * @param n size of array
 */
void Jarvis(Point S[], int n)
{
	for (int i = 0; i < n; i++)
		S[i].extreme = false;
	int ltl = LTL(S, n);
	int k = ltl;
	do
	{
		S[k].extreme = true;
		int next = -1;
		for (int i = 0; i < n; i++)
		{
			if (i != k && i != next && (next == -1 || !ToLeft(S[k], S[next], S[i])))
				next = i;
		}
		S[k].succ = next;
		k = next;
	} while (k != ltl);
}