#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Function to convert a string to its numerical equivalent based on the provided mapping
int getNumber(string s, unordered_map<char, int>& hm) {
    string num = "";
    // Construct the number as a string based on the mapping
    for (int i = 0; i < s.length(); i++) {
        num += to_string(hm[s[i]]);
    }
    // Convert the constructed string to an integer
    return stoi(num);
}

// Recursive function to solve the cryptarithm
void solve(int i, string unique, unordered_map<char, int>& hm, vector<bool>& used, vector<string>& words, string result) {
    // Base case: if all unique characters are assigned a digit
    if (i == unique.length()) {
        int sum = 0;
        // Calculate the sum of the numerical equivalents of the words
        for (const string& s : words) {
            sum += getNumber(s, hm);
        }
        // Get the numerical equivalent of the result word
        int r = getNumber(result, hm);
        // Check if the sum of the words equals the result
        if (sum == r) {
            // Print the mapping if a valid solution is found
            for (int k = 0; k <= 25; k++) {
                char ch = static_cast<char>('A' + k);
                if (hm.find(ch) != hm.end()) {
                    cout << ch << " -> " << hm[ch] << " ";
                }
            }
            cout << endl;
        }
        return;
    }

    // Recursive case: try assigning digits to the current character
    char ch = unique[i];
    for (int j = 0; j <= 9; j++) {
        // Only assign the digit if it hasn't been used yet
        if (!used[j]) {
            hm[ch] = j;
            used[j] = true;
            // Recur for the next character
            solve(i + 1, unique, hm, used, words, result);
            // Backtrack: unassign the digit and mark it as unused
            hm[ch] = -1;
            used[j] = false;
        }
    }
}

int main() {
    // List of words in the cryptarithm
    vector<string> words = {"SEND", "MORE"};
    // The result word in the cryptarithm
    string result = "MONEY";
    // Mapping from characters to digits
    unordered_map<char, int> hm;
    // String to keep track of unique characters
    string unique = "";

    // Initialize the mapping for characters in the words
    for (const string& s : words) {
        for (char ch : s) {
            if (hm.find(ch) == hm.end()) {
                hm[ch] = -1;
                unique += ch;
            }
        }
    }

    // Initialize the mapping for characters in the result word
    for (char ch : result) {
        if (hm.find(ch) == hm.end()) {
            hm[ch] = -1;
            unique += ch;
        }
    }

    // Boolean vector to keep track of used digits
    vector<bool> used(10, false);
    // Solve the cryptarithm
    solve(0, unique, hm, used, words, result);

    return 0;
}
