#include<iostream>
#include"SVG.h"
#include"MyFunctions.h"

SVG::SVG()
{
	initialize();
}

SVG::~SVG()
{
	destroy();
}

SVG::SVG(const SVG& other)
{
	copy(other);
}

SVG& SVG::operator=(const SVG& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}
	return *this;
}

void SVG::add(char* str)
{
	if (this->size >= this->capacity)
		resize();
	char* color = NULL;
	this->shapes[size] = get_shape_from_svg(str,color);
	if (this->shapes[size])
		size++;
	if (color)
		delete[] color;
}

void SVG::create(char* str)
{
	if (is_opened())
	{
		if (this->size >= this->capacity)
			resize();
		int* p = NULL;
		char* color = NULL;
		this->shapes[size] = create_shape(str, p, color);
		if (this->shapes[size])
		{
			std::cout << "Created a " << this->shapes[size]->get_type() << ".\n";
			size++;
		}
		if (p)
			delete[] p;
		if (color)
			delete[] color;
	}
	else
		print_not_opened();
}

void SVG::open(char* str)
{
	if (!is_opened())
	{
		char* file_name = get_file_name(str, "open ");
		std::ifstream input;
		input.open(file_name);
		if (input.is_open())
		{
			set_filename(file_name);
			read_from_file(input);
			this->opened = true;
			std::cout << "The file is opened.\n";
		}
		else
			std::cout << "The file is not valid.\n";
		input.close();
		delete[] file_name;
	}
	else
		std::cout << "There is an opened file.\n";
}

void SVG::close()
{
	if (is_opened())
	{
		destroy();
		initialize();
		this->opened = false;
		std::cout << "The file is closed.\n";
	}
	else
		print_not_opened();
}

void SVG::save() const
{
	if (is_opened())
	{
		std::ofstream output;
		output.open(this->filename);
		print_svg(output);
		output.close();
		std::cout << "Saved.\n";
	}
	else
		print_not_opened();
}

void SVG::save_as(char* str) const
{
	if (is_opened())
	{
		char* new_filename = get_file_name(str, "save as ");
		std::ofstream output;
		output.open(new_filename);
		print_svg(output);
		output.close();
		std::cout << "Saved as: " << new_filename << '\n';
		delete[] new_filename;
	}
	else
		print_not_opened();
}

std::ostream& operator<<(std::ostream& output, const SVG& svg)
{
	if (svg.is_opened())
	{
		for (int i = 0; i < svg.size; i++)
		{
			output << i + 1 << ". ";
			svg.shapes[i]->print(output);
		}
	}
	else
		print_not_opened();
	return output;
}

void SVG::print_svg(std::ostream& output) const
{
	for (int i = 0; i < this->rows; i++)
		output << this->text[i] << '\n';
	output << "<svg>\n";
	for (int i = 0; i < this->size; i++)
	{
		this->shapes[i]->print_svg(output);
	}
	output << "</svg>\n";
}

void SVG::erase()
{
	if (is_opened())
	{
		std::cout << *this;
		std::cout << "Which figure do you want to erase: ";
		int n;
		std::cin >> n;
		erase(n);
	}
	else
		print_not_opened();
}

void SVG::translate()
{
	if (is_opened())
	{
		std::cout << *this;
		int n, h, v;
		std::cout << "Which figure do you want to translate: ";
		std::cin >> n;
		std::cout << "horizontal=";
		std::cin >> h;
		std::cout << "vertical=";
		std::cin >> v;
		translate(n, Point(h, v));
	}
	else
		print_not_opened();
}

void SVG::translate_all(char* str)
{
	if (is_opened())
	{
		int* p = get_values(str);
		translate_all(Point(p[0], p[1]));
		delete[] p;
	}
	else
		print_not_opened();
}

void SVG::within(char* str)
{
	if (is_opened())
	{
		if (contains(str, "circle"))
		{
			int* p = get_values(str);
			within_circle(Point(p[0], p[1]), p[2]);
			delete[] p;
		}

		else if (contains(str, "rectangle"))
		{
			int* p = get_values(str);
			within_rectangle(Point(p[0], p[1]), p[2], p[3]);
			delete[] p;
		}

		else
			std::cout << "Invalid comand.\n";
	}
	else
		print_not_opened();
}

