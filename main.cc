#include <iostream>
#include "board.hh"
#include "moves.hh"
#include <array>

#define URL "localhost:8000"

std::string checkWin()
{
    return "none";
}

int main()
{
    Board board;
    Moves moves(board.board);
    board.printBoard();
    printf("\n");
    moves.printBoard();
    printf("\n");
    board.board[0][0] = 't';
    board.printBoard();
    printf("\n");
    moves.printBoard();

    return 0;
}