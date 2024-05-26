#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm> // Include for std::reverse

using namespace std;

struct Node {
    int value;
    int heuristic;

    Node(int v, int h) : value(v), heuristic(h) {}

    bool operator>(const Node& other) const {
        return heuristic > other.heuristic;
    }
};

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

unordered_map<int, int> calculateManhattanHeuristics(int goal) {
    unordered_map<int, int> heuristicValues;

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

vector<int> bestFirstSearch(int start, int goal, const unordered_map<int, int>& heuristicValues) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<int, int> parent;
    unordered_set<int> visited;

    pq.push(Node(start, heuristicValues.at(start)));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int currentValue = current.value;

        if (currentValue == goal) {
            return reconstructPath(parent, currentValue);
        }

        visited.insert(currentValue);

        for (int neighbor : graph[currentValue]) {
            if (visited.find(neighbor) == visited.end()) {
                parent[neighbor] = currentValue;
                pq.push(Node(neighbor, heuristicValues.at(neighbor)));
            }
        }
    }

    return {};
}

int main() {
    int startState, goalState;
    cout << "Enter the start state: ";
    cin >> startState;
    cout << "Enter the goal state: ";
    cin >> goalState;

    auto heuristicValues = calculateManhattanHeuristics(goalState);
    auto path = bestFirstSearch(startState, goalState, heuristicValues);

    cout << "Heuristic Values: " << endl;
    for (const auto& entry : heuristicValues) {
        cout << "Node " << entry.first << ": " << entry.second << endl;
    }

    cout << "Path: ";
    for (int node : path) {
        cout << node << " -> ";
    }
    cout<<"Reached";
    cout << endl;

    return 0;
}
