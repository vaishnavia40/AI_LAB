#include <bits/stdc++.h>
using namespace std;

// Typedef for pair<int, int> to simplify notation
typedef pair<int, int> p;

// Function to print the path from the initial state to the solution state
void printPath(map<p, p> mp, p u)
{
    // Base case: if the initial state is reached, print it
    if (u.first == 0 && u.second == 0)
    {
        cout << 0 << " " << 0 << endl;
        return;
    }
    // Recursively print the path from the parent state
    printPath(mp, mp[u]);
    // Print the current state
    cout << u.first << " " << u.second << endl;
}

// Function to solve the water jug problem using BFS
void BFSSolution(int x, int y, int target)
{
    // Map to keep track of visited states
    map<p, int> m;
    // Flag to indicate if a solution is found
    bool isSolvable = false;
    // Map to store the parent of each state for path reconstruction
    map<p, p> mp;
    // Queue for BFS
    queue<p> q;
    // Push the initial state (0, 0) into the queue
    q.push(make_pair(0, 0));
    
    while (!q.empty())
    {
        // Get the front state from the queue
        auto u = q.front();
        q.pop();
        
        // Skip this state if it has already been visited
        if (m[u] == 1)
            continue;

        // Skip this state if it is out of bounds
        if ((u.first > x || u.second > y || u.first < 0 || u.second < 0))
            continue;
        
        // Mark this state as visited
        m[{u.first, u.second}] = 1;

        // Check if the current state meets the target condition
        if (u.first == target || u.second == target)
        {
            isSolvable = true;

            // Print the path from the initial state to the solution state
            printPath(mp, u);

            // If the solution state has the target amount in one jug, empty the other jug
            if (u.first == target)
            {
                if (u.second != 0)
                    cout << u.first << " " << 0 << endl;
            }
            else
            {
                if (u.first != 0)
                    cout << 0 << " " << u.second << endl;
            }
            return;
        }

        // Try to fill Jug2
        if (m[{u.first, y}] != 1)
        {
            q.push({u.first, y});
            mp[{u.first, y}] = u;
        }

        // Try to fill Jug1
        if (m[{x, u.second}] != 1)
        {
            q.push({x, u.second});
            mp[{x, u.second}] = u;
        }

        // Try to pour water from Jug1 to Jug2 until Jug2 is full or Jug1 is empty
        int d = y - u.second;
        if (u.first >= d)
        {
            int c = u.first - d;
            if (m[{c, y}] != 1)
            {
                q.push({c, y});
                mp[{c, y}] = u;
            }
        }
        else
        {
            int c = u.first + u.second;
            if (m[{0, c}] != 1)
            {
                q.push({0, c});
                mp[{0, c}] = u;
            }
        }

        // Try to pour water from Jug2 to Jug1 until Jug1 is full or Jug2 is empty
        d = x - u.first;
        if (u.second >= d)
        {
            int c = u.second - d;
            if (m[{x, c}] != 1)
            {
                q.push({x, c});
                mp[{x, c}] = u;
            }
        }
        else
        {
            int c = u.first + u.second;
            if (m[{c, 0}] != 1)
            {
                q.push({c, 0});
                mp[{c, 0}] = u;
            }
        }

        // Try to empty Jug2
        if (m[{u.first, 0}] != 1)
        {
            q.push({u.first, 0});
            mp[{u.first, 0}] = u;
        }

        // Try to empty Jug1
        if (m[{0, u.second}] != 1)
        {
            q.push({0, u.second});
            mp[{0, u.second}] = u;
        }
    }
    // If no solution is found, print "Solution not possible"
    if (!isSolvable)
        cout << "Solution not possible";
}

int main()
{
    int Jug1 = 4, Jug2 = 3, target = 2;
    cout << "Path from initial state to solution state ::\n";
    // Call the BFS solution to solve the problem
    BFSSolution(Jug1, Jug2, target);
    return 0;
}

    //               (0, 0)
    //              /      \
    //         (4, 0)      (0, 3)
    //          /   \        /   \
    //     (4, 3)  (1, 3)  (3, 0)
    //      |        |       |   |
    //  (0, 3)   (1, 0)   (3, 3) |
    //           /               |
    //       (0, 1)              |
    //           |               |
    //         ...               |
    //                           |
    //                       (2, 3)
    //                       /    \
    //                  (2, 0)    ...
