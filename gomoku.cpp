#include <iostream>

using namespace std;

const int N = 15;
const int M = 15;
const int a_row = 5;
const int n_players = 2;
char marks[n_players] = { 'X', 'O' };
char grid[N][M];
char lastTurnGrid[N][M];
void getGridBack()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            grid[i][j] = lastTurnGrid[i][j];
        }
    }
}

//This function prints the grid of Gomoku as the game progresses
void print_grid()
{
    for (int i = 0; i < n_players; i++)
    {
        cout << "Player " << i + 1 << ": " << marks[i] << "  ";
        if (i < n_players - 1)
            cout << "vs  ";
    }
    cout << "\n";
    cout << "--";
    for (int i = 0; i < M; cout << "---", i++);
    cout << "--\n";
    for (int i = 0; i < N; i++)
    {
        cout << "|  ";
        for (int j = 0; j < M; j++)
            cout << grid[i][j] << "  ";
        cout << "|\n";
        cout << "--";
        for (int i = 0; i < M; cout << "---", i++);
        cout << "--\n";
    }
}
//This function checks if the game has a win state or not
bool check_win()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < (M - 4); j++)
            if (grid[i][j] == grid[i][j + 1] && grid[i][j + 2] == grid[i][j] && grid[i][j + 3] == grid[i][j] && grid[i][j + 4] == grid[i][j] && grid[i][j] != ' ')
            {
                return true;
            }

    }


    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < (N - 4); j++)
            if (grid[j][i] == grid[j + 1][i] && grid[j + 2][i] == grid[j][i] && grid[j + 3][i] == grid[j][i] && grid[j + 4][i] == grid[j][i] && grid[j][i] != ' ')
            {
                return true;
            }
    }
    for (int i = 0; i < (N - 4); i++)
    {
        for (int j = 0; j < (M - 4); j++)
        {
            bool isThereWin = true;
            char mark = grid[i][j];
            if (mark == ' ')
                continue;
            int counter = 1;
            while (counter <= 4)
            {
                if (grid[i + counter][j + counter] != mark)
                {
                    isThereWin = false;
                    break;
                }
                counter += 1;
            }
            if (isThereWin)
                return true;

        }

    }


    for (int i = 4; i < M; i++)
    {
        for (int j = 0; j < (N - 4); j++)
        {
            bool isThereWin = true;
            char mark = grid[i][j];
            if (mark == ' ')
                continue;
            int counter = 1;
            while (counter <= 4)
            {
                cout << counter;
                if (grid[i - counter][j + counter] != mark)
                {
                    isThereWin = false;
                    break;
                }
                counter += 1;
            }
            if (isThereWin)
                return true;

        }

    }
    return false;
}

//This function checks if the game has a tie state or not
bool check_tie()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (grid[i][j] == ' ')
                grid[i][j] = 'X';
        }
    }
    if (check_win())
    {
        getGridBack();
        return false;
    }
    getGridBack();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (grid[i][j] == ' ')
                grid[i][j] = 'O';
        }
    }
    if (check_win())
    {
        getGridBack();
        return false;
    }
    getGridBack();
    return true;
}
//This function checks if given cell is empty or not
bool check_empty(int i, int j)
{
    if (grid[i][j] == ' ')
    {
        return true;
    }
    return false;
}
//This function checks if given position is valid or not
bool check_valid_position(int i, int j)
{
    if (0 <= i < 15 && 0 <= j < 15)
    {
        return true;
    }

    return false;
}
//This function sets the given mark to the given column
void set_cell(int i, int j, char mark)
{
    grid[i][j] = mark;
    lastTurnGrid[i][j] = mark;
}
//This function clears the game structures
void grid_clear()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            grid[i][j] = ' ';
            lastTurnGrid[i][j] = ' ';
        }
    }
}
//This function reads a valid position input
void read_input(int& i, int& j)
{
    cout << "Enter the row index and column index: ";
    cin >> i >> j;
    while (!check_valid_position(i, j) || !check_empty(i, j))
    {
        cout << "Enter a valid row index and a valid column index: ";
        cin >> i >> j;
    }
}
//MAIN FUNCTION
void play_game()
{
    cout << "Gomoku Game!\n";
    cout << "Welcome...\n";
    cout << "============================\n";
    int player = 0;
    while (true)
    {
        //Prints the grid
        print_grid();
        //Read an input from the player
        cout << "Player " << marks[player] << " is playing now\n";
        int i, j;
        read_input(i, j);
        //Set the input position with the mark
        set_cell(i, j, marks[player]);
        //Check if the state of the grid has a win state
        if (check_win())
        {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Congrats, Player " << marks[player] << " is won!\n";
            break;
        }
        //Check if the state of the grid has a tie state
        if (check_tie())
        {
            //Prints the grid
            print_grid();
            //Announcement of the final statement
            cout << "Woah! That's a tie!\n";
            break;
        }
        //Player number changes after each turn
        player = (player + 1) % n_players;
    }
}
int main()
{
    while (true)
    {
        grid_clear();
        play_game();
        char c;
        cout << "Play Again [Y/N] ";
        cin >> c;
        if (c != 'y' && c != 'Y')
            break;
    }
}