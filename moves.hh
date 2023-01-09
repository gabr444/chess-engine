#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <cstdlib>
#include "board.hh"

#ifndef MOVES_HH_INCLUDED
#define MOVES_HH_INCLUDED

class Moves
{
    public:
        std::vector<Square> documentedMoves;
        char *board[8][8];
        char previousBoard[8][8];
        Square latestMove; 

        Moves(char arr[8][8], const std::vector<Square> moves = std::vector<Square>(), Square lastMove = get_pos(-1, -1));
        
    private:
        bool movedPosition(Square pos);

        bool out_of_bounds(int y, int x);

        std::vector<Square> pawn_move(Square pos);

        std::vector<Square> rook_move(Square pos);

        std::vector<Square> knight_move(Square pos);

        std::vector<Square> bishop_move(Square pos);

        std::vector<Square> king_move(Square pos);

        std::vector<Square> queen_move(Square pos);


    public:
        std::vector<Square> get_moves(int y, int x);

        void castle(Square start1, Square end1, Square start2, Square end2);

        void move_piece(Square start, Square end, bool documentMove = true);

        void undo_move();

        bool pawnPromotion(Square pos);

        void promotePawn(Square pos, char piece);

        bool isCheck(bool lowercase);

        std::vector<Square> filterMoves(Square pos, std::vector<Square> moves);

        bool checkMate(bool lowercase);

        bool staleMate(bool lowercase);

        std::vector<Square> getPositions(bool lowercase);

        void printBoard();
};
#endif