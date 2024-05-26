#include <iostream>
#include <set>
#include <vector>
using namespace std;

// Representation of a state of the puzzle
struct State {
    vector<vector<int>> board;
    int zeroRow, zeroCol;
    static const vector<vector<int>> goal;

    // Constructor to initialize the state
    State(vector<vector<int>>& b, int zRow, int zCol) : board(b), zeroRow(zRow), zeroCol(zCol) {}

    // Function to check if the state is the goal state
    bool isGoal() const {
        return board == goal;
    }

    // Function to generate successor states
    vector<State> successors() const {
        // Define the movements in terms of row and column changes: Up, Down, Left, Right
        static const int dr[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
        static const int dc[] = {0, 0, -1, 1};

        // Initialize a vector to store successor states
        vector<State> succ;

        // Iterate over all possible movements
        for (int d = 0; d < 4; ++d) {
            // Calculate the new position of the empty cell after the movement
            int newRow = zeroRow + dr[d];
            int newCol = zeroCol + dc[d];

            // Check if the new position is within the bounds of the puzzle board
            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
                // Create a new board configuration by swapping the empty cell with the neighboring cell
                vector<vector<int>> newBoard = board;
                swap(newBoard[zeroRow][zeroCol], newBoard[newRow][newCol]);

                // Create a new successor state using the updated board configuration and position of the empty cell
                succ.emplace_back(newBoard, newRow, newCol);
            }
        }

        // Return the vector of successor states
        return succ;
    }
};

const vector<vector<int>> State::goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

// Depth-Limited Search function
bool dls(State currentState, set<vector<vector<int>>>& visited, int depth, int limit) {
    // Check if the current state is the goal state
    if (currentState.isGoal()) {
        // If the goal state is reached, print it and return true
        cout << "Goal state reached!" << endl;
        cout << "Goal state:" << endl;
        // Print the goal state's board configuration
        for (const auto& row : currentState.board) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
        return true; // Indicate that the goal state is found
    }

    // If the depth limit is reached, return false
    if (depth >= limit) {
        return false;
    }

    // Mark the current state as visited
    visited.insert(currentState.board);

    // Iterate over successor states of the current state
    for (const State& nextState : currentState.successors()) {
        // Check if the successor state has not been visited before
        if (visited.find(nextState.board) == visited.end()) {
            // Print information about the successor state and its depth level
            cout << "Depth Level: " << depth << endl;
            cout << "Next state:" << endl;
            // Print the successor state's board configuration
            for (const auto& row : nextState.board) {
                for (int val : row) {
                    cout << val << " ";
                }
                cout << endl;
            }
            cout << "-----------------" << endl;
            // Recursively call dls on the successor state with an increased depth level
            if (dls(nextState, visited, depth + 1, limit))
                return true; // If the goal state is found, return true to propagate the success
        }
    }

    return false; // Return false if no solution is found from the current state
}

int main() {
    vector<vector<int>> initialBoard = {{1, 2, 3}, {4, 0, 6}, {7, 5, 8}}; // Initial state of the puzzle
    int zeroRow = 1, zeroCol = 1; // Position of the empty cell (zero)
    State initialState(initialBoard, zeroRow, zeroCol);
    cout << "Initial state:" << endl;
    for (const auto& row : initialBoard) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "-----------------" << endl;

    cout << "Goal state:" << endl;
    for (const auto& row : State::goal) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "-----------------" << endl;

    set<vector<vector<int>>> visited;
    int depthLimit = 4;
    if (!dls(initialState, visited, 0, depthLimit)) // Call the dls function with initial state, passing the set of visited states and starting depth level 0
        cout << "No solution found within depth limit!" << endl; // Print "No solution found!" if dls function returns false

    return 0;
}
