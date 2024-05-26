#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm> // Include for std::reverse

using namespace std;

// Node structure to represent a node in the graph
struct Node {
    int value;      // Identifier of the node
    int heuristic;  // Heuristic value of the node

    // Constructor to initialize a Node object with value and heuristic
    Node(int v, int h) : value(v), heuristic(h) {}

    // Overloaded '>' operator to compare nodes based on their heuristic values
    bool operator>(const Node& other) const {
        return heuristic > other.heuristic;
    }
};

// Define the graph using an unordered_map
unordered_map<int, vector<int>> graph = {
    {0, {1, 2, 3}},
    {1, {0, 4}},
    {2, {0, 4, 5}},
    {3, {0, 5}},
    {4, {1, 2, 6}},
    {5, {2, 3, 6}},
    {6, {4, 5, 7}},
    {7, {}}
};

// Function to calculate Manhattan heuristic values for each node based on the goal state
unordered_map<int, int> calculateManhattanHeuristics(int goal) {
    unordered_map<int, int> heuristicValues;

    // Define node coordinates and calculate Manhattan distances
    unordered_map<int, pair<int, int>> nodeCoordinates = {
        {0, {0, 0}},
        {1, {5, 8}},
        {2, {8, 5}},
        {3, {12, 2}},
        {4, {3, 3}},
        {5, {7, 7}},
        {6, {11, 11}},
        {7, {15, 15}}
    };

    pair<int, int> goalCoordinates = nodeCoordinates[goal];

    for (auto& entry : nodeCoordinates) {
        int node = entry.first;
        pair<int, int> coordinates = entry.second;
        int distance = abs(coordinates.first - goalCoordinates.first) + abs(coordinates.second - goalCoordinates.second);
        heuristicValues[node] = distance;
    }

    return heuristicValues;
}

// Function to reconstruct the shortest path from the parent map
vector<int> reconstructPath(const unordered_map<int, int>& parent, int goal) {
    vector<int> path;
    while (parent.find(goal) != parent.end()) {
        path.push_back(goal);
        goal = parent.at(goal);
    }
    path.push_back(goal);
    reverse(path.begin(), path.end()); // Using std::reverse
    return path;
}

// Function to perform best-first search algorithm
vector<int> bestFirstSearch(int start, int goal, const unordered_map<int, int>& heuristicValues) {
    priority_queue<Node, vector<Node>, greater<Node>> pq; // Min-heap priority queue
    unordered_map<int, int> parent; // Parent map to reconstruct the path
    unordered_set<int> visited; // Set to keep track of visited nodes

    // Push the start node into the priority queue
    pq.push(Node(start, heuristicValues.at(start)));

    while (!pq.empty()) {
        Node current = pq.top(); // Get the node with the lowest heuristic value
        pq.pop();
        int currentValue = current.value;

        // Check if the goal state is reached
        if (currentValue == goal) {
            return reconstructPath(parent, currentValue);
        }

        visited.insert(currentValue); // Mark the current node as visited

        // Explore neighbors of the current node
        for (int neighbor : graph[currentValue]) {
            if (visited.find(neighbor) == visited.end()) {
                parent[neighbor] = currentValue; // Update parent map
                pq.push(Node(neighbor, heuristicValues.at(neighbor))); // Push neighbor into priority queue
            }
        }
    }

    return {}; // If no path is found, return an empty vector
}

// Main function
int main() {
    int startState, goalState;
    cout << "Enter the start state: ";
    cin >> startState;
    cout << "Enter the goal state: ";
    cin >> goalState;

    // Calculate Manhattan heuristic values for each node
    auto heuristicValues = calculateManhattanHeuristics(goalState);

    // Perform best-first search to find the shortest path
    auto path = bestFirstSearch(startState, goalState, heuristicValues);

    // Print heuristic values for each node
    cout << "Heuristic Values: " << endl;
    for (const auto& entry : heuristicValues) {
        cout << "Node " << entry.first << ": " << entry.second << endl;
    }

    // Print the shortest path
    cout << "Path: ";
    for (int node : path) {
        cout << node << " -> ";
    }
    cout << "Reached" << endl;

    return 0;
}

/*The evaluation function for best-first search is f(n) = h(n).This search algorithm does not involve past knowledge.
Best-first search is not complete.Best-first search is not optimal as the path found may not be optimal.Its time complexity is O(bm) and space complexity can be polynomial.

where b is the branching and m is the maximum depth of the search tree */