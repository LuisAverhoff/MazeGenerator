#include "Maze.hpp"
#include <iostream>
#include <random>
#include <stack>

constexpr int MAX_NEIGHBOURS = 4;

namespace RandomCellNumGenerator
{
	std::random_device rd;
	std::default_random_engine randEngine(rd());
}

Maze::Maze(int totalRows, int totalColmuns): ROWS(totalRows), COLUMNS(totalColmuns)
{
	cells.reserve(ROWS * COLUMNS);

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			cells.push_back(Cell(i, j));
		}
	}
}

void Maze::displayMaze(std::vector<std::string> &contentForFile) const
{
	for (int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLUMNS; j++)
		{
			if (cells[i * COLUMNS + j].walls[0])
			{
				contentForFile.push_back("+---");
				std::cout << "+---";
			}
			else
			{
				contentForFile.push_back("+   ");
				std::cout << "+   ";
			}
		}
		
		contentForFile.push_back("+\n");
		std::cout << "+" << std::endl;

		for (int j = 0; j < COLUMNS; j++)
		{
			if (cells[i * COLUMNS + j].walls[3])
			{
				contentForFile.push_back("|   ");
				std::cout << "|   ";
			}
			else
			{
				contentForFile.push_back("    ");
				std::cout << "    ";
			}
		}

		contentForFile.push_back("|\n");
		std::cout << "|" << std::endl;
	}

	for (int i = 0; i < COLUMNS; i++)
	{
		contentForFile.push_back("+---");
		std::cout << "+---";
	}
	
	contentForFile.push_back("+\n");
	std::cout << "+" << std::endl;
}

void Maze::generateMaze()
{
	std::uniform_int_distribution<int> distRow(0, ROWS - 1);
	std::uniform_int_distribution<int> distColumn(0, COLUMNS - 1);

	int startingRow = distRow(RandomCellNumGenerator::randEngine);
	int startingColumn = distColumn(RandomCellNumGenerator::randEngine);

	generateMaze(startingRow, startingColumn);
}

void Maze::generateMaze(int row, int column)
{
	int currentNeighbour = getCellIndex(row, column);

	std::stack<Cell> dfs;
	dfs.push(cells[currentNeighbour]);
	cells[currentNeighbour].setVisitedCell(true);

	while (!dfs.empty())
	{
		int nextNeighbour = getNeighbourCell(row, column);

		if (nextNeighbour != -1)
		{
			dfs.push(cells[nextNeighbour]);
			cells[nextNeighbour].setVisitedCell(true);
			removeWalls(currentNeighbour, nextNeighbour);
			row = cells[nextNeighbour].getRowNumber();
			column = cells[nextNeighbour].getColumnNumber();
			currentNeighbour = nextNeighbour;
		}
		else
		{
			dfs.pop();

			if (!dfs.empty())
			{
				row = dfs.top().getRowNumber();
				column = dfs.top().getColumnNumber();
				currentNeighbour = row * COLUMNS + column;
			}
		}
	}
}

int Maze::getNeighbourCell(int row, int column)
{
	int neighbours[MAX_NEIGHBOURS];
	int validNeighbours = 0;

	int top = getCellIndex(row - 1, column);
	int right = getCellIndex(row, column + 1);
	int bottom = getCellIndex(row + 1, column);
	int left = getCellIndex(row, column - 1);

	if (top != -1 && !cells[top].isCellVisited())
	{
		neighbours[validNeighbours] = top;
		validNeighbours++;
	}

	if (right != -1 && !cells[right].isCellVisited())
	{
		neighbours[validNeighbours] = right;
		validNeighbours++;
	}

	if (bottom != -1 && !cells[bottom].isCellVisited())
	{
		neighbours[validNeighbours] = bottom;
		validNeighbours++;
	}

	if (left != -1 && !cells[left].isCellVisited())
	{
		neighbours[validNeighbours] = left;
		validNeighbours++;
	}

	if (validNeighbours > 0)
	{
		std::uniform_int_distribution<int> distNeighbours(0, validNeighbours - 1);
		int randomNeighbourCellIndex = distNeighbours(RandomCellNumGenerator::randEngine);
		int nextNeighbourIndex = neighbours[randomNeighbourCellIndex];
		return nextNeighbourIndex;
	}

	return -1;
}

int Maze::getCellIndex(int row, int column) const
{
	if (row < 0 || column < 0 || row > ROWS - 1 || column > COLUMNS - 1)
		return -1;
	return (row * COLUMNS) + column;
}

void Maze::removeWalls(int currentNeighbour, int nextNeighbour)
{
	int result = cells[currentNeighbour].getRowNumber() - cells[nextNeighbour].getRowNumber();
	
	if (result != 0)
	{
		if (result == 1)
		{
			cells[currentNeighbour].walls[0] = false;
			cells[nextNeighbour].walls[2] = false;
		}
		else if (result == -1)
		{
			cells[currentNeighbour].walls[2] = false;
			cells[nextNeighbour].walls[0] = false;
		}
	}
	else
	{
		result = cells[currentNeighbour].getColumnNumber() - cells[nextNeighbour].getColumnNumber();

		if (result == 1)
		{
			cells[currentNeighbour].walls[3] = false;
			cells[nextNeighbour].walls[1] = false;
		}
		else if (result == -1)
		{
			cells[currentNeighbour].walls[1] = false;
			cells[nextNeighbour].walls[3] = false;
		}
	}
}