// You are given two unmarked jugs with capacities x and y liters. Determine the moves to obtain exactly n liters of water in any of the two jugs or both by the end.
// Given that:
// 1. There is infinite supply of water.
// 2. Both the jugs are empty at the beginning.
// Operations allowed:
// 1. Empty /fill a jug completely with water.
// 2. Pour water from one jug to another until one of the jugs is either empty or full.
#include <bits/stdc++.h>
using namespace std;

int x; // Capacity of the first jug
int y; // Capacity of the second jug

// Function to display the current state of the jugs
void show(int a, int b);

// Function to find the minimum of two integers
int min(int w, int z) {
    if (w < z)
        return w;
    else
        return z;
}

// Function to display the current state of the jugs
void show(int a, int b) {
    cout << setw(12) << a << setw(12) << b << endl;
}

// Function to simulate the pouring process to get 'n' liters of water
void s(int n) {
    int xq = 0, yq = 0; // Initial water levels in the jugs
    int t; // Temporary variable to hold the amount of water to pour
    cout << setw(15) << "FIRST JUG" << setw(15) << "SECOND JUG" << endl; // Print headers for the jugs

    // Continue pouring water until one of the jugs contains the desired amount 'n'
    while (xq != n && yq != n) {
        if (xq == 0) { // If the first jug is empty
            xq = x; // Fill the first jug to its maximum capacity
            show(xq, yq); // Display the state of the jugs
        } else if (yq == y) { // If the second jug is full
            yq = 0; // Empty the second jug
            show(xq, yq); // Display the state of the jugs
        } else { // Pour water from the first jug to the second jug
            t = min(y - yq, xq); // Calculate the amount of water that can be poured
            yq = yq + t; // Pour water into the second jug
            xq = xq - t; // Subtract the poured water from the first jug
            show(xq, yq); // Display the state of the jugs
        }
    }
    if(xq==n){
        yq=0;
    }else if(yq==n){
        xq=0;
    }
    show(xq, yq);
}

int main() {
    int n; // Desired amount of water

    // Prompt the user to enter the desired amount of water and the capacities of the jugs
    cout << "Enter the liters of water required out of the two jugs: ";
    cin >> n;
    cout << "Enter the capacity of the first jug: ";
    cin >> x;
    cout << "Enter the capacity of the second jug: ";
    cin >> y;

    // Check if it is possible to measure 'n' liters using the given jugs
    if (n < x || n < y) {
        // Check if 'n' is a multiple of the gcd of the capacities of the jugs
        if (n % (__gcd(x, y)) == 0)
            s(n); // Simulate the pouring process
        else
            cout << "This is not possible....\n"; // Print not possible
    } else
        cout << "This is not possible....\n"; // Print not possible
}
