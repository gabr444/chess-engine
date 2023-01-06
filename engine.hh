#include <map>
#include <vector>

#define MAX_INT	2000000

std::vector<std::vector<int>> pawnScores   {{0,  0,  0,  0,  0,  0,  0,  0},
                                            {50, 50, 50, 50, 50, 50, 50, 50},
                                            {10, 10, 20, 30, 30, 20, 10, 10},
                                            {5,  5, 10, 25, 25, 10,  5,  5},
                                            {0,  0,  0, 20, 20,  0,  0,  0},
                                            {5, -5,-10,  0,  0, -10, -5,  5},
                                            {5, 10, 10,-20,-20, 10, 10,  5},
                                            {0,  0,  0,  0,  0,  0,  0,  0}};

std::vector<std::vector<int>> rookScores   {{  0,  0,  0,  0,  0,  0,  0,  0},
                                            {5, 10, 10, 10, 10, 10, 10,  5},
                                            {-5,  0,  0,  0,  0,  0,  0, -5},
                                            {-5,  0,  0,  0,  0,  0,  0, -5},
                                            {-5,  0,  0,  0,  0,  0,  0, -5},
                                            {-5,  0,  0,  0,  0,  0,  0, -5},
                                            {-5,  0,  0,  0,  0,  0,  0, -5},
                                            {0,  0,  0,  5,  5,  0,  0,  0}};

std::vector<std::vector<int>> knightScores {{-50,-40,-30,-30,-30,-30,-40,-50},
                          {-40,-20,  0,  0,  0,  0,-20,-40},
                          {-30,  0, 10, 15, 15, 10,  0,-30},
                          {-30,  5, 15, 20, 20, 15,  5,-30},
                          {-30,  0, 15, 20, 20, 15,  0,-30},
                          {-30,  5, 10, 15, 15, 10,  5,-30},
                          {-40,-20,  0,  5,  5,  0,-20,-40},
                          {-50,-40,-30,-30,-30,-30,-40,-50,}};

std::vector<std::vector<int>> bishopScores {{-20,-10,-10,-10,-10,-10,-10,-20},
                          {-10,  0,  0,  0,  0,  0,  0,-10},
                          {-10,  0,  5, 10, 10,  5,  0,-10},
                          {-10,  5,  5, 10, 10,  5,  5,-10},
                          {-10,  0, 10, 10, 10, 10,  0,-10},
                          {-10, 10, 10, 10, 10, 10, 10,-10},
                          {-10,  5,  0,  0,  0,  0,  5,-10},
                          {-20,-10,-10,-10,-10,-10,-10,-20}};

std::vector<std::vector<int>> queenScore {{-20,-10,-10, -5, -5,-10,-10,-20},
                               {-10,  0,  0,  0,  0,  0,  0,-10},
                               {-10,  0,  5,  5,  5,  5,  0,-10},
                               {-5,  0,  5,  5,  5,  5,  0, -5 },
                               {0,  0,  5,  5,  5,  5,  0, -5  },
                               {-10,  5,  5,  5,  5,  5,  0,-10},
                               {-10,  0,  5,  0,  0,  0,  0,-10},
                               {-20,-10,-10, -5, -5,-10,-10,-20}};

std::vector<std::vector<int>> kingScores {{-30,-40,-40,-50,-50,-40,-40,-30},
                    {-30,-40,-40,-50,-50,-40,-40,-30},
                        {-30,-40,-40,-50,-50,-40,-40,-30},
                        {-30,-40,-40,-50,-50,-40,-40,-30},
                        {-20,-30,-30,-40,-40,-30,-30,-20},
                        {-10,-20,-20,-20,-20,-20,-20,-10},
                        { 20, 20,  0,  0,  0,  0, 20, 20},
                        { 20, 30, 10,  0,  0, 10, 30, 20}};

// Map with score for each piece!
std::map<char, int> scores = 
{
    { 'p', 100 },
    { 'r', 900 },
    { 'n', 300 },
    { 'b', 300 },
    { 'q', 900 },
    { 'k', 5000 }
};

std::map<char, std::vector<std::vector<int>>> positionScores = 
{
    { 'p', pawnScores },
    { 'r', rookScores },
    { 'n', knightScores },
    { 'b', bishopScores },
    { 'q', queenScore },
    { 'k', kingScores }
};

