#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "fonctions.h"

int main() {
	int grid[9][9];

	loadGrid(grid);
	print(grid);
	solve(grid);

	printf("\n======== SOLVING ========\n\n");

	print(grid);

	return 0;
}
