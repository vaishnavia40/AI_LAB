#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm> // For std::find and std::reverse

using namespace std;

class Node {
public:
    string name; // Name of the node
    int h; // Heuristic value for the node
    int fScore; // Total cost of the path up to this node
    
    unordered_map<Node*, int> neighbours; // Neighbouring nodes and their distances
    
    // Constructor to initialize a node with its name and heuristic value
    Node(string name, int h) : name(name), h(h), fScore(0) {}
    
    // Method to add a neighbouring node with its distance
    void addNeighbour(Node* neighbour, int distance) {
        if (this == neighbour) // Ensure not adding itself as a neighbour
            return;
        neighbours[neighbour] = distance; // Add the neighbour and its distance
    }

    // Method to get the distance to a neighbouring node
    int Distance(Node* neighbour) {
        return neighbours[neighbour];
    }
};

class CompareFScore {
public:
    // Comparator class to compare nodes based on their fScore
    bool operator()(const Node* a, const Node* b) {
        return a->fScore > b->fScore; // Compare fScores in ascending order
    }
};

class AStar {
public:
    // Function to perform A* search algorithm
    static vector<Node*> aStarSearch(Node* start, Node* goal);
    
    // Function to reconstruct the final path from start to goal node
    static vector<Node*> finalPath(unordered_map<Node*, Node*>& parent, Node* current, unordered_map<Node*, int>& gScore,
            unordered_map<Node*, int>& fScore);
};

// A* search algorithm implementation
vector<Node*> AStar::aStarSearch(Node* start, Node* goal) {
    unordered_map<Node*, Node*> parent; // Map to store parent nodes for each node
    unordered_map<Node*, int> gScore; // Map to store gScores for each node
    unordered_map<Node*, int> fScore; // Map to store fScores for each node
    vector<Node*> openList; // Vector to track nodes in the open list
    vector<Node*> closedList; // Vector to track nodes in the closed list

    gScore[start] = 0; // Initialize gScore of start node to 0
    fScore[start] = start->h; // Initialize fScore of start node to its heuristic value
    start->fScore = start->h; // Initialize fScore of start node to its heuristic value
    openList.push_back(start); // Add start node to the open list

    while (!openList.empty()) {
        // Find the node with the lowest fScore in the open list
        Node* current = openList.front();
        int minFScore = fScore[current];
        for (Node* node : openList) {
            if (fScore[node] < minFScore) {
                current = node;
                minFScore = fScore[node];
            }
        }
        openList.erase(remove(openList.begin(), openList.end(), current), openList.end());

        if (current == goal) {
            return finalPath(parent, current, gScore, fScore); // If goal node reached, return the final path
        }

        closedList.push_back(current); // Add current node to the closed list

        for (auto& neighbour : current->neighbours) {
            Node* neighbourNode = neighbour.first;
            int distance = neighbour.second;

            // Ignore the neighbour which is already evaluated
            if (find(closedList.begin(), closedList.end(), neighbourNode) != closedList.end()) {
                continue;
            }

            int tentativeGScore = gScore[current] + current->Distance(neighbourNode);

            if (find(openList.begin(), openList.end(), neighbourNode) == openList.end() || tentativeGScore < gScore[neighbourNode]) {
                parent[neighbourNode] = current; // Update parent of neighbour node
                gScore[neighbourNode] = tentativeGScore; // Update gScore of neighbour node
                fScore[neighbourNode] = gScore[neighbourNode] + neighbourNode->h; // Update fScore of neighbour node
                neighbourNode->fScore = fScore[neighbourNode]; // Update fScore property of neighbour node

                if (find(openList.begin(), openList.end(), neighbourNode) == openList.end()) {
                    openList.push_back(neighbourNode); // Add neighbour node to the open list if not already present
                }
            }
        }
    }
    return vector<Node*>(); // Return empty vector if no path found
}

// Function to reconstruct the final path from start to goal node
vector<Node*> AStar::finalPath(unordered_map<Node*, Node*>& parent, Node* current, unordered_map<Node*, int>& gScore,
        unordered_map<Node*, int>& fScore) {
    vector<Node*> path;
    while (current != nullptr) {
        path.push_back(current); // Add current node to the path
        current = parent[current]; // Move to the parent of current node
    }
    reverse(path.begin(), path.end()); // Reverse the path to get it from start to goal
    return path;
}

int main() {
    // Create nodes with their names and heuristic values
    Node* A = new Node("A", 14);
    Node* B = new Node("B", 12);
    Node* C = new Node("C", 11);
    Node* D = new Node("D", 6);
    Node* E = new Node("E", 4);
    Node* F = new Node("F", 11);
    Node* Z = new Node("Z", 0);
    
    // Add neighbours for each node with their distances
    A->addNeighbour(B, 4);
    A->addNeighbour(C, 3);
    B->addNeighbour(E, 12);
    B->addNeighbour(F, 5);
    C->addNeighbour(D, 7);
    C->addNeighbour(E, 11);
    D->addNeighbour(E, 2);
    F->addNeighbour(Z, 16);
    E->addNeighbour(Z, 5);

    // Perform A* search algorithm from start node A to goal node Z
    vector<Node*> path = AStar::aStarSearch(A, Z);

    // Print the final path from start to goal node
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->name; // Print node name
        if (i < path.size() - 1) {
            cout << "->"; // Print arrow between nodes
        }
    }
    return 0;
}

/*A*search is a searching algorithm used to find the shortest path which calculates
 the cost of all its neighboring nodes and selects the minimum cost node.
 It defines the evaluation function f(n) = g(n) + h(n) where, h(n) is heuristics function and 
 g(n) is the past knowledge acquired while searching.
 
 The evaluation function for A* search is f(n) = h(n) + g(n)
This search algorithm involves past knowledge.A* search is complete.A* search is optimal as the path found is always optimal.
its time complexity is O(bm) and space complexity is also O(bm).
where b is the branching and m is the maximum depth of the search tree*/