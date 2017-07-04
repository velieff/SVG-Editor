#include<iostream>
#include"Rectangle.h"
#include"MyFunctions.h"

Rectangle::Rectangle() : Shape()
{
	this->w = 0;
	this->h = 0;
}

Rectangle::Rectangle(Point& P, int W, int H, char* C) : Shape(P, C)
{
	this->w = W;
	this->h = H;
}

Rectangle::~Rectangle()
{
	destroy();
}

Rectangle::Rectangle(const Rectangle& other) : Shape(other)
{
	this->w = other.w;
	this->h = other.h;
}

Rectangle& Rectangle::operator=(const Rectangle& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
		this->w = other.w;
		this->h = other.h;
	}
	return *this;
}

void Rectangle::print(std::ostream& output) const
{
	output << get_type() << ' ' << get_point() << ' ' << this->w << ' ' << this->h << ' ' << get_color() << '\n';
}

void Rectangle::print_svg(std::ostream& output) const
{
	output << "<rect x = \"" << get_point().get_x() << "\" y = \"" << get_point().get_y()
		<< "\" width = \"" << this->w << "\" height = \"" << this->h << "\" fill = \"" << get_color() << "\" />\n";
}

void Rectangle::translate(Point& P)
{
	set_point(get_point() + P);
}

bool Rectangle::within_circle(Point& P, int R) const
{
	return (((square(get_point().get_x() - P.get_x()) + square(get_point().get_y() - P.get_y())) <= square(R)) &&
		((square((get_point().get_x() + this->w) - P.get_x()) + square((get_point().get_y() + this->h) - P.get_y())) <= square(R)) &&
		((square((get_point().get_x() + this->w) - P.get_x()) + square(get_point().get_y() - P.get_y())) <= square(R)) &&
		((square(get_point().get_x() - P.get_x()) + square((get_point().get_y() + this->h) - P.get_y())) <= square(R)));
}

bool Rectangle::within_rectangle(Point& P, int W, int H) const
{
	return ((get_point().get_x() >= P.get_x()) && (get_point().get_x() <= (P.get_x() + W)) &&
		(get_point().get_y() >= P.get_y()) && (get_point().get_y() <= (P.get_y() + H)) &&
		((get_point().get_x() + this->w) >= P.get_x()) && ((get_point().get_x() + this->w) <= (P.get_x() + W)) &&
		((get_point().get_y() + this->h) >= P.get_y()) && ((get_point().get_y() + this->h) <= (P.get_y() + H)));
		
}

Shape* Rectangle::get_copy() const
{
	return new Rectangle(*this);
}

const char* Rectangle::get_type() const
{
	return "rectangle";
}