#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <tuple>
#include <iostream>
#include <cstdlib>
#include "moves.hh"

class Engine
{
    private:
        std::string fen; 
        char **board;
        Moves moves(board);

    public:

        // Calculate moves. Tuple input as following: <x, y>
        std::vector<int> calculate_moves(std::tuple<int, int> pos)
        {
            std::vector<std::tuple<int, int>> moves;
            auto diagonal = [] (int a) {
                return ;
            };

            switch(tolower(board[std::get<0>(pos)][std::get<1>(pos)]))
            {
                case 'p':
                    moves = pawn_move(pos);
                case 'r':
                    moves = rook_move(pos);
            }

        
            return;
        }
};