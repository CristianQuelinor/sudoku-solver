#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include "list.h"

// STATIC FUNCTIONS
static int isValid(int grid[9][9], LIST* toExamine);
static int count(int grid[9][9], int i, int j);

// GLOBAL VARIABLES
int isInRow[9][9];
int isInColumn[9][9];
int isInBloc[9][9];

// Assuming that the cursor is in "toExamine"
// Returns 1 if the grid is valid, else 0
static int isValid(int grid[9][9], LIST* toExamine) {	
	if (toExamine == NULL) // It means we have finished the grid
		return 1;

	int row = toExamine->i, column = toExamine->j, k;

	if (grid[row][column] != 0) // If the grid's not empty, it means we have to go no the next case
		return isValid(grid, toExamine->next);

	for (k = 0; k < 9; k++) { // Test of every possible value
		if (!isInRow[row][k] && !isInColumn[column][k] && !isInBloc[3*(row/3)+(column/3)][k]) {
			// Let's assume the correct value is k (well, k + 1 actually)
			isInRow[row][k] = 1;
			isInColumn[column][k] = 1;
			isInBloc[3*(row/3)+(column/3)][k] = 1;

			if (isValid(grid, toExamine->next)) {
				grid[row][column] = k + 1; // We write in the right box
				return 1;
			}

			// Erasing of the old value in case it was wrong
			isInRow[row][k] = 0;
			isInColumn[column][k] = 0;
			isInBloc[3*(row/3)+(column/3)][k] = 0;
		}
	}

	return 0;
}

// Returns the number of possible values in (i, j)
static int count(int grid[9][9], int row, int column) {
	int ret = 0, k;
	
	for (k = 0 ; k < 9 ; k++)
		if (!isInRow[row][k] && !isInColumn[column][k] && !isInBloc[3*(row/3)+(column/3)][k])
			k++;
	
	return ret;
}

// Solve the grid (backtracking algorithm)
void solve(int grid[9][9]) {
	// Initialization of the "path" to follow to test solutions
	int row, column;
	LIST* toExamine = NULL;
	
	for (row = 0 ; row < 9 ; row++)
		for (column = 0 ; column < 9 ; column++)
			if (grid[row][column] == 0)
				pushFront(&toExamine, row, column, count(grid, row, column));

	toExamine = insertionSort(toExamine);
	
	// Init of arrays
	for (row = 0 ; row < 9 ; row++) {
		for (column = 0 ; column < 9 ; column++) {
			isInRow[row][column] = 0;
			isInColumn[row][column] = 0;
			isInBloc[row][column] = 0;
		}
	}

	// Init of arrays
	int t;
	for (row = 0 ; row < 9 ; row++) {
		for (column = 0 ; column < 9 ; column++) {
			t = grid[row][column];

			if (t != 0) { // If the box's not empty; // isInRow[row][t] = 1 <==> t+1 is in the row
				t--;
				isInRow[row][t] = 1;
				isInColumn[column][t] = 1;
				isInBloc[3*(row/3)+(column/3)][t] = 1;
			}
		}
	}

	isValid(grid, toExamine);
	
	deleteList(&toExamine);
}

// Load the grid
int loadGrid(int grid[9][9]) {
	int row = 0, column = 0;

	FILE *file;
	file = fopen ("../files/grid.in", "r");

	if (file == NULL) {
		printf("Error: Couln't open grid");
		return 0;
	}

	char c;

	while ((c = getc(file)) != EOF) {
		if (c == '\n')
			continue;

		grid[row][column] = (int)(strtol(&c, NULL, 10));

		if (column <= 9)
			column += 1;
			
		if (column == 9) {
			column = 0;
			row += 1;

			if (row == 9)
				break;
		}
	}

	fclose (file);
	return 1;
}

// Print the grid
void print(int grid[9][9]) {
	int row, column;
	for (row = 0 ; row < 9 ; row++) {
		for (column = 0 ; column < 9 ; column++) {
			if (column == 3 || column == 6)
				printf("|");

			printf("%d", grid[row][column]);
		}

		if (row == 2 || row == 5)
			printf("\n===========");

		printf("\n");
	}
}
