#include <bits/stdc++.h>
using namespace std;

bool isSudokuValid(vector<vector<int> > &sudoku)
{
    map<int, bool> row[9], col[9];
    map<int, bool> subGrid[3][3];

    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            if (sudoku[r][c] == 0)
            {
                continue;
            }

            // If the current value of sudoku was present in the current column, row, and subgrid previously, return false.
            if (subGrid[r / 3][c / 3][sudoku[r][c]] || col[c][sudoku[r][c]] || row[r][sudoku[r][c]])
            {
                return false;
            }

            // Mark the current value of sudoku as true in the current column, row, and subgrid.
            subGrid[r / 3][c / 3][sudoku[r][c]] = true;
            row[r][sudoku[r][c]] = true;
            col[c][sudoku[r][c]] = true;
        }
    }
    return true;
}

// Function to try all the possible ways to solve the sudoku.
bool bruteForce(vector<vector<int> > &sudoku, int i, int j)
{
    if (j == 9)
    {
        if (i == 8)
        {
            if (isSudokuValid(sudoku))
            {
                return true;
            }
            return false;
        }

        j = 0;
        i++;
    }

    if (sudoku[i][j] != 0)
    {
        return bruteForce(sudoku, i, j + 1);
    }

    // Try all the values possible.
    for (int put = 1; put <= 9; put++)
    {
        sudoku[i][j] = put;

        if (bruteForce(sudoku, i, j + 1))
        {
            return true;
        }

        sudoku[i][j] = 0;
    }
    return false;
}

void solveSudoku(vector<vector<int> > &sudoku)
{
    bruteForce(sudoku, 0, 0);
}

void printSudoku(const vector<vector<int> > &sudoku)
{
    for (const vector<int> &row : sudoku)
    {
        for (const int &cell : row)
        {
            cout << cell << " ";
        }
        cout << "\n";
    }
}

int main()
{
    vector<vector<int> > sudoku = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Initial Sudoku:\n";
    printSudoku(sudoku);

    solveSudoku(sudoku);

    cout << "\nSolved Sudoku:\n";
    printSudoku(sudoku);

    return 0;
}
