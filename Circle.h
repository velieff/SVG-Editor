#include<iostream>
#include"Shape.h"

#ifndef _CIRCLE_HEADER_
#define _CIRCLE_HEADER_

class Circle : public Shape
{
private:
	int r;
public:
	Circle();
	Circle(Point& P, int R, char* C);
	virtual ~Circle();
	Circle(const Circle& other);
	Circle& operator=(const Circle& other);

	virtual void print(std::ostream& output) const;
	virtual void print_svg(std::ostream& output) const;
	virtual void translate(Point& P);
	virtual bool within_circle(Point& P, int R) const;
	virtual bool within_rectangle(Point& P, int W, int H) const;
	virtual Shape* get_copy() const;
	virtual const char* get_type() const;
};

#endif