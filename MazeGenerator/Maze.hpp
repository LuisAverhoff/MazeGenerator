#pragma once

#include<vector>

class Maze
{
	public:
		Maze(int totalRows, int totalColumns);
		void displayMaze(std::vector<std::string> &contentForFile) const;
		void generateMaze();
		void generateMaze(int row, int column);
		int getNeighbourCell(int row, int column);
		int getCellIndex(int row, int column) const;
		void removeWalls(int currentCellIndex, int nextNeighbour);

	private:
		struct  Cell
		{
			Cell(int r, int col)
			{
				row = r;
				column = col;
				visited = false;
			}

			int getRowNumber() const
			{
				return row;
			}

			int getColumnNumber() const
			{
				return column;
			}

			bool Cell::isCellVisited() const
			{
				return visited;
			}

			void Cell::setVisitedCell(bool visit)
			{
				visited = visit;
			}

			int row;
			int column;
			bool visited;
			static const int MAX_WALLS = 4;

			bool walls[MAX_WALLS] = {true, true, true, true}; // Top, right, bottom, left.
		};

	private:
		std::vector<Cell> cells;

	public:
		const int ROWS;
		const int COLUMNS;
};