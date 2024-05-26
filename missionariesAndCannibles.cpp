#include <iostream>
#include <iomanip>
using namespace std;

class game
{
public:
    int counto, i; // Count of turns and loop index
    char left[6], right[6]; // Arrays representing the left and right sides of the river
    int m_num, c_num; // Number of missionaries and cannibals to move
    bool side; // Side of the boat: false = left, true = right
    int ml_count, cl_count; // Number of missionaries and cannibals on the left side
    int mr_count, cr_count; // Number of missionaries and cannibals on the right side

    // Constructor to initialize the game
    game()
    {
        counto = 1; // Initial turn count
        ml_count = cl_count = 3; // Initial counts of missionaries and cannibals on the left side
        mr_count = cr_count = 0; // Initial counts of missionaries and cannibals on the right side
        side = false; // Initial boat side (left)

        // Initialize the left side with 3 missionaries and 3 cannibals
        for (i = 0; i < 3; i++)
        {
            left[i] = 'M'; // Missionaries
            left[i + 3] = 'C'; // Cannibals
            right[i] = ' '; // Empty right side
            right[i + 3] = ' '; // Empty right side
        }
    }

    // Function to get the user input for
    // Function to get the user input for the number of missionaries and cannibals to move
    void get()
    {
    start:
        cout << "\nEnter no.of missionaries= ";
        cin >> m_num; // Get number of missionaries
        cout << "\nEnter no.of cannibals= ";
        cin >> c_num; // Get number of cannibals

        // Validate input: must be within range and total number of passengers must be between 1 and 2
        if (m_num > 3 || c_num > 3 || m_num < 0 || c_num < 0 || (m_num + c_num) > 2 || (m_num + c_num == 0))
            goto start; // If invalid, ask for input again
    }

    // Function to display the current state of both sides
    void display()
    {
        cout << "\nleft side\tright side\n";

        // Display the left side
        for (i = 0; i < 3; i++)
            cout << left[i] << " ";
        cout << "\t\t";
        for (i = 0; i < 3; i++)
            cout << right[i] << " ";
        cout << endl;

        // Display the right side
        for (i = 3; i < 6; i++)
            cout << left[i] << " ";
        cout << "\t\t";
        for (i = 3; i < 6; i++)
            cout << right[i] << " ";
        cout << endl;

        // Indicate which side the boat is on
        if (counto % 2 == 0)
        {
            side = true; // Boat is on the right side
            cout << "\nBoat on right side of river\n";
        }
        else
        {
            side = false; // Boat is on the left side
            cout << "\nBoat on left side of river\n";
        }
    }

    // Function to move missionaries and cannibals from left to right
    void boat_lr()
    {
        // Move missionaries
        for (i = 0; i < m_num; i++)
        {
            if (left[0] == 'M')
            {
                left[0] = ' ';
                right[0] = 'M';
                ml_count -= 1;
                mr_count += 1;
            }
            else if (left[1] == 'M')
            {
                left[1] = ' ';
                right[1] = 'M';
                ml_count -= 1;
                mr_count += 1;
            }
            else if (left[2] == 'M')
            {
                left[2] = ' ';
                right[2] = 'M';
                ml_count -= 1;
                mr_count += 1;
            }
        }

        // Move cannibals
        for (i = 0; i < c_num; i++)
        {
            if (left[3] == 'C')
            {
                left[3] = ' ';
                right[3] = 'C';
                cl_count -= 1;
                cr_count += 1;
            }
            else if (left[4] == 'C')
            {
                left[4] = ' ';
                right[4] = 'C';
                cl_count -= 1;
                cr_count += 1;
            }
            else if (left[5] == 'C')
            {
                left[5] = ' ';
                right[5] = 'C';
                cl_count -= 1;
                cr_count += 1;
            }
        }
    }

    // Function to move missionaries and cannibals from right to left
    void boat_rl()
    {
        // Move missionaries
        for (i = 0; i < m_num; i++)
        {
            if (right[0] == 'M')
            {
                right[0] = ' ';
                left[0] = 'M';
                ml_count += 1;
                mr_count -= 1;
            }
            else if (right[1] == 'M')
            {
                right[1] = ' ';
                left[1] = 'M';
                ml_count += 1;
                mr_count -= 1;
            }
            else if (right[2] == 'M')
            {
                right[2] = ' ';
                left[2] = 'M';
                ml_count += 1;
                mr_count -= 1;
            }
        }

        // Move cannibals
        for (i = 0; i < c_num; i++)
        {
            if (right[3] == 'C')
            {
                right[3] = ' ';
                left[3] = 'C';
                cl_count += 1;
                cr_count -= 1;
            }
            else if (right[4] == 'C')
            {
                right[4] = ' ';
                left[4] = 'C';
                cl_count += 1;
                cr_count -= 1;
            }
            else if (right[5] == 'C')
            {
                right[5] = ' ';
                left[5] = 'C';
                cl_count += 1;
                cr_count -= 1;
            }
        }
    }
};

int main()
{
    game g; // Create a game object

    while (true)
    {
        // Check for losing conditions: more cannibals than missionaries on either side (and missionaries > 0)
        if ((g.ml_count < g.cl_count && g.ml_count > 0) || (g.mr_count < g.cr_count && g.mr_count > 0))
        {
            cout << "\n\n~~~~~~~~~~~~~~~~YOU LOST!!~~~~~~~~~~~~~~~~\n";
            break; // End game if lost
        }
        // Check for winning condition: all missionaries and cannibals on the right side
        else if (g.cr_count == 3 && g.mr_count == 3)
        {
            cout << "\n\n~~~~~~~~~~~~~~~~YOU WON!!~~~~~~~~~~~~~~~~\n";
            break; // End game if won
        }
        else
        {
            g.display(); // Display current state
            g.get(); // Get user input

            // Move boat based on current side
            if (!g.side)
                g.boat_lr();
            else
                g.boat_rl();
        }
        g.counto++; // Increment turn count
    }
    return 0;
}
