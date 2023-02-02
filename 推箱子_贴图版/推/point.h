#ifndef POINT_H
#define POINT_H

class point
{
public:
	point(int x = -1, int y = -1);
	point(const point& p);
	point operator+(const point& t)const;
	point& operator+=(const point& t);
	point& operator-=(const point& t);
	int x, y;
};

#endif
