#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int board[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};

void show_board()
{
    cout << "   "<< "    |   "<< "    |   " << endl;
    cout << "   " << board[0] << "   |   " << board[1] << "   |   " << board[2] << endl;
    cout << "-------------------------" << endl;
    cout << "   "<< "    |   "<< "    |   " << endl;
    cout << "   " << board[3] << "   |   " << board[4] << "   |   " << board[5] << endl;
    cout << "-------------------------" << endl;
    cout << "   "<< "    |   "<< "    |   " << endl;
    cout << "   " << board[6] << "   |   " << board[7] << "   |   " << board[8] << endl;
}

void Go(int index, int turn)
{
    board[index] = (turn % 2 != 0) ? 3 : 5;
}

int GetUserMove()
{
    int move;
    cout<<"3 is for human and 5 is for computer:";
    cout << "Enter your move (1-9): ";

    cin >> move;
    return move - 1; // Adjusting for zero-based indexing
}

int posswin(int player)
{
    if (player == 3)
    {
        //row wise
        for (int i = 0; i < 9; i += 3)
        {
            if (board[i] * board[i + 1] * board[i + 2] == 18)
            {
                if (board[i] == 2)
                {
                    return i;
                }
                if (board[i + 1] == 2)
                {
                    return i + 1;
                }
                if (board[i + 2] == 2)
                {
                    return i + 2;
                }
            }
        }

        //column wise
        for (int i = 0; i < 3; i++)
        {
            if (board[i] * board[i + 3] * board[i + 6] == 18)
            {
                if (board[i] == 2)
                {
                    return i;
                }
                if (board[i + 3] == 2)
                {
                    return i + 3;
                }
                if (board[i + 6] == 2)
                {
                    return i + 6;
                }
            }
        }

        //diagonals
        if (board[0] * board[4] * board[8] == 18)
        {
            if (board[0] == 2)
            {
                return 0;
            }
            if (board[4] == 2)
            {
                return 4;
            }
            if (board[8] == 2)
            {
                return 8;
            }
        }

        if (board[2] * board[4] * board[6] == 18)
        {
            if (board[2] == 2)
            {
                return 2;
            }
            if (board[4] == 2)
            {
                return 4;
            }
            if (board[6] == 2)
            {
                return 6;
            }
        }
    }
    if (player == 5)
    {
        //row
        for (int i = 0; i < 9; i += 3)
        {
            if (board[i] * board[i + 1] * board[i + 2] == 50)
            {
                if (board[i] == 2)
                {
                    return i;
                }
                if (board[i + 1] == 2)
                {
                    return i + 1;
                }
                if (board[i + 2] == 2)
                {
                    return i + 2;
                }
            }
        }

        //col
        for (int i = 0; i < 3; i++)
        {
            if (board[i] * board[i + 3] * board[i + 6] == 50)
            {
                if (board[i] == 2)
                {
                    return i;
                }
                if (board[i + 3] == 2)
                {
                    return i + 3;
                }
                if (board[i + 6] == 2)
                {
                    return i + 6;
                }
            }
        }

        //daigonal
        if (board[0] * board[4] * board[8] == 50)
        {
            if (board[0] == 2)
            {
                return 0;
            }
            if (board[4] == 2)
            {
                return 4;
            }
            if (board[8] == 2)
            {
                return 8;
            }
        }

        if (board[2] * board[4] * board[6] == 50)
        {
            if (board[2] == 2)
            {
                return 2;
            }
            if (board[4] == 2)
            {
                return 4;
            }
            if (board[6] == 2)
            {
                return 6;
            }
        }
    }

    return -1;
}
int Make2()
{
    if (board[5] == 2)
    {
        return 5;
    }
    else
    {
        int options[] = {2, 4, 6, 8};
        int index = rand() % 4; // Generates a random index (0 to 3)
        return options[index];
    }
}

bool check_winner(int player)
{
    //row
    for (int i = 0; i < 9; i += 3)
    {
        if (board[i] * board[i + 1] * board[i + 2] == player * player * player)
        {
            return true;
        }
    }

    //col
    for (int i = 0; i < 3; i++)
    {
        if (board[i] * board[i + 3] * board[i + 6] == player * player * player)
        {
            return true;
        }
    }

    //diagonally
    if (board[0] * board[4] * board[8] == player * player * player)
    {
        return true;
    }

    if (board[2] * board[4] * board[6] == player * player * player)
    {
        return true;
    }

    return false;
}

int main()
{
    show_board();
    int turn = 1;
    while (turn <= 9)
    {
        if (turn % 2 != 0) // Human's turn
        {
            int userMove = GetUserMove();
            while (board[userMove] != 2)
            {
                cout << "Invalid move. Try again." << endl;
                userMove = GetUserMove();
            }
            Go(userMove, turn);
        }
        else // Computer's turn
        {
            if (turn == 2)
            {
                Go((board[4] == 2) ? 4 : 1, turn);
            }
            else if (turn == 4)
            {
                if (posswin(3) != -1)
                {
                    Go(posswin(3), turn);
                }
                else
                {
                    Go(Make2(), turn);
                }
            }
            else if (turn % 2 == 0 && turn <= 8)
            {
                if (posswin(5) != -1)
                {
                    Go(posswin(5), turn);
                }
                else if (posswin(3) != -1)
                {
                    Go(posswin(3), turn);
                }
                else
                {
                    Go(Make2(), turn);
                }
            }
        }
        

        show_board();

        if (check_winner(3))
        {
            cout << "Human wins!" << endl;
            break;
        }
        else if (check_winner(5))
        {
            cout << "Computer wins!" << endl;
            break;
        }
        else if (turn == 9)
        {
            cout << "It's a draw!" << endl;
            break;
        }
        turn++;
    }

    return 0;
}
