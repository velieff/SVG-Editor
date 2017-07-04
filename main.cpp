/**
*
*	SVG Editor
*
*	Object-oriented programming
*	Solution to course project
*	Faculty of Mathematics and Informatics of Sofia University
*	Summer semester 2016/2017
*
*	Created By Merhat Veliev
*	https://github.com/velieff/SVG-Editor
*
*/

/**
*
*	VALID COMMANDS:
*	1) open <svg-filename>				-opens <svg-filename>
*	2) print					-prints shapes
*	3) create <shape-type> <coordinates> <color>	-creates new shape
*	4) erase <number>				-erases existing shape
*	5) translate <number> <horizontal> <vertical>	-translates only one shape
*	6) tranlsate all <horizontal> <vertical>	-translates all shapes
*	7) within <shape-type> <coordinates>		-checks whether there are shapes within another shape
*	8) save						-saves changes to the original file
*	9) save as <new-svg-filename>			-saves changes to new file
*	10) close					-closes the file
*	11) exit					-exit the program
*
*/

#include<iostream>
#include"SVG.h"
#include"MyFunctions.h"

int main()
{
	SVG svg;
	char* command = new char[STRING_SIZE];

	do
	{
		std::cin.getline(command, STRING_SIZE);

		if (contains(command, "open"))
			svg.open(command);

		else if (contains(command, "close"))
			svg.close();

		else if (contains(command, "save as"))
			svg.save_as(command);

		else if (contains(command, "save"))
			svg.save();

		else if (contains(command, "exit"))
			std::cout << "Goodbye.\n";

		else if (contains(command, "print"))
			std::cout << svg;

		else if (contains(command, "create"))
			svg.create(command);

		else if (contains(command, "erase"))
			svg.erase();

		else if (contains(command, "translate all"))
			svg.translate_all(command);

		else if (contains(command, "translate"))
			svg.translate();

		else if (contains(command, "within"))
			svg.within(command);

		else
			std::cout << "Invalid comand.\n";

	}
	while (!contains(command, "exit"));

	delete[] command;
	return 0;
}
