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

// Recursive DFS function to solve the water jug problem
bool DFS(int x, int y, int target, map<p, int> &m, map<p, p> &mp, p u)
{
    // If the current state has already been visited, return false
    if (m[u] == 1)
        return false;

    // If the current state is out of bounds, return false
    if ((u.first > x || u.second > y || u.first < 0 || u.second < 0))
        return false;

    // Mark the current state as visited
    m[{u.first, u.second}] = 1;

    // Check if the current state meets the target condition
    if (u.first == target || u.second == target)
    {
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
        return true;
    }

    // Try to fill Jug2
    if (DFS(x, y, target, m, mp, {u.first, y}))
    {
        mp[{u.first, y}] = u;
        return true;
    }

    // Try to fill Jug1
    if (DFS(x, y, target, m, mp, {x, u.second}))
    {
        mp[{x, u.second}] = u;
        return true;
    }

    // Try to pour water from Jug1 to Jug2 until Jug2 is full or Jug1 is empty
    int d = y - u.second;
    if (u.first >= d)
    {
        int c = u.first - d;
        if (DFS(x, y, target, m, mp, {c, y}))
        {
            mp[{c, y}] = u;
            return true;
        }
    }
    else
    {
        int c = u.first + u.second;
        if (DFS(x, y, target, m, mp, {0, c}))
        {
            mp[{0, c}] = u;
            return true;
        }
    }

    // Try to pour water from Jug2 to Jug1 until Jug1 is full or Jug2 is empty
    d = x - u.first;
    if (u.second >= d)
    {
        int c = u.second - d;
        if (DFS(x, y, target, m, mp, {x, c}))
        {
            mp[{x, c}] = u;
            return true;
        }
    }
    else
    {
        int c = u.first + u.second;
        if (DFS(x, y, target, m, mp, {c, 0}))
        {
            mp[{c, 0}] = u;
            return true;
        }
    }

    // Try to empty Jug2
    if (DFS(x, y, target, m, mp, {u.first, 0}))
    {
        mp[{u.first, 0}] = u;
        return true;
    }

    // Try to empty Jug1
    if (DFS(x, y, target, m, mp, {0, u.second}))
    {
        mp[{0, u.second}] = u;
        return true;
    }

    // If none of the above moves lead to a solution, return false
    return false;
}

// Function to solve the water jug problem using DFS
void DFSSolution(int x, int y, int target)
{
    // Map to keep track of visited states
    map<p, int> m;
    // Flag to indicate if a solution is found
    bool isSolvable = false;
    // Map to store the parent of each state for path reconstruction
    map<p, p> mp;
    // Initial state (0, 0)
    p start = {0, 0};
    // Call DFS starting from the initial state
    if (DFS(x, y, target, m, mp, start))
        isSolvable = true;

    // If no solution is found, print "Solution not possible"
    if (!isSolvable)
        cout << "Solution not possible";
}

int main()
{
    // Define the capacities of the jugs and the target amount
    int Jug1 = 4, Jug2 = 3, target = 2;
    cout << "Path from initial state to solution state:\n";
    // Call the DFS solution to solve the problem
    DFSSolution(Jug1, Jug2, target);
    return 0;
}

        //               (0,0)
        //               / | \
        //            (0,3) (4,0) ...
        //            / | \    / | \
        //       (4,3)(3,0)(0,0)(4,3)(1,3)(0,0)
        //       / | \   ...   / | \ ...
        //  ... (3,3)(4,3) ... (4,2)(1,3) ...
