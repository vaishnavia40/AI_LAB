#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

struct node {
    int data;
    vector<vector<node*>*> v;
    bool mark;
    bool solved;
};

int edge_cost = 0;

// Function to insert nodes into the tree
void insert(node* root) {
    cout << "Enter data of node :" << endl;
    cin >> root->data;

    cout << "Enter number of OR nodes for value " << root->data << " :" << endl;
    int or_no;
    cin >> or_no;

    for (int i = 0; i < or_no; i++) {
        vector<node*>* ans = new vector<node*>;
        cout << "Enter number of AND nodes for " << i + 1 << " or node for value " << root->data << " :" << endl;
        int and_no;
        cin >> and_no;

        for (int j = 0; j < and_no; j++) {
            node* n = new node;
            n->solved = false;
            n->mark = false;
            insert(n);
            (*ans).push_back(n);
        }
        root->v.push_back(ans);
    }
}

// Function to implement the AO* algorithm
void aostar(node* root) {
    vector<node*>* min_ans = new vector<node*>;
    (*min_ans).push_back(root);

    while (!root->solved) {
        node* next_node = root;
        stack<node*> st;

        while (next_node && next_node->mark) {
            if (next_node->v.size() == 0) {
                root->solved = true;
                return;
            }

            int cost = INT_MAX;
            st.push(next_node);

            for (unsigned int i = 0; i < next_node->v.size(); i++) {
                vector<node*>* ans = (next_node->v)[i];
                vector<node*> ans_v = *ans;
                int temp_cost = 0;

                for (unsigned int j = 0; j < ans_v.size(); j++) {
                    node* n = ans_v[j];
                    temp_cost += n->data + edge_cost;
                }

                if (temp_cost < cost) {
                    min_ans = ans;
                    cost = temp_cost;
                }
            }

            vector<node*> min_ans_v = *min_ans;
            next_node = NULL;

            for (unsigned int j = 0; j < min_ans_v.size(); j++) {
                if (!min_ans_v[j]->mark) {
                    next_node = min_ans_v[j];
                    break;
                }
            }
        }

        vector<node*> min_ans_v = *min_ans;

        for (unsigned int j = 0; j < min_ans_v.size(); j++) {
            node* n = min_ans_v[j];
            cout << "Exploring: " << n->data << endl;

            if (n->v.size() == 0) {
                n->mark = true;
            } else {
                int final_cost = INT_MAX;

                for (unsigned int i = 0; i < n->v.size(); i++) {
                    vector<node*>* ans = (n->v)[i];
                    vector<node*> ans_v = *ans;
                    int temp_cost = 0;

                    for (unsigned int j = 0; j < ans_v.size(); j++) {
                        node* n = ans_v[j];
                        temp_cost += n->data + edge_cost;
                    }

                    if (temp_cost < final_cost) {
                        final_cost = temp_cost;
                    }
                }

                n->data = final_cost;
                n->mark = true;
            }

            cout << "Marked: " << n->data << endl;
        }

        for (int i = 0; i < 20; i++) cout << "=";
        cout << endl;

        while (!st.empty()) {
            node* n = st.top();
            st.pop();
            int final_cost = INT_MAX;

            for (unsigned int i = 0; i < n->v.size(); i++) {
                vector<node*>* ans = (n->v)[i];
                vector<node*> ans_v = *ans;
                int temp_cost = 0;

                for (unsigned int j = 0; j < ans_v.size(); j++) {
                    node* child = ans_v[j];
                    temp_cost += child->data + edge_cost;
                }

                if (temp_cost < final_cost) {
                    min_ans = ans;
                    final_cost = temp_cost;
                }
            }

            n->data = final_cost;
        }
        next_node = root;
    }
}

// Function to print the tree structure
void print(node* root) {
    if (root) {
        cout << root->data << " ";
        vector<vector<node*>* > vec = root->v;

        for (unsigned int i = 0; i < root->v.size(); i++) {
            vector<node*>* ans = (root->v)[i];
            vector<node*> ans_v = *ans;

            for (unsigned int j = 0; j < ans_v.size(); j++) {
                node* n = ans_v[j];
                print(n);
            }
        }
    }
    return;
}

