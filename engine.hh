#include <map>
#include <vector>

#define MAX_INT	2000000

std::vector<std::vector<int>> pawnScores   {{0,  0,  0,  0,  0,  0,  0,  0},
                                            {50, 50, 50, 50, 50, 50, 50, 50},
                                            {10, 10, 20, 30, 30, 20, 10, 10},
                                            {5,  5, 10, 25, 25, 10,  5,  5},
                                            {0,  0,  0, 20, 20,  0,  0,  0},
                                            {5, -5,-10,  0,  0,-10, -5,  5},
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
    { 'p', 20 },
    { 'r', 100 },
    { 'n', 60 },
    { 'b', 60 },
    { 'q', 180 },
    { 'k', 1800 }
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

        std::vector<Position> bestMove(Moves mve, int depth)
        {
            char boardCpy[8][8];
            Position bestEndPos;
            Position bestStartPos;
            Position bestPromotionPiece;
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
            Moves get_moves(boardCpy, mve.documentedMoves);

            for(Position pos: get_moves.getPositions(true))
            {
                for(Position move: get_moves.get_moves(pos.y, pos.x))
                {
                    get_moves.move_piece(pos, move);
                    if(get_moves.pawnPromotion(move))
                    {
                        char promotionPieces[2] = {'q', 'r'};
                        for(int i=0;i<2;i++)
                        {
                            get_moves.promotePawn(move, promotionPieces[i]);
                            int score = miniMax(get_moves, false, depth-1, alpha, beta);
                            if(score > bestScore)
                            {
                                bestScore = score;
                                bestStartPos = pos;
                                bestEndPos = move;
                                bestPromotionPiece.y = i;
                            }
                            if(score > alpha)
                            {
                                alpha = score;
                            }
                            get_moves.undo_move();
                        }
                    }
                    else
                    {
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
            }
            
            std::vector<Position> bestMoves {bestStartPos, bestEndPos, bestPromotionPiece};

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
            Moves testMoves(boardCpy);
            if(testMoves.checkMate(true))
            {
                return MAX_INT;
            }
            
            if(testMoves.checkMate(false))
            {
                return -MAX_INT;
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
                    testMoves.move_piece(pos, move);
                    if(testMoves.pawnPromotion(move))
                    {
                        char promotionPieces[2] = {'q', 'n'};
                        if(!maximizing)
                        {
                            promotionPieces[0] = 'Q';
                            promotionPieces[1] = 'N';
                        }
                        for(int i=0;i<2;i++)
                        {
                            testMoves.promotePawn(move, promotionPieces[i]);
                            int score = miniMax(testMoves, false, depth-1, alpha, beta);
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

                    else
                    {
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
                }

                if(prune)
                {
                    prune = false;
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
                        if(islower(piece))
                        {
                            int positionScore = positionScores.at(piece)[7-i][j]/5;
                            blackScore += scores.at(piece)+mobilityScore;
                        }
                        
                        else
                        {
                            int positionScore = positionScores.at(piece)[i][j]/5;
                            whiteScore+=scores.at(piece)+mobilityScore;
                        }
                    }
                }
            }

            return blackScore-whiteScore;
        }
};