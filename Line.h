#include<iostream>
#include"Shape.h"

#ifndef _LINE_HEADER_
#define _LINE_HEADER_

class Line : public Shape
{
private:
	Point p2;
public:
	Line();
	Line(Point& P1, Point& P2);
	virtual ~Line();
	Line(const Line& other);
	Line& operator=(const Line& other);

	virtual void print(std::ostream& output) const;
	virtual void print_svg(std::ostream& output) const;
	virtual void translate(Point& P);
	virtual bool within_circle(Point& P, int R) const;
	virtual bool within_rectangle(Point& P, int W, int H) const;
	virtual Shape* get_copy() const;
	virtual const char* get_type() const;
};

#endif