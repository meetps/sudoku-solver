#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

#define UNASSIGNED 0
 
#define N 9
 
using namespace std;

bool FindUnassignedLocation(vector< vector<int> > &board, int &row, int &col);
 
bool isSafe(vector< vector<int> > &board, int row, int col, int num);
 
bool SolveSudoku(vector<vector<int> > &board)
{
    int row, col; 
    if (!FindUnassignedLocation(board, row, col))
       return true;
 
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(board, row, col, num))
        {
            board[row][col] = num;
 
            if (SolveSudoku(board))
                return true;
 
            board[row][col] = UNASSIGNED;
        }
    }
    return false; 
  }
 
bool FindUnassignedLocation(vector<vector<int> > &board, int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (board[row][col] == UNASSIGNED)
                return true;
    return false;
}
 
bool UsedInRow(vector<vector<int> > &board, int row, int num)
{
    for (int col = 0; col < N; col++)
        if (board[row][col] == num)
            return true;
    return false;
}
 
bool UsedInCol(vector<vector<int> > &board, int col, int num)
{
    for (int row = 0; row < N; row++)
        if (board[row][col] == num)
            return true;
    return false;
}
 
bool UsedInBox(vector<vector<int> > &board, int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (board[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}
 
bool isSafe(vector<vector<int> > &board, int row, int col, int num)
{
    return !UsedInRow(board, row, num) &&
           !UsedInCol(board, col, num) &&
           !UsedInBox(board, row - row%3 , col - col%3, num);
}
 
void printGrid(vector<vector<int> > &board)
{ 
    cout << "______________________" << '\n';
    for (int row = 0; row < N; row++)
    {
       cout << '|';
       for (int col = 0; col < N; col++)
            {
              cout << board[row][col] << " ";
              if(col%3 == 2) {cout << '|';}
            }
      if(row%3 == 2){cout << '\n' << "______________________" << '\n';}
      else cout << '\n';
    }
}
 
int main()
{
  vector<vector<int> > board;
  string s;
  for(int i =0; i < 9; i++)
  {
    cin >> s;
    vector<int> row;
    for(int j = 0; j < 9; j++)
      {
        row.push_back(s[2*j] - 48);  
      }
    board.push_back(row);
  }
    
  if (SolveSudoku(board) == true)
      printGrid(board);
  else
    printf("No solution exists");
  return 0;
}
