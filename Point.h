#include<iostream>

#ifndef _POINT_HEADER_
#define _POINT_HEADER_

class Point
{
private:
	int x, y;
public:
	Point();
	Point(int X, int Y);
	~Point();
	Point(const Point& other);
	Point& operator=(const Point& other);

	void set(int X, int Y);
	int get_x() const;
	int get_y() const;

	friend std::ostream& operator<<(std::ostream& output, const Point& p);
	Point& operator+=(const Point& other);
	friend Point operator+(const Point& p1, const Point& p2);
};

#endif