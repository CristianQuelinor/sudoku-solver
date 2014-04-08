#ifndef FONCTIONS
#define FONCTIONS

bool isNotInRow(int k, int grid[9][9], int row);
bool isNotInColumn(int k, int grid[9][9], int column);
bool isNotInBloc(int k, int grid[9][9], int _row, int _column);
bool isValid(int grid[9][9], int position);
void solve(int grid[9][9]);
bool loadGrid(int grid[9][9]);
void print(int grid[9][9]);

#endif