class Engine
{
    public:
        char *board[8][8];
        Engine(char arr[8][8])
        {
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    board[i][j] = &arr[i][j];
                }
            }
        } 

        int positionsChecked = 0;

        std::vector<Position> bestMove(Moves mve, int depth)
        {
            char boardCpy[8][8];
            Position bestEndPos = get_pos(-1, -1);
            Position bestStartPos = get_pos(-1, -1);
            int alpha = -MAX_INT;
            int beta = MAX_INT;
            int bestScore = -MAX_INT;
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    boardCpy[i][j] = *board[i][j];
                }
            }
            Moves get_moves(boardCpy, mve.documentedMoves, mve.latestMove);

            for(Position pos: get_moves.getPositions(true))
            {
                for(Position move: get_moves.filterMoves(pos, get_moves.get_moves(pos.y, pos.x)))
                {
                    positionsChecked+=1;
                    get_moves.move_piece(pos, move);
                    if(get_moves.pawnPromotion(move))
                    {
                        get_moves.promotePawn(move, 'q');
                    }
                    int score = miniMax(get_moves, false, depth-1, alpha, beta);
                    if(score > bestScore)
                    {
                        bestScore = score;
                        bestStartPos = pos;
                        bestEndPos = move;
                    }
                    if(score > alpha)
                    {
                        alpha = score;
                    }

                    get_moves.undo_move();
                }
            }

            std::cout << positionsChecked << std::endl;
            positionsChecked = 0;
            
            std::vector<Position> bestMoves {bestStartPos, bestEndPos};

            return bestMoves;
        }

    private:
        int miniMax(Moves mve, bool maximizing, int depth, int alpha, int beta)
        {
            char boardCpy[8][8];
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    boardCpy[i][j] = *mve.board[i][j];
                }
            }

            Moves testMoves(boardCpy, mve.documentedMoves, mve.latestMove);

            if(testMoves.checkMate(true))
            {
                return MAX_INT;
            }
            
            if(testMoves.checkMate(false))
            {
                return -MAX_INT;
            }

            if(testMoves.staleMate(maximizing))
            {
                return 0;
            }

            if(depth == 0)
            {
                return evaluation(boardCpy);
            }

            int bestScore = -MAX_INT;

            if(!maximizing)
            {
                bestScore = MAX_INT;
            }

            bool prune = false;
            for(Position pos: testMoves.getPositions(maximizing))
            {
                for(Position move: testMoves.filterMoves(pos, testMoves.get_moves(pos.y, pos.x)))
                {
                    positionsChecked+=1;
                    testMoves.move_piece(pos, move);
                    if(testMoves.pawnPromotion(move))
                    {
                        testMoves.promotePawn(move, 'q');
                    }
                    int score = miniMax(testMoves, !maximizing, depth-1, alpha, beta);
                    testMoves.undo_move();
                    if(maximizing)
                    {
                        if(score > bestScore)
                        {
                            bestScore = score;
                        }   

                        if(score > alpha)
                        {
                            alpha = score;
                        }
                    }
                    else
                    {
                        if(score < bestScore)
                        {
                            bestScore = score;
                        }
                        if(beta > score)
                        {
                            beta = score;
                        }
                    }

                    if(beta <= alpha)
                    {
                        prune = true;
                        break;
                    }
                }

                if(prune)
                {
                    break;
                }
            }

            return bestScore;
        }

        std::vector<Position> getPositions(char boardCpy[8][8], bool maximizing)
        {
            std::vector<Position> availablePositions;
            for(int i=0;i<8;i++)
            {
                for(int j=8;j<8;j++)
                {
                    if(boardCpy[i][j] != '.' && !islower(boardCpy[i][j]))
                    {
                        if(maximizing && islower(boardCpy[i][j]) || !maximizing && !islower(boardCpy[i][j])) 
                        {
                            availablePositions.push_back(get_pos(i, j));
                        }
                    }
                }
            }

            return availablePositions;
        }

        int evaluation(char boardCpy[8][8])
        {
            int blackScore = 0;
            int whiteScore = 0;
            Moves mve(boardCpy);
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(boardCpy[i][j] != '.')
                    {
                        char piece = tolower(boardCpy[i][j]);
                        int mobilityScore = mve.get_moves(i, j).size();
                        if(islower(boardCpy[i][j]))
                        {
                            int positionScore = positionScores.at(piece)[7-i][j];
                            blackScore += scores.at(piece)+mobilityScore+positionScore;
                        }
                        
                        else
                        {
                            int positionScore = positionScores.at(piece)[i][j];
                            whiteScore+=scores.at(piece)+mobilityScore+positionScore;
                        }
                    }
                }
            }

            return blackScore-whiteScore;
        }
};
