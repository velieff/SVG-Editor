#include<iostream>
#include"Point.h"

Point::Point()
{
	set(0, 0);
}

Point::Point(int X, int Y)
{
	set(X, Y);
}

Point::~Point()
{
	// ...
}

Point::Point(const Point& other)
{
	set(other.x, other.y);
}

Point& Point::operator=(const Point& other)
{
	if (this != &other)
		set(other.x, other.y);
	return *this;
}

void Point::set(int X, int Y)
{
	this->x = X;
	this->y = Y;
}

int Point::get_x() const
{
	return this->x;
}

int Point::get_y() const
{
	return this->y;
}

std::ostream& operator<<(std::ostream& output, const Point& p)
{
	return output << p.x << ' ' << p.y;
}

Point& Point::operator+=(const Point& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Point operator+(const Point& p1, const Point& p2)
{
	Point tmp(p1);
	tmp += p2;
	return tmp;
}