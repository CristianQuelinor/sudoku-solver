#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

// Assuming that the cursor is in "index"
// Returns true if the grid is valid, else false
bool isValid(int grid[9][9], bool isInRow[9][9], bool isInColumn[9][9], bool isInBloc[9][9], int index) {
	if (index == 81) // It means we have finished the grid
		return true;

	int row = index/9, column = index%9;

	if (grid[row][column] != 0) // If the grid's not empty, it means we have to go no the next index
		return isValid(grid, isInRow, isInColumn, isInBloc, index+1);

	for (int k = 0; k < 9; k++) { // Test of every possible value
		if (!isInRow[row][k] && !isInColumn[column][k] && !isInBloc[3*(row/3)+(column/3)][k]) {
			// Let's assume the correct value is k (well, k + 1 actually)
			isInRow[row][k] = true;
			isInColumn[column][k] = true;
			isInBloc[3*(row/3)+(column/3)][k] = true;

			if (isValid(grid, isInRow, isInColumn, isInBloc, index+1)) {
				grid[row][column] = k + 1; // We write in the right box
				return true;
			}

			// Erasing of the old value in case it was wrong
			isInRow[row][k] = false;
			isInColumn[column][k] = false;
			isInBloc[3*(row/3)+(column/3)][k] = false;
		}
	}

	return false;
}

// Solve the grid (backtracking algorithm)
void solve(int grid[9][9]) {
	bool isInRow[9][9];
	bool isInColumn[9][9];
	bool isInBloc[9][9];

	// Init
	for (int row = 0 ; row < 9 ; row++) {
		for (int column = 0 ; column < 9 ; column++) {
			isInRow[row][column] = false;
			isInColumn[row][column] = false;
			isInBloc[row][column] = false;
		}
	}

	// Init, writting true where it's supposed to be
	int t;
	for (int row = 0 ; row < 9 ; row++) {
		for (int column = 0 ; column < 9 ; column++) {
			int t = grid[row][column];

			if (t != 0) { // If the box's not empty - 1;
				t--;
				isInRow[row][t] = true;
				isInColumn[column][t] = true;
				isInBloc[3*(row/3)+(column/3)][t] = true;
			}
		}
	}

	isValid(grid, isInRow, isInColumn, isInBloc, 0);
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