int main() {
    node* root = new node;
    root->solved = false;
    root->mark = false;
    insert(root);
    cout << endl;

    cout << "Enter the edge cost: " << endl;
    cin >> edge_cost;
    cout << endl;

    cout << "The tree is as follows :" << endl;
    print(root);
    cout << endl;

    aostar(root);
    cout << "The minimum cost is : " << root->data << endl;

    return 0;
}



// Enter data of node :
// 5
// Enter number of OR nodes for value 5 :
// 2
// Enter number of AND nodes for 1 or node for value 5 :
// 2
// Enter data of node :
// 3
// Enter number of OR nodes for value 3 :
// 1
// Enter number of AND nodes for 1 or node for value 3 :
// 1
// Enter data of node :
// 1
// Enter number of OR nodes for value 1 :
// 0
// Enter data of node :
// 2
// Enter number of OR nodes for value 2 :
// 0
// Enter number of AND nodes for 2 or node for value 5 :
// 1
// Enter data of node :
// 4
// Enter number of OR nodes for value 4 :
// 1
// Enter number of AND nodes for 1 or node for value 4 :
// 1
// Enter data of node :
// 1
// Enter number of OR nodes for value 1 :
// 0
// Enter the edge cost: 
// 1

//         5
//        / \
//       OR  OR
//      /  \  \
//     3    2  4
//    /       / 
//   1       1 

// ### Detailed Steps and Calculations:

// 1. **Root Node 5 Exploration:**
//  - Initial cost is 5.

// 2. **Exploring Node 3:**
//  - Child node 1 has no further children, so it's marked.
//  - The cost of node 3 is updated considering the edge cost.
//    - Cost of node 1 = 1
//    - Cost of node 3 = 1 (from child) + 1 (edge cost) = 2
//    - Final cost of node 3 is 3 (itself) + 2 (child path) = 5

// 3. **Exploring Node 4:**
//  - Child node 1 has no further children, so it's marked.
//  - The cost of node 4 is updated considering the edge cost.
//    - Cost of node 1 = 1
//    - Cost of node 4 = 1 (from child) + 1 (edge cost) = 2
//    - Final cost of node 4 is 4 (itself) + 2 (child path) = 6

// 4. **Exploring Node 2:**
//  - Node 2 has no children, so it remains as is.

// ### Backtracking:
// 1. **Back to Root Node 5:**
//  - Considering both OR branches:
//    - The minimal cost path from root to goal state will be through node 3:
//      - Path 1: 5 -> 3 -> 1: Cost = 5 (root) + 1 (edge) + 3 (child cost) = 9
//      - Path 2: 5 -> 4 -> 1: Cost = 5 (root) + 1 (edge) + 4 (child cost) = 10
//    - Thus, the minimum cost from root node 5 is via path 1 with total cost = 9

// ### Verifying Given Output:
// 1. **Initial State:**
/*The tree is as follows : 5 3 1 2 4 1

markdown
Copy code
2. **Explorations:**
Exploring: 5 -> Marked: 5
Exploring: 4 -> Marked: 2
Exploring: 1 -> Marked: 1
2 3
The minimum cost is: 3

vbnet
Copy code

### Validation:
- **Issue:** The provided output does not match the expected minimal cost path derived logically above. The cost calculations seem incorrect, particularly the backtracking costs.
- **Error:** The minimum cost displayed as 3 is incorrect.

### Correct Output:
For the provided input structure and edge costs, the correct minimal cost after AO* algorithm should be calculated and printed accurately, accounting for the depth and backtracking costs correctly.

### Conclusion:
The provided output is incorrect based on the analysis. The correct cost should reflect a logical traversal and backtracking with edge costs properly accounted for. The expected minimal cost should be re-evaluated based on the given algorithm and tree structure, leading to a correct minimal cost path, potentially around `9` as calculated.




*/