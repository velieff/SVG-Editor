#include<iostream>
#include<fstream>
#include"Shape.h"
#include"MyFunctions.h"

Shape::Shape()
{
	this->color = new char[1];
	this->color[0] = '\0';
}

Shape::Shape(Point& P, char* C)
{
	this->p = P;
	this->color = new char[len(C) + 1];
	cpy(this->color, C);
}

Shape::~Shape()
{
	destroy();
}

Shape::Shape(const Shape& other)
{
	copy(other);
}

Shape& Shape::operator=(const Shape& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

void Shape::set_color(char* Color)
{
	delete[] this->color;
	this->color = new char[len(Color) + 1];
	cpy(this->color, Color);
}

void Shape::set_point(Point& P)
{
	this->p = P;
}

char* Shape::get_color() const
{
	return this->color;
}

Point Shape::get_point() const
{
	return this->p;
}

void Shape::print(std::ostream& output) const
{
	// ...
}

void Shape::print_svg(std::ostream& output) const
{
	// ...
}

void Shape::translate(Point& P)
{
	// ...
}

bool Shape::within_circle(Point& P, int R) const
{
	return false;
}

bool Shape::within_rectangle(Point& P, int W, int H) const
{
	return false;
}

Shape* Shape::get_copy() const
{
	return NULL;
}

const char* Shape::get_type() const
{
	return NULL;
}

void Shape::copy(const Shape& other)
{
	this->color = new char[len(other.color) + 1];
	cpy(this->color, other.color);
	this->p = other.p;
}

void Shape::destroy()
{
	delete[] this->color;
}