#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define n 3
const bool SUCCESS = true;

class state {
public:
    int board[n][n], h; // Removed g, f; kept only h for heuristic value
    state* came_from;
    state () {
        h = 0; // Initialize h to 0
        came_from = NULL;
    }
    static int heuristic (state from, state to) {
        int ret = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (from.board[i][j] != to.board[i][j])
                    ret++;
        return ret;
    }
    bool operator == (state a) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (this->board[i][j] != a.board[i][j])
                    return false;
        return true;
    }
    void print () {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
        cout <<endl<< "h = " << h << endl << endl; // Print heuristic value (h) with an extra newline
    }
};

vector <state> output;
bool lowerH (state a, state b) {
    return a.h < b.h;
}

bool isinset (state a, vector <state> b) {
    for (int i = 0; i < b.size(); i++)
        if (a == b[i])
            return true;
    return false;
}

void addNeighbor (state current, state goal, int newi, int newj, int posi, int posj, vector <state>& openset, vector <state> closedset) {
    state newstate = current;
    swap (newstate.board[newi][newj], newstate.board[posi][posj]);
    if (!isinset(newstate, closedset) && !isinset(newstate, openset)) {
        newstate.h = state::heuristic(newstate, goal); // Calculate heuristic (h)
        state* temp = new state();
        *temp = current;
        newstate.came_from = temp;
        openset.push_back(newstate);
    }
}

void neighbors (state current, state goal, vector <state>& openset, vector <state>& closedset) {
    int i, j, posi ,posj;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (current.board[i][j] == 0) {
                posi = i;
                posj = j;
                break;
            }
    i = posi, j = posj;
    if (i - 1 >= 0)
        addNeighbor(current, goal, i - 1, j, posi, posj, openset, closedset);
    if (i + 1 < n)
        addNeighbor(current, goal, i + 1, j, posi, posj, openset, closedset);
    if (j + 1 < n)
        addNeighbor(current, goal, i, j + 1, posi, posj, openset, closedset);
    if (j - 1 >= 0)
        addNeighbor(current, goal, i, j - 1, posi, posj, openset, closedset);
}

bool reconstruct_path(state current, vector<state> &came_from) {
    state *temp = &current;
    while(temp != NULL) {
        came_from.push_back(*temp);
        temp = temp->came_from;
    }
    return SUCCESS;
}

bool best_first_search (state start, state goal) {
    vector <state> openset;
    vector <state> closedset;
    state current;
    start.h = state::heuristic(start, goal); // Calculate heuristic for start state
    openset.push_back(start);
    while (!openset.empty()) {
        sort(openset.begin(), openset.end(), lowerH);
        current = openset[0];
        if (current == goal)
            return reconstruct_path(current, output);
        openset.erase(openset.begin());
        closedset.push_back(current);
        neighbors(current, goal, openset, closedset);
    }
    return !SUCCESS;
}

int main () {
    state start, goal;

    // Initial state
    start.board[0][0] = 2; start.board[0][1] = 8; start.board[0][2] = 3;
    start.board[1][0] = 1; start.board[1][1] = 6; start.board[1][2] = 4;
    start.board[2][0] = 7; start.board[2][1] = 0; start.board[2][2] = 5;

    // Goal state
    goal.board[0][0] = 1; goal.board[0][1] = 2; goal.board[0][2] = 3;
    goal.board[1][0] = 8; goal.board[1][1] = 0; goal.board[1][2] = 4;
    goal.board[2][0] = 7; goal.board[2][1] = 6; goal.board[2][2] = 5;

    if (best_first_search(start, goal) == SUCCESS) {
        for (int i = output.size() - 1; i >= 0; i--)
            output[i].print();
        cout << "SUCCESS!! GOAL STATE REACHED." << endl;
    }
    else cout << "FAIL" << endl;
    return 0;
}