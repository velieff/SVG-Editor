#include<iostream>
#include<fstream>
#include"Point.h"

#ifndef _SHAPE_HEADER_
#define _SHAPE_HEADER_

class Shape
{
private:
	Point p;
	char* color;
public:
	Shape();
	Shape(Point& P, char* C);
	virtual ~Shape();
	Shape(const Shape& other);
	Shape& operator=(const Shape& other);

	void set_color(char* Color);
	void set_point(Point& P);
	char* get_color() const;
	Point get_point() const;

	virtual void print(std::ostream& output) const;
	virtual void print_svg(std::ostream& output) const;
	virtual void translate(Point& P);
	virtual bool within_circle(Point& P, int R) const;
	virtual bool within_rectangle(Point& P, int W, int H) const;
	virtual Shape* get_copy() const;
	virtual const char* get_type() const;

	void copy(const Shape& other);
	void destroy();
};

#endif