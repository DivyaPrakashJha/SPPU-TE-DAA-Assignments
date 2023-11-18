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

bool isSafe(vector<vector<int>>board, int col, int row){
    int n = board.size();

    // Row check
    for(int i = col; i >= 0; i--){
        if (board[row][i]) return false;
    }

    // Upper Left diagonal check
    for(int i = row, j = col; i >= 0 and j >= 0; i--, j--){
        if (board[i][j]) return false;
    }

    // Lower Left diagonal check
    for(int i = row, j = col; i < n and j >= 0; i++, j--){
        if (board[i][j]) return false;
    }

    return true;
}

bool solveNQueens(vector<vector<int>>&board, int col){
    int n = board.size();

    if (col == n){
        return true;
    }

    for(int row = 0; row < n; row++){
        if (isSafe(board, col, row)){
            board[row][col] = 1;
            
            if (solveNQueens(board, col+1)) return true;

            board[row][col] = 0;
        }
    }

    return false;
}

int main(){
    int n;
    cin>>n;

    vector<vector<int>>board(n, vector<int>(n, 0));

    if (!solveNQueens(board, 0)) cout<<"No solution exists!!\n";
    else printConfig(board);
}