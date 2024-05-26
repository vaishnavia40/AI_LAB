#include <bits/stdc++.h>
using namespace std;

// Function to find the position of the zero (empty space) in the puzzle
void findZero(vector<vector<int>> board, int &x, int &y)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                x = i;
                y = j;
                return;
            }
        }
    }
}

// Function to print the current state of the board
void printBoard(vector<vector<int>> board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if the current board state is the goal state
bool isGoalState(vector<vector<int>> &board, vector<vector<int>> &goal)
{
    return board == goal;
}

// Function to calculate the number of misplaced tiles (heuristic)
int findMisplacedTiles(vector<vector<int>> &board, vector<vector<int>> &goal)
{
    int count = 0;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] != goal[i][j])
                count++;
        }
    }
    return count;
}

// A* algorithm implementation to solve the 8-puzzle problem
void aStar(vector<vector<int>> &board, vector<vector<int>> &goal, int depth, int x, int y)
{
    // Priority queue to store the boards with their cost (g + h)
    priority_queue<pair<int, vector<vector<int>>>, vector<pair<int, vector<vector<int>>>>,
                   greater<pair<int, vector<vector<int>>>>>
        pq;    // Min heap

    int g = depth; // Cost from start to the current node
    int h = findMisplacedTiles(board, goal); // Heuristic cost to reach the goal
    pq.push({(g + h), board});

    while (!pq.empty())
    {
        vector<vector<int>> curr = pq.top().second;
        pq.pop();
        printBoard(curr); // Print current board state

        int x, y;
        findZero(curr, x, y); // Find position of zero (empty space)

        if (isGoalState(curr, goal))
        {
            cout << "Goal State Reached" << endl;
            return;
        }

        // Possible movements (right, left, up, down)
        int dx[] = {0, 0, -1, 1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];

            // Check if the new position is within bounds
            if (newX >= 0 && newX < curr.size() && newY >= 0 && newY < curr.size())
            {
                swap(curr[x][y], curr[newX][newY]); // Swap the zero with the new position
                g = depth + 1; // Increment the depth (cost)
                h = findMisplacedTiles(curr, goal); // Recalculate the heuristic cost
                pq.push({(g + h), curr}); // Push the new board state into the priority queue
                swap(curr[x][y], curr[newX][newY]); // Backtrack to the original state
            }
        }
    }

    cout << "NO SOLUTION FOUND" << endl; // If no solution is found
    return;
}

int main()
{
    // Initial state of the board
    vector<vector<int>> initial = {
        {2, 8, 3},
        {1, 6, 4},
        {7, 0, 5}};

    // Goal state of the board
    vector<vector<int>> goal = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}};

    int x, y;
    findZero(initial, x, y); // Find the position of the zero in the initial state

    aStar(initial, goal, 0, x, y); // Call the A* algorithm to solve the puzzle

    return 0;
}
