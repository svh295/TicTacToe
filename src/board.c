/*
 * FILE: board.c
 * AUTHOR: sara van hoeve
 * ID: 1432671
 * 
 * This file contains functions for initializing, displaying, and checking
 * the game board, as well as controlling the ai move.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

/*
 * board init
 * initializes the board by setting all cells to empty
*/
void board_init(char board[MAX_SIZE][MAX_SIZE], int n)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++) board[i][j] = EMPTY;
    }
}

/*
 * board print
 * clears the screen and displays the board with row and column numbers
 * to help identify cell positions
 */
void board_print(char board[MAX_SIZE][MAX_SIZE], int n)
{
    system("cls");
    fflush(stdout);

    printf("\n");
    printf("   ");

    for (int i=0;i<n;i++) printf("%2d  ", i);

    printf("\n");
    printf("  +");

    for (int i=0;i<n;i++) printf("---+");

    printf("\n");

    for (int i=0;i<n;i++)
    {
        printf("%d |", i);

        for (int j=0;j<n;j++) printf(" %c |", board[i][j]);

        printf("\n");
        printf("  +");

        for (int j=0;j<n;j++) printf("---+");

        printf("\n");
    }

    fflush(stdout);

}

/*
 * Move is valid
 * checks whether a requeted move is within the board boundaries
 * and whether the selected cell is empty
 *
 * returns 1 for valid and 0 for not
 */
int move_is_valid(char board[MAX_SIZE][MAX_SIZE], int n, int row, int col)
{
    if (n <= 0) return 0;
    if (row < 0 || row >= n || col < 0 || col >= n) return 0;
    if (board[row][col] != EMPTY) return 0;
    return 1;
}

/*
 * board has winner
 * checks whether the passed mark has a full row, column
 * diagnol, or antidiagnol
 *
 * returns 1 for a full and 0 for not
*/
int board_has_winner(char board[MAX_SIZE][MAX_SIZE], int n, char mark)
{
    int full_diag = 1;
    int full_inverse_diag = 1;

    for (int i=0;i<n;i++)
    {
        int full_row = 1;
        int full_col = 1;

        for (int j=0;j<n;j++)
        {
            if (board[i][j] != mark) full_row = 0;
        
            if (board[j][i] != mark) full_col = 0;
        }

        if (full_row || full_col) return 1;

        if (board[i][i] != mark) full_diag = 0;

        if (board[i][n-1-i] != mark) full_inverse_diag = 0;
        
    }

    return full_diag || full_inverse_diag;
}

/*
 * board is full
 * checks if every cell is occupied
 *
 * returns 1 if the board is full and 0 if not
*/
int board_is_full(char board[MAX_SIZE][MAX_SIZE], int n)
{
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (board[i][j] == EMPTY) return 0;
        }
    }

    return 1;
}

/*
 * ai move
 * determines and makes the computer move by first checking for a win, then a block,
 * and lastly a random cell.
*/
void ai_move(char board[MAX_SIZE][MAX_SIZE], int n, char ai_mark, char human_mark)
{
    srand(time(NULL));

    int pos[2] = {-1, -1};

    calculate_win(pos, board, n, ai_mark);

    if (pos[0] != -1 && pos[1] != -1) board[pos[0]][pos[1]] = ai_mark;
    else
    {
        calculate_win(pos, board, n, human_mark);
        if (pos[0] != -1 && pos[1] != -1) board[pos[0]][pos[1]] = ai_mark;
        else 
        {
            do
            {
                pos[0] = (rand() % n);
                pos[1] = (rand() % n);

            } while (move_is_valid(board, n, pos[0], pos[1]) != 1);

            board[pos[0]][pos[1]] = ai_mark;
        }
    }
}
/*
 * calculate win
 * searches the board for a row, column, diagnal, or antidiagnal that has n - 1 marks, storing
 * the position of the empty cell of that section 
 *
 * returns by pointer, thus no return is required.
 */
void calculate_win(int pos[], char board[MAX_SIZE][MAX_SIZE], int n, char mark)
{
    int marks;
    int empty;

    //check rows
    for (int i=0; i<n; i++)
    {
        marks = 0;
        empty = -1;

        for (int j=0; j<n; j++)
        {
            if (board[i][j] == mark) marks++;
            if (board[i][j] == EMPTY) empty = j;
        }

        if (marks == n - 1 && empty != -1)
        {
            pos[0] = i;
            pos[1] = empty;
            return;
        }
    }

    //check columns
    for (int j=0;j<n;j++)
    {
        marks = 0;
        empty = -1;

        for (int i=0;i<n;i++)
        {
            if (board[i][j] == mark) marks++;
            if (board[i][j] == EMPTY) empty = i;
        }

        if (marks == n-1 && empty != -1)
        {
            pos[0] = empty;
            pos[1] = j;
            return;
        }
    }
    
    //check diagnal
    marks = 0;
    empty = -1;

    for (int i=0; i<n; i++)
    {
        if(board[i][i] == mark) marks++;
        if (board[i][i] == EMPTY) empty = i;
    }

    if (marks == n-1 && empty != -1)
    {
        pos[0] = empty;
        pos[1] = empty;
        return;
    }

    //check inverse diagnal
    marks = 0;
    empty = -1;

    for (int i=0; i<n; i++)
    {
        int j = n-1-i;

        if (board[i][j] == mark) marks++;
        if (board[i][j] == EMPTY) empty = i;
    }

    if (marks == n-1 && empty != -1)
    {
        pos[0] = empty;
        pos[1] = n-1-empty;
        return;
    }

    return;
}