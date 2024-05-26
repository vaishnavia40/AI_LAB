#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
//using BFS
// Representation of a state of the puzzle
struct State {
    vector<vector<int>> board;
    int zeroRow, zeroCol;
    int depth; // Depth level of the state
    static const vector<vector<int>> goal;

    // Constructor to initialize the state
    State(vector<vector<int>>& b, int zRow, int zCol, int d) {
        board = b;
        zeroRow = zRow;
        zeroCol = zCol;
        depth = d;
    }
    // Function to check if the state is the goal state
    //here const after the funcion indicates that function does not modify the state of the object
    //on which it is called. It's a promise to the compiler that calling this function won't change the object's state.
    bool isGoal() const {
        return board == goal;
    }

    // Function to generate successor states
    vector<State> successors() const {
        static const int dr[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
        static const int dc[] = {0, 0, -1, 1};
        vector<State> succ;
        for (int d = 0; d < 4; ++d) {
            int newRow = zeroRow + dr[d];
            int newCol = zeroCol + dc[d];
            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
                vector<vector<int>> newBoard = board;
                swap(newBoard[zeroRow][zeroCol], newBoard[newRow][newCol]);
                succ.emplace_back(newBoard, newRow, newCol, depth + 1); // Increase depth level by 1 for successors
            }
        }
        return succ;
    }
};

//goal is a static const variable of struct and to access the static variable of struct/class we use :: operator
const vector<vector<int>> State::goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

// Function to perform Breadth First Search to solve the puzzle
void solvePuzzle(State initialState) {
    queue<State> q; // Queue to store states to be explored
    set<vector<vector<int>>> visited; // Set to store visited states (represented as boards)
    q.push(initialState); // Push the initial state onto the queue

    int stateNumber = 1; // To label each state

    // Main loop: Continue until the queue is empty (no more states to explore)
    while (!q.empty()) {
        // Get the current state from the front of the queue
        State currState = q.front();
        q.pop(); // Remove the current state from the queue

        // Generate successor states for the current state
        for (const State& nextState : currState.successors()) {
            // Check if the successor state has not been visited before
            if (visited.find(nextState.board) == visited.end()) {
                // Mark the successor state as visited
                visited.insert(nextState.board);

                // Print information about the successor state
                cout << "Next state " << stateNumber << " at depth " << nextState.depth << ":" << endl;
                for (const auto& row : nextState.board) {
                    for (int val : row) {
                        cout << val << " ";
                    }
                    cout << endl;
                }
                cout << "-----------------" << endl;

                // Check if the successor state is the goal state
                if (nextState.isGoal()) {
                    cout << "Goal state reached!" << endl;
                    cout << "Goal state:" << endl;
                    for (const auto& row : nextState.board) {
                        for (int val : row) {
                            cout << val << " ";
                        }
                        cout << endl;
                    }
                    return; // Exit the function if the goal state is reached
                }

                // If the successor state is not the goal state, push it onto the queue for further exploration
                q.push(nextState);

                // Increment the state number for labeling purposes
                stateNumber++;
            }
        }
    }

    // If the loop exits without finding the goal state, print a message indicating no solution was found
    cout << "No solution found!" << endl;
}

int main() {
    vector<vector<int>> initialBoard = {{1, 2, 3}, {0, 4, 6}, {7, 5, 8}}; // Initial state of the puzzle
    int zeroRow = 1, zeroCol = 0; // Position of the empty cell (zero)
    State initialState(initialBoard, zeroRow, zeroCol, 0); // Initial depth level is 0
    cout << "Initial state:" << endl;
    
    for (int i = 0; i < initialBoard.size(); ++i) {
        for (int j = 0; j < initialBoard[i].size(); ++j) {
            cout << initialBoard[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------" << endl;

    cout << "Goal state:" << endl;
    for (int i = 0; i < State::goal.size(); ++i) {
        for (int j = 0; j < State::goal[i].size(); ++j) {
            cout << State::goal[i][j] << " ";
        }
        cout << std::endl;
    }
    cout << "-----------------" << endl;

    solvePuzzle(initialState);
    return 0;
}
