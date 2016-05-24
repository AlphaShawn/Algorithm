
/**
 * Calculate the double area of triangle with vertex p, q, s
 * The return area value can be nagative, if the point s is in right side of p->q
 * @param  p [description]
 * @param  q [description]
 * @param  s [description]
 * @return   [description]
 */
double Area2(Point p, Point q, Point s)
{
	/*
				| p.x  p.y  1 |
		area =	| q.x  q.y  1 |
	     		| s.x  s.y  1 |
	 */
	return p.x*q.y + p.y*s.x + q.x*s.y - q.y*s.x - p.y*q.x - p.x*s.y;
}

/**
 * Determine whether point s is in the left side of p->q
 * This function is depend on Area2 function
 * @param  p [description]
 * @param  q [description]
 * @param  s [description]
 * @return   true: point s is in the left side of p->q
 *           false: s is in the right side or on the p->q segment.
 */
bool ToLeft(Point p, Point q, Point s)
{
	return Area2(p, q, s)>0;
}