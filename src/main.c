/*
 * FILE: main.c
 * AUTHOR: sara van hoeve
 * ID: 1432671
 *
 * This file contains the main program logic for a tictactoe game,
 * handling game setup, player turns, and win and draw detection.
*/

#include <stdio.h>
#include "board.h"
#include "input.h"

//global variables required for all game functions
int size = 0;
int mode = 0;

char p1 = 'x';
char p2 = 'o';

int winner;

//function declarations
void player_turn(char board[MAX_SIZE][MAX_SIZE], char mark);

/*
 * main
 * controlls overall game, including board size and mode selection,
 * alternating turns, and detecting game results
*/
int main(void)
{
    int x_wins = 0;
    int o_wins = 0;
    int ties = 0;

    char play_again = '\0';

    //ask for a game board size within perimeters
    while (size > 10 || size < 3)
    {
        printf("Board Size (3-10): ");
        size = read_int();
    }

    //ask for a game mode
    while (mode < 1 || mode > 2)
    {
        printf("Game Mode (1 for 2 players or 2 for 1 players): ");
        mode = read_int();
    }

    char board[MAX_SIZE][MAX_SIZE];

    //continue running rounds while player selects y
    do {

        board_init(board, size);
        play_again = '\0';
        winner = 0;

        //continue running turns until the board is full or a player has won
        do {
            //check for which mode is selected
            if (mode == 1)
            {
                board_print(board, size);
                player_turn(board, p1);

                if (board_has_winner(board, size, p1) == 1)
                {
                    winner = 1;
                    break;
                }

                if (board_is_full(board, size))
                {
                    winner = -1;
                    break;
                }

                board_print(board, size);
                player_turn(board, p2);

                if (board_has_winner(board, size, p2) == 1)
                {
                    winner = 2;
                    break;
                }

                if (board_is_full(board, size))
                {
                    winner = -1;
                    break;
                }
            }
            //second game mode (against ai)
            else
            {
                board_print(board, size);
                player_turn(board, p1);

                if (board_has_winner(board, size, p1) == 1)
                {
                    winner = 1;
                    break;
                }

                if (board_is_full(board, size))
                {
                    winner = -1;
                    break;
                }

                board_print(board, size);
                ai_move(board, size, p2, p1);

                if (board_has_winner(board, size, p2) == 1)
                {
                    winner = 2;
                    break;
                }

                if (board_is_full(board, size))
                {
                    winner = -1;
                    break;
                } 
            }

        } while (winner == 0);

        board_print(board, size);

        //announce result and declare winner
        switch(winner)
        {
            case 1:
                printf("Player 1 Wins!\n");
                x_wins++;
                break;
            case 2:
                if (mode == 1) printf("Player 2 Wins!\n");
                else printf("Ai Wins!\n");
                o_wins++;
                break;
            default:
                printf("Cats Game!\n");
                ties++;
        }

        printf("Player 1 Wins: %d\tPlayer 2 Wins: %d\tTies: %d\n", x_wins, o_wins, ties);

        do { 
            printf("Play Again (Y/N): ");
            play_again = read_char();

        } while (play_again != 'Y' && play_again != 'y' && play_again != 'N' && play_again != 'n');

    } while (play_again == 'Y' || play_again == 'y');

    fflush(stdout);
    printf("\nFinal Scores\nPlayer 1 Wins: %d\tPlayer 2 Wins: %d\tTies: %d\n", x_wins, o_wins, ties);    

    return 0;
}

/*
 * player turn
 * gets a row and column selection from the player and places 
 * their mark on the board.
 * Implemented to keep the main function cleaner, similar to the 
 * breakdown of the ai move function in board.c
 *
 * has no return as it uses pointers (through the array)
*/
void player_turn(char board[MAX_SIZE][MAX_SIZE], char mark)
{
    int choice_x;
    int choice_y;
    
    do {
        printf("Choose a row: ");
        choice_x = read_int();

        printf("Choose a column: ");
        choice_y = read_int();

    } while (move_is_valid(board, size, choice_x, choice_y) != 1);

    board[choice_x][choice_y] = mark;
}