#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

// Returns true if k is in the row, else false
bool isNotInRow(int k, int grid[9][9], int row) {
	for (int column = 0 ; column < 9 ; column++) {
		if (grid[row][column] == k)
			return false;
	}

	return true;
}

// Returns true if k is in the column, else false
bool isNotInColumn(int k, int grid[9][9], int column) {
	for (int row = 0 ; row < 9 ; row++) {
		if (grid[row][column] == k)
			return false;
	}

	return true;
}

// Returns true if k is in the bloc whose left top corner is (row, column), else false
bool isNotInBloc(int k, int grid[9][9], int _row, int _column) {
	_row = _row-(_row%3);
	_column = _column-(_column%3);
	for (int row = _row ; row < _row + 3 ; row++) {
		for (int column = _column ; column < _column + 3 ; column++) {
			if (grid[row][column] == k)
				return false;
		}
	}

	return true;
}

// Assuming that the cursor is in "index"
// Returns true if the grid is valid, else false
bool isValid(int grid[9][9], int index) {
	if (index == 81) // It means we have finished the grid
		return true;

	int row = index/9, column = index%9;

	if (grid[row][column] != 0) // If the grid's not empty, it means we have to go no the next index
		return isValid(grid, index+1);

	for (int k = 1; k <= 9; k++) { // Test of every possible value
		if (isNotInRow(k, grid, row) && isNotInColumn(k, grid, column) && isNotInBloc(k, grid, row, column)) {
			grid[row][column] = k; // Let's assume the correct value is k

			if (isValid(grid, index+1))
				return true;
		}
	}

	grid[row][column] = 0; // Erasing of the old value in case it was wrong
	return false;
}

// Solve the grid
void solve(int grid[9][9]) {
	isValid(grid, 0);
}

// Load the grid
bool loadGrid(int grid[9][9]) {
	int row = 0, column = 0;

	FILE *file;
	file = fopen ("../files/grid.in", "r");

	if (file == NULL)
	{
		printf("Error: Couln't open grid");
		return false;
	}

	char c;

	while ((c = getc(file)) != EOF) {
		if (c == '\n')
			continue;

		grid[row][column] = (int)(strtol(&c, NULL, 10));

		if (column <= 9) {
			column += 1;
		}
		if (column == 9) {
			column = 0;
			row += 1;

			if (row == 9) {
				break;
			}
		}
	}

	fclose (file);
	return true;
}

// Print the grid
void print(int grid[9][9]) {
	for (int row = 0 ; row < 9 ; row++) {
		for (int column = 0 ; column < 9 ; column++) {
			if (column == 3 || column == 6)
				printf("|");

			printf("%d", grid[row][column]);
		}

		if (row == 2 || row == 5)
			printf("\n===========");

		printf("\n");
	}
}
