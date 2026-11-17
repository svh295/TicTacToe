# TicTacToe

The purpose of this project was to design and implement a command line tic-tac-toe game written in C. The program allows players to play on a variable size board ranging from a three by three to a ten by ten. It has also been designed to enable single player games by implementing an ai move portion into the code, whist still allowing for the traditional two player games. 
The program checks that the selected moves are within boundaries and not already filled. It then checks for full diagonals, antidiagonals, rows, and columns, keeping track of which players’ marks are in those cells. The ai component follows basic decision-making strategies, checking first if it can win, then if it can block the opponents win, and finally, if none of the above, it picks a random cell. 
After each round the scores are displayed and the player(s) are asked if another game should be loaded. If so that scores of the successive games are kept track of, allowing players to play ‘best-of’ games.