void SVG::read_from_file(std::ifstream& input)
{
	while (!input.eof() && this->rows < STRING_SIZE)
	{
		text[this->rows] = new char[STRING_SIZE];
		input.getline(text[this->rows], STRING_SIZE);
		if (contains(this->text[this->rows], "<svg>"))
		{
			delete[] this->text[this->rows];
			break;
		}
		this->rows++;
	}

	char* str = new char[STRING_SIZE];
	while (!input.eof())
	{
		input.getline(str, STRING_SIZE);
		if (contains(str, "</svg>"))
			break;
		else
			add(str);
	}

	delete[] str;
}

void SVG::set_filename(char* file_name)
{
	delete[] this->filename;
	this->filename = new char[len(file_name) + 1];
	cpy(this->filename, file_name);
}

char* SVG::get_filename() const
{
	return this->filename;
}

bool SVG::is_opened() const
{
	return this->opened;
}

void SVG::erase(int i)
{
	if ((i - 1) < 0 || (i - 1) >= this->size)
	{
		std::cout << "There is no figure number " << i << "!\n";
		return;
	}
	const char* type = this->shapes[i - 1]->get_type();
	this->size--;
	for (int j = i - 1; j < this->size; j++)
	{
		this->shapes[j] = this->shapes[j + 1];
	}
	std::cout << "Erased a " << type << " (" << i << ").\n";
}

void SVG::translate_all(Point& P)
{
	if (this->size > 0)
	{
		for (int i = 0; i < this->size; i++)
			shapes[i]->translate(P);
		std::cout << "Translated all figures.\n";
	}
}

void SVG::translate(int i, Point& P)
{
	if ((i - 1) < 0 || (i - 1) >= this->size)
	{
		std::cout << "There is no figure number " << i << "!\n";
		return;
	}
	shapes[i - 1]->translate(P);
	std::cout << "Translated a " << shapes[i - 1]->get_type() << " (" << i << ").\n";
}

void SVG::within_circle(Point& P, int R) const
{
	int k = 1;
	for (int i = 0; i < this->size; i++)
	{
		if (shapes[i]->within_circle(P, R))
		{
			std::cout << k << ". ";
			shapes[i]->print(std::cout);
			k++;
		}
	}
	if (k == 1)
		std::cout << "No figures are located within circle " << P << ' ' << R << ".\n";
}

void SVG::within_rectangle(Point& P, int W, int H) const
{
	int k = 1;
	for (int i = 0; i < this->size; i++)
	{
		if (shapes[i]->within_rectangle(P, W, H))
		{
			std::cout << k << ". ";
			shapes[i]->print(std::cout);
			k++;
		}
	}
	if (k == 1)
		std::cout << "No figures are located within rectangle " << P << ' ' << W << ' ' << H << ".\n";
}

void SVG::initialize()
{
	this->size = 0;
	this->capacity = 4;
	this->shapes = new Shape*[capacity];
	this->filename = new char[1];
	this->filename[0] = '\0';
	this->text = new char*[STRING_SIZE];
	this->rows = 0;
	this->opened = false;
}

void SVG::copy(const SVG& other)
{
	this->size = other.size;
	this->capacity = other.capacity;
	this->shapes = new Shape*[capacity];
	for (int i = 0; i < this->size; i++)
		this->shapes[i] = other.shapes[i]->get_copy();
	this->filename = new char[len(other.filename) + 1];
	cpy(this->filename, other.filename);
	this->text = new char*[STRING_SIZE];
	this->rows = other.rows;
	for (int i = 0; i < this->rows; i++)
	{
		this->text[i] = new char[len(other.text[i]) + 1];
		cpy(this->text[i], other.text[i]);
	}
	this->opened = other.opened;
}

void SVG::destroy()
{
	for (int i = 0; i < this->size; i++)
		this->shapes[i]->destroy();
	delete[] this->shapes;
	delete[] this->filename;
	for (int i = 0; i < this->rows; i++)
		delete[] this->text[i];
	delete[] this->text;
}

void SVG::resize()
{
	this->capacity *= 2;
	Shape** tmp = new Shape*[capacity];
	for (int i = 0; i < this->size; i++)
	{
		tmp[i] = shapes[i];
	}
	delete[] this->shapes;
	this->shapes = tmp;
}