#include <iostream>
#include <array>
#include "ui.hh"

#define URL "localhost:8000"

std::string checkWin()
{
    return "none";
}

int main()
{
    Board chessBoard;
    Moves moves;
    UserInterface interface;
    int round = 0;
    while(!chessBoard.checkWin())
    {
        if(round % 2 == 0)
        {
            std::vector<Position> whitePositions = chessBoard.getPositions(islower('R'));
            Position first_piece = interface.mouseClick(whitePositions);
            std::vector<Position> possible_moves = moves.get_moves(first_piece.y, first_piece.x);
            // Highlight possible moves.
            for(auto x: possible_moves)
            {
                interface.highlightPosition(x.y, x.x);
            }
            Position mouse_pos = interface.mouseClick(possible_moves);
            board[mouse_pos.y][mouse_pos.x] = board[first_piece.y][first_piece.x];
            board[first_piece.y][first_piece.x] = '.';
            interface.drawBoxes();
            interface.loadImages();


            SDL_Delay(3000);
            interface.quit();
            break;
        }
        round+=1;
    }
    /*
    board[1][0] = '.';
    chessBoard.printBoard();
    std::vector<Position> get_move = moves.get_moves(0, 0);
    for(int i=0;i<get_move.size();i++)
    {
        printf("%d %d\n", get_move[i].y, get_move[i].x);
    }*/
    
    return 0;
}