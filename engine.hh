#include <map>
#include <vector>
#include "moves.hh"
#include "board.hh"

#ifndef ENGINE_HH_INCLUDED
#define ENGINE_HH_INCLUDED

#define MAX_INT	2000000

extern std::vector<std::vector<int>> pawnScores;

extern std::vector<std::vector<int>> rookScores;

extern std::vector<std::vector<int>> knightScores;

extern std::vector<std::vector<int>> bishopScores;

extern std::vector<std::vector<int>> queenScore;

extern std::vector<std::vector<int>> kingScores;

// Map with score for each position for each piece!
extern std::map<char, int> scores;

// Map with material scores.
extern std::map<char, std::vector<std::vector<int>>> positionScores;

class Engine
{
    public:
        char *board[8][8];
        Engine(char arr[8][8]);

        std::vector<Square> bestMove(Moves mve, int depth);

    private:
        int miniMax(Moves mve, bool maximizing, int depth, int alpha, int beta);

        std::vector<Square> getPositions(char boardCpy[8][8], bool maximizing);

        int evaluation(char boardCpy[8][8]);
};

#endif