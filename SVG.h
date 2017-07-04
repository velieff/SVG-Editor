#include<iostream>
#include"Shape.h"
#include"Line.h"
#include"Rectangle.h"
#include"Circle.h"

#ifndef _SVG_HEADER_
#define _SVG_HEADER_

class SVG
{
private:
	Shape** shapes;
	int size;
	int capacity;
	char* filename;
	char** text;
	int rows;
	bool opened;

public:
	SVG();
	~SVG();
	SVG(const SVG& other);
	SVG& operator=(const SVG& other);

	void add(char* str);
	void create(char* str);
	void open(char* str);
	void close();
	void save() const;
	void save_as(char* str) const;
	friend std::ostream& operator<<(std::ostream& output, const SVG& svg);
	void print_svg(std::ostream& output) const;
	void erase();
	void translate();
	void translate_all(char* str);
	void within(char* str);
	void read_from_file(std::ifstream& input);
	void set_filename(char* file_name);
	char* get_filename() const;
	bool is_opened() const;

private:
	void erase(int i);
	void translate_all(Point& P);
	void translate(int i, Point& P);
	void within_circle(Point& P, int R) const;
	void within_rectangle(Point& P, int W, int H) const;

	void initialize();
	void copy(const SVG& other);
	void destroy();
	void resize();
};

#endif