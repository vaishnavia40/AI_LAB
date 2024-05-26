#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm> // For std::find and std::reverse

using namespace std;

class Node {
public:
    string name;
    int h;
    int fScore; // Add fScore here
    
    unordered_map<Node*, int> neighbours;
    
    Node(string name, int h) : name(name), h(h), fScore(0) {}
    
    void addNeighbour(Node* neighbour, int distance) {
        if (this == neighbour)
            return;
        neighbours[neighbour] = distance;
    }

    int Distance(Node* neighbour) {
        return neighbours[neighbour];
    }
};

class CompareFScore {
public:
    bool operator()(const Node* a, const Node* b) {
        return a->fScore > b->fScore;
    }
};

class AStar {
public:
    static vector<Node*> aStarSearch(Node* start, Node* goal);
    static vector<Node*> finalPath(unordered_map<Node*, Node*>& parent, Node* current, unordered_map<Node*, int>& gScore,
            unordered_map<Node*, int>& fScore);
};

vector<Node*> AStar::aStarSearch(Node* start, Node* goal) {
    unordered_map<Node*, Node*> parent;
    unordered_map<Node*, int> gScore;
    unordered_map<Node*, int> fScore;
    vector<Node*> openList; // Use a separate vector to track nodes in the open list
    vector<Node*> closedList;

    gScore[start] = 0;
    fScore[start] = start->h;
    start->fScore = start->h;
    openList.push_back(start);

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
            return finalPath(parent, current, gScore, fScore);
        }

        closedList.push_back(current);

        for (auto& neighbour : current->neighbours) {
            Node* neighbourNode = neighbour.first;
            int distance = neighbour.second;

            if (find(closedList.begin(), closedList.end(), neighbourNode) != closedList.end()) {
                continue; // Ignore the neighbour which is already evaluated
            }

            int tentativeGScore = gScore[current] + current->Distance(neighbourNode);

            if (find(openList.begin(), openList.end(), neighbourNode) == openList.end() || tentativeGScore < gScore[neighbourNode]) {
                parent[neighbourNode] = current;
                gScore[neighbourNode] = tentativeGScore;
                fScore[neighbourNode] = gScore[neighbourNode] + neighbourNode->h;
                neighbourNode->fScore = fScore[neighbourNode];

                if (find(openList.begin(), openList.end(), neighbourNode) == openList.end()) {
                    openList.push_back(neighbourNode);
                }
            }
        }
    }
    return vector<Node*>();
}

vector<Node*> AStar::finalPath(unordered_map<Node*, Node*>& parent, Node* current, unordered_map<Node*, int>& gScore,
        unordered_map<Node*, int>& fScore) {
    vector<Node*> path;
    while (current != nullptr) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    Node* A = new Node("A", 14);
    Node* B = new Node("B", 12);
    Node* C = new Node("C", 11);
    Node* D = new Node("D", 6);
    Node* E = new Node("E", 4);
    Node* F = new Node("F", 11);
    Node* Z = new Node("Z", 0);
    A->addNeighbour(B, 4);
    A->addNeighbour(C, 3);
    B->addNeighbour(E, 12);
    B->addNeighbour(F, 5);
    C->addNeighbour(D, 7);
    C->addNeighbour(E, 11);
    D->addNeighbour(E, 2);
    F->addNeighbour(Z, 16);
    E->addNeighbour(Z, 5);

    vector<Node*> path = AStar::aStarSearch(A, Z);
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->name;
        if (i < path.size() - 1) {
            cout << "->";
        }
    }
    return 0;
}