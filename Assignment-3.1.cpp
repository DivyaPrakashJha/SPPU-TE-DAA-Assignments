// Problem Statement

// Write a recursive program to find the solution of placing n queens on the chessboard 
// so that no two queens attack each other using Backtracking

#include<bits/stdc++.h>

using namespace std;

void printConfig(vector<vector<int>>board){
    int n = board.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (board[i][j]) cout<<"Q ";
            else cout<<". ";
        }
        cout<<endl;
    }
}

bool isSafe(int col, int row, vector<int>&r, vector<int>&uld, vector<int>&lld){
    int n = r.size();

    if (r[row]) return false;
    if (uld[n+row-col]) return false;
    if (lld[row+col]) return false;

    return true;
}

bool solveNQueens(vector<vector<int>>&board, int col, vector<int>&r, vector<int>&uld, vector<int>&lld){
    int n = board.size();

    if (col == n){
        return true;
    }

    for(int row = 0; row < n; row++){
        if (isSafe(col, row, r, uld, lld)){

            board[row][col] = r[row] = uld[n+row-col] = lld[row+col] = 1;
            
            if (solveNQueens(board, col+1, r, uld, lld)) return true;

            board[row][col] = r[row] = uld[abs(n+row-col)] = lld[row+col] = 0;
        }
    }

    return false;
}

int main(){
    int n;
    cin>>n;

    vector<vector<int>>board(n, vector<int>(n, 0));

    // // Using hashing to implement isSafe function
    vector<int>r(n, 0), uld(2*n, 0), lld(2*n, 0); // row, upperLeftDiagonal, lowerLeftDiagonal

    if (!solveNQueens(board, 0, r, uld, lld)) cout<<"No solution exists!!\n";
    else printConfig(board);
}