#include <iostream>
#include <vector>
using namespace std;

// Function to print the board configuration
void printSolution(vector<vector<char>> board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

// Function to check if it's safe to place a queen at board[row][col]
bool isSafe(int row, int col, vector<vector<char>> board, int n) {
    int i = row;
    int j = col;
    
    // Check the row on the left side
    // means us row me koi queen placed nahi honi chahiye:)
    while (j >= 0) {
        if (board[i][j] == 'Q') {
            return false;
        }
        j--;
    }

    // Check the upper diagonal on the left side
    i = row;
    j = col;
    while (i >= 0 && j >= 0) {
        if (board[i][j] == 'Q') {
            return false;
        }
        i--;
        j--;
    }

    // Check the lower diagonal on the left side
    i = row;
    j = col;
    while (i < n && j >= 0) {
        if (board[i][j] == 'Q') {
            return false;
        }
        i++;
        j--;
    }

    // If no queens threaten the position, it is safe
    return true;
}

// Function to solve the N-Queens problem using backtracking
void solve(vector<vector<char>> board, int col, int n) {
    // Base case: If all queens are placed
    if (col >= n) {
        printSolution(board, n); // Print the solution
        return;
    }

    // Consider this column and try placing this queen in all rows one by one
    for (int row = 0; row < n; row++) {
        // Check if the queen can be placed on board[row][col]
        if (isSafe(row, col, board, n)) {
            board[row][col] = 'Q'; // Place the queen

            // Recur to place the rest of the queens
            solve(board, col + 1, n);

            // If placing the queen in board[row][col] doesn't lead to a solution,
            // then backtrack: remove the queen from board[row][col]
            board[row][col] = '_';
        }
    }
}

int main() {
    int n = 5; // Set the size of the board
    vector<vector<char>> board(n, vector<char>(n, '_')); // Initialize the board with '_'
    int col = 0; // Start from the first column
    solve(board, col, n); // Solve the N-Queens problem
    return 0;
}
