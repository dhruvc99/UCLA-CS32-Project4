/**
 * @file myttt.cpp 
 * @author Dhruv Chakraborty
 * @brief Tic Tac Toe game
 * PIC 10C Homework 3: Exception Handling
 */

#include <iostream>
using namespace std;

char square[10] = {'o','1','2','3','4','5','6','7','8','9'};

int checkwin();
void print_board();
void mark_square(int choice, char mark);
int comp_choice();
int get_num_players();
int get_input(int player);

class NumPlayersError: public logic_error
{
public:
    NumPlayersError(string reason, int num_players)
        :logic_error(reason), n(num_players) {}
    void PrintError() const
    {
        cout << "Invalid value (" << n << ") received. Please enter 1 or 2.\n";
    }
private:
    int n;
};

class WrongInputError: public logic_error
{
public:
    WrongInputError(string reason, int choice)
        :logic_error(reason), n(choice) {}
    void PrintError() const
    {
        cout << "Invalid square choice (" << n << ") to mark. Please enter a number between 1 and 9, ensuring that the square has already not been marked.\n";
    }
private:
    int n;
};

int main()
{
    int num_players;
    while(true)
    {
        try
        {
            num_players = get_num_players();
            break;
        }
        catch(NumPlayersError& e)
        {
            e.PrintError();
            cout << "Would you like to retry? (y/n)";
            char c;
            cin >> c;
            if (c == 'y')
                continue;
            else
                break;
        }
    }
    
    
    int player = -1; // player = 1 or -1
    int if_win;
    int choice; // player's move
    char mark;
    do
    {
        print_board();

        if (player == 1 && num_players == 1)
        {
            choice = comp_choice();
        }
        else
        {
            while(true)
            {
                try
                {
                    choice = get_input(player);
                    break;
                }
                catch(WrongInputError& e)
                {
                    e.PrintError();
                    cout << "Would you like to retry? (y/n)";
                    char c;
                    cin >> c;
                    if (c == 'y')
                        continue;
                    else
                        return 0;
                }
            }
        }

        // select player's mark symbol
        if (player == -1)
            mark = 'X';
        else if (player == 1)
            mark = 'O';
        
        // update square array according to player's move
        mark_square(choice, mark);
        
        // check if game stops
        if_win=checkwin();
        
        // change to next player's move
        player *= -1;
        
    } while(if_win==-1);
    
    print_board();
    if (if_win==1)
        cout<< "\nPlayer " << (-player+3)/2 << " win.\n ";
    else
        cout<< "\nTie Game.\n";

    return 0;
}

/*********************************************
    FUNCTION TO RETURN GAME STATUS
    1 FOR GAME IS OVER WITH RESULT
    -1 FOR GAME IS IN PROGRESS
    O GAME IS OVER AND NO RESULT
**********************************************/

int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
    // the board is full
    else if (   square[1] != '1' && square[2] != '2' && square[3] != '3'
             && square[4] != '4' && square[5] != '5' && square[6] != '6'
             && square[7] != '7' && square[8] != '8' && square[9] != '9')
        return 0; // tie situation
    else
        return -1; // game in progress
}


/*******************************************************************
     FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYER MARKS
********************************************************************/
void print_board()
{
    cout << "\n \t Tic Tac Toe \n";
    cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;

    cout << "     |     |     " << endl;
    cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;

    cout << "     |     |     " << endl << endl;
}

// update the square array accoring to player's move
void mark_square(int choice, char mark)
{
    // if choice = 1, c = '1', ...
    char c = '0'+choice;
    square[choice] = mark;
}

// return's computer's move in case of one player game
int comp_choice()
{
    if (square[1] == square[2] && square[3] == '3')
        return 3;
    else if (square[1] == square[3] && square[2] == '2')
        return 2;
    else if (square[2] == square[3] && square[1] == '1')
        return 1;
    else if (square[4] == square[5] && square[6] == '6')
        return 6;
    else if (square[4] == square[6] && square[5] == '5') 
        return 5;
    else if (square[5] == square[6] && square[4] == '4')
        return 4;
    else if (square[7] == square[8] && square[9] == '9')
        return 9;
    else if (square[7] == square[9] && square[8] == '8')
        return 8;
    else if (square[8] == square[9] && square[7] == '7')
        return 7;     
    else if (square[1] == square[4] && square[7] == '7')
        return 7;
    else if (square[1] == square[7] && square[4] == '4')
        return 4;
    else if (square[4] == square[7] && square[1] == '1')
        return 1;
    else if (square[2] == square[5] && square[8] == '8')
        return 8;
    else if (square[2] == square[8] && square[5] == '5')
        return 5;
    else if (square[5] == square[8] && square[2] == '2')
        return 2;
    else if (square[3] == square[6] && square[9] == '9')
        return 9;
    else if (square[3] == square[9] && square[6] == '6')
        return 6;
    else if (square[6] == square[9] && square[3] == '3')
        return 3;
    else if (square[1] == square[5] && square[9] == '9')
        return 9;
    else if (square[1] == square[9] && square[5] == '5')
        return 5;
    else if (square[5] == square[9] && square[1] == '1')
        return 1;
    else if (square[3] == square[5] && square[7] == '7')
        return 7;
    else if (square[3] == square[7] && square[5] == '5')
        return 5;
    else if (square[5] == square[7] && square[3] == '3')
        return 3;
    else
    {
        for (int i = 1; i <= 9; i++)
        {
            if (square[i] == (i+'0'))
                return i;
        }
    }
    return -1;
}

// get number of players from user
int get_num_players()
{
    int num_players;
    std::cout << "Do you want to play a 1-player or 2-player game? Please enter 1 or 2.\n";
    cin >> num_players;

    if (num_players > 2 || num_players < 1 || cin.fail())
    {
        throw NumPlayersError("Invalid number of players", num_players);
    }
    
    return num_players;
}

// get input from player to mark square
int get_input(int player)
{
    int choice;
    cout << "Player " << (player+3)/2 << ", enter a number:  ";
    cin >> choice; // player's move
    if (choice < 1 || choice > 9 || square[choice] != choice+'0' || cin.fail())
    {
        throw WrongInputError("Invalid input to mark square", choice);
    }    
    return choice;
}