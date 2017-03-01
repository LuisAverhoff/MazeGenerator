// MazeGenerator.cpp : Defines the entry point for the console application.
#include "Maze.hpp"
#include <regex>

int main()
{
	Maze maze(9, 17);
	maze.generateMaze();
	maze.displayMaze();
	system("pause");
    return 0;
}

