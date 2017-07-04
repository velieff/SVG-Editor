#include<iostream>
#include"Shape.h"
#include"Line.h"
#include"Rectangle.h"
#include"Circle.h"
#include"SVG.h"

const int VALUE_SIZE = 8;
const int STRING_SIZE = 256;

inline int square(int a)
{
	return (a * a);
}

inline int absolute(int a)
{
	return (a < 0 ? a * (-1) : a);
}

inline int len(char* str)
{
	int num = 0;
	while (str[num])
		num++;
	return num;
}

inline void cpy(char* a, char* b)
{
	int num = 0;
	while (b[num])
	{
		a[num] = b[num];
		num++;
	}
	a[num] = '\0';
}

inline bool contains(char* a, char* b)
{
	int len_a = len(a), len_b = len(b);
	for (int i = 0; i < len_a; i++)
	{
		if (a[i] == b[0] || absolute(int(a[i]) - int(b[0])) == 32)
		{
			for (int j = 0; j < len_b; j++)
			{
				if (a[i + j] != b[j] && absolute(int(a[i + j]) - int(b[j])) != 32)
					break;
				if (j == len_b - 1)
					return true;
			}
		}
	}
	return false;
}

inline int find(char* a, char* b, int start)
{
	int len_a = len(a), len_b = len(b);
	for (int i = start; i < len_a; i++)
	{
		if (a[i] == b[0])
		{
			for (int j = 0; j < len_b; j++)
			{
				if (a[i + j] != b[j] && absolute(int(a[i + j]) - int(b[j])) != 32)
					break;
				if (j == len_b - 1)
					return (i + j);
			}
		}
	}
	return -1;
}

inline int get_value(char* str, char* what)
{
	int i = find(str, what, 5), k = 0;
	if (i == -1)
		return i;
	while (str[i] != '\"')
		i++;
	char* val = new char[VALUE_SIZE];
	i++;
	while (str[i + k] != '\"')
	{
		val[k] = str[i + k];
		k++;
	}
	val[k] = '\0';
	int value = atoi(val);
	delete[] val;
	return value;
}

inline char* get_color(char* str, char* what)
{
	int i = find(str, what, 5), k = 0;
	if (i == -1)
		return NULL;
	while (str[i] != '\"')
		i++;
	char* color = new char[VALUE_SIZE];
	i++;
	while (str[i + k] != '\"')
	{
		color[k] = str[i + k];
		k++;
	}
	color[k] = '\0';
	return color;
}

inline Shape* get_shape_from_svg(char* str, char*& color)
{
	if (contains(str, "line"))
	{
		int x1 = get_value(str, "x1"),
			y1 = get_value(str, "y1"),
			x2 = get_value(str, "x2"),
			y2 = get_value(str, "y2");
		return new Line(Point(x1, y1), Point(x2, y2));
	}

	else if (contains(str, "rect"))
	{
		int x = get_value(str, "x"),
			y = get_value(str, "y"),
			w = get_value(str, "width"),
			h = get_value(str, "height");
		color = get_color(str, "fill");
		return new Rectangle(Point(x, y), w, h, color);
	}

	else if (contains(str, "circle"))
	{
		int cx = get_value(str, "cx"),
			cy = get_value(str, "cy"),
			r = get_value(str, "r");
		color = get_color(str, "fill");
		return new Circle(Point(cx, cy), r, color);
	}

	else
		return NULL;
}

inline bool is_digit(char a)
{
	return (a >= '0' && a <= '9');
}

inline bool is_letter(char a)
{
	return ((a >= 'a'&& a <= 'z') || (a >= 'A'&& a <= 'Z'));
}

inline int* get_values(char* str)
{
	int* p = new int[4];
	int n = len(str), j = 0;
	for (int i = 0; i < n; i++)
	{
		if (is_digit(str[i]) && j < 4)
		{
			char* val = new char[VALUE_SIZE];
			int k = i;
			while (is_digit(str[i]))
			{
				val[i - k] = str[i];
				i++;
			}
			val[i - k] = '\0';
			p[j] = atoi(val);
			j++;
			delete[] val;
		}
	}
	while (j < 4)
	{
		p[j] = 0;
		j++;
	}
	return p;
}

inline char* get_color_cr(char* str)
{
	char* color = new char[VALUE_SIZE];
	int n = len(str);
	for (int i = n - 1; i >= 0; i--)
	{
		if (is_letter(str[i]) && str[i - 1] == ' ')
		{
			int j = 0;
			while (is_letter(str[j + i]) && (j + i) < n)
			{
				color[j] = str[j + i];
				j++;
			}
			color[j] = '\0';
			return color;
		}
	}
}

inline Shape* create_shape(char* str, int*& p, char*& color)
{
	int n = len(str);
	if (contains(str, "line"))
	{
		p = get_values(str);
		return new Line(Point(p[0], p[1]), Point(p[2], p[3]));
	}

	else if (contains(str, "rectangle"))
	{
		p = get_values(str);
		color = get_color_cr(str);
		return new Rectangle(Point(p[0], p[1]), p[2], p[3], color);
	}

	else if (contains(str, "circle"))
	{
		p = get_values(str);
		color = get_color_cr(str);
		return new Circle(Point(p[0], p[1]), p[2], color);
	}

	else
		return NULL;
}

inline char* get_file_name(char* str, char* what)
{
	int n = len(what), i;
	char* filename = new char[STRING_SIZE];
	for (i = 0; str[i + n]; i++)
		filename[i] = str[i + n];
	filename[i] = '\0';
	return filename;
}

inline void print_not_opened()
{
	std::cout << "There is not any opened file.\n";
}