// MazeGenerator.cpp : Defines the entry point for the console application.
#include "Maze.hpp"
#include <iostream>
#include <sstream>
#include <string>

int getInt(std::string prompt);

int main()
{
	int totalRows, totalColumns;

	totalRows = getInt("How many rows do you want the maze to have? ");
	totalColumns = getInt("How many columns do you want the maze to have? ");
	std::cout << std::endl;

	Maze maze(totalRows, totalColumns);
	maze.generateMaze();
	maze.displayMaze();

	system("pause");

    return 0;
}

int getInt(std::string prompt)
{
	int retInteger;
	std::string strNumber;

	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, strNumber);
		std::stringstream convert(strNumber);

		if (convert >> retInteger && !(convert >> strNumber))
			return retInteger;

		std::cin.clear();
		std::cerr << "Input must be an integer with only one argument! Please try again." << std::endl << std::endl;
	}
}

