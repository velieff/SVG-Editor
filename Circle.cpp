#include<iostream>
#include"Circle.h"
#include"MyFunctions.h"

Circle::Circle() : Shape()
{
	this->r = 0;
}

Circle::Circle(Point& P, int R, char* C) : Shape(P, C)
{
	this->r = R;
}

Circle::~Circle()
{
	destroy();
}

Circle::Circle(const Circle& other) : Shape(other)
{
	this->r = other.r;
}

Circle& Circle::operator=(const Circle& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
		this->r = other.r;
	}
	return *this;
}

void Circle::print(std::ostream& output) const
{
	output << get_type() << ' ' << get_point() << ' ' << this->r << ' ' << get_color() << '\n';
}

void Circle::print_svg(std::ostream& output) const
{
	output << '<' << get_type() << " cx = \"" << get_point().get_x() << "\" cy = \"" << get_point().get_y()
		<< "\" r = \"" << this->r << "\" fill = \"" << get_color() << "\" />\n";
}

void Circle::translate(Point& P)
{
	set_point(get_point() + P);
}

bool Circle::within_circle(Point& P, int R) const
{
	return (((square(get_point().get_x() - P.get_x()) + square(get_point().get_y() - P.get_y())) <= square(this->r + R)) &&
		((square(get_point().get_x() - P.get_x()) + square(get_point().get_y() - P.get_y())) >= square(this->r - R)));
}

bool Circle::within_rectangle(Point& P, int W, int H) const
{
	return (((get_point().get_x() - this->r) >= P.get_x()) && ((get_point().get_x() + this->r) <= (P.get_x() + W)) &&
		((get_point().get_y() - this->r) >= P.get_y()) && ((get_point().get_y() + this->r) <= (P.get_y() + H)));
}

Shape* Circle::get_copy() const
{
	return new Circle(*this);
}

const char* Circle::get_type() const
{
	return "circle";
}