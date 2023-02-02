#include "point.h"

point::point(int x, int y) :x(x), y(y)
{
}

point::point(const point& p) {
	x = p.x;
	y = p.y;
}

point point::operator+(const point& t)const {
	return point(x + t.x, y + t.y);
}

point& point::operator-=(const point& t) {
	x -= t.x;
	y -= t.y;
	return *this;
}

point& point::operator+=(const point& t) {
	x += t.x;
	y += t.y;
	return *this;
}
