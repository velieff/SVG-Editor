#include<iostream>
#include"Shape.h"

#ifndef _RECTANGLE_HEADER_
#define _RECTANGLE_HEADER_

class Rectangle : public Shape
{
private:
	int w, h;
public:
	Rectangle();
	Rectangle(Point& P, int W, int H, char* C);
	virtual ~Rectangle();
	Rectangle(const Rectangle& other);
	Rectangle& operator=(const Rectangle& other);

	virtual void print(std::ostream& output) const;
	virtual void print_svg(std::ostream& output) const;
	virtual void translate(Point& P);
	virtual bool within_circle(Point& P, int R) const;
	virtual bool within_rectangle(Point& P, int W, int H) const;
	virtual Shape* get_copy() const;
	virtual const char* get_type() const;
};

#endif