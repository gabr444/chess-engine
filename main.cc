#include <iostream>
#include "moves.hh"
#include <array>

#define URL "localhost:8000"

std::string checkWin()
{
    return "none";
}

int main()
{
    Board chessBoard;
    Moves moves;
    board[1][0] = '.';
    chessBoard.printBoard();
    std::vector<std::tuple<int, int>> get_moves = moves.get_moves(0, 0);
    for(int i=0;i<get_moves.size();i++)
    {
        printf("%d %d\n", std::get<0>(get_moves[i]), std::get<1>(get_moves[i]));
    }

    return 0;
}