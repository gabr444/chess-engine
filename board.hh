#include <string>
#include <vector>

#ifndef BOARD_HH_INCLUDED
#define BOARD_HH_INCLUDED

struct Square
{
    int y;
    int x;
};

Square get_pos(int y, int x);

class Board
{
    public:
        char board[8][8];
        std::string fen; 
        
        Board();

        std::string get_FEN();

        // FEN Input e.g: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
        void parse_FEN(std::string input_fen);
};

#endif