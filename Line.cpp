#include<iostream>
#include"Line.h"
#include"MyFunctions.h"

Line::Line() : Shape()
{
	// ...
}

Line::Line(Point& P1, Point& P2) : Shape(P1, "")
{
	this->p2 = P2;
}

Line::~Line()
{
	destroy();
}

Line::Line(const Line& other) : Shape(other)
{
	this->p2 = other.p2;
}

Line& Line::operator=(const Line& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
		this->p2 = other.p2;
	}
	return *this;
}

void Line::print(std::ostream& output) const
{
	output << get_type() << ' ' << get_point() << ' ' << p2 << '\n';
}

void Line::print_svg(std::ostream& output) const
{
	output << '<' << get_type() << " x1 = \"" << get_point().get_x() << "\" y1 = \"" << get_point().get_y()
		<< "\" x2 = \"" << p2.get_x() << "\" y2 = \"" << p2.get_y() << "\" />\n";
}

void Line::translate(Point& P)
{
	set_point(get_point() + P);
	p2 += P;
}

bool Line::within_circle(Point& P, int R) const
{
	return (((square(get_point().get_x() - P.get_x()) + square(get_point().get_y() - P.get_y())) <= square(R)) &&
		((square(p2.get_x() - P.get_x()) + square(p2.get_y() - P.get_y())) <= square(R)));
}

bool Line::within_rectangle(Point& P, int W, int H) const
{
	return ((get_point().get_x() >= P.get_x()) && (get_point().get_x() <= (P.get_x() + W)) &&
		(get_point().get_y() >= P.get_y()) && (get_point().get_y() <= (P.get_y() + H)) &&
		(p2.get_x() >= P.get_x()) && (p2.get_x() <= (P.get_x() + W)) &&
		(p2.get_y() >= P.get_y()) && (p2.get_y() <= (P.get_y() + H)));
}

Shape* Line::get_copy() const
{
	return new Line(*this);
}

const char* Line::get_type() const
{
	return "line";
}