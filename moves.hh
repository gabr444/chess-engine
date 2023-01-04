#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <cstdlib>

class Moves
{
    public:
        std::vector<Position> documentedMoves;
        char *board[8][8];
        char previousBoard[8][8];
        Position latestMove; 

        Moves(char arr[8][8], const std::vector<Position> moves = std::vector<Position>())
        {
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    board[i][j] = &arr[i][j];
                }
            }

            if(moves.size() > 0)
            {
                documentedMoves = moves;
            }
        } 
        
    private:
        bool movedPosition(Position pos)
        {
            for(Position x: documentedMoves)
            {
                if(pos.y == x.y && pos.x == x.x)
                {
                    return true;
                }
            }
            return false;
        }

        bool out_of_bounds(int y, int x)
        {
            bool out_of_bounds = true;
            if(y < 8 && y > -1 && x < 8 && x > -1)
            {
                out_of_bounds = false;
            }

            return out_of_bounds;
        }

        std::vector<Position> pawn_move(Position pos)
        {
            std::vector<Position> moves;
            int y = pos.y;
            int x = pos.x;
            auto lowercase = islower(*board[y][x]);
            int direction = 1;
            if(!lowercase)
            {
                direction = -1;
            }
            if(!out_of_bounds(y+direction, x))
            {
                if(*board[y+direction][x] == '.')
                {
                    moves.push_back(get_pos(y+direction, x));
                    if(!out_of_bounds(y+direction*2, x))
                    {
                        if(*board[y+direction*2][x] == '.')
                        {
                            if(lowercase && y == 1 || !lowercase && y == 6)
                            {
                                moves.push_back(get_pos(y+direction*2, x));
                            }
                        }
                    }
                }
            }

            if(x != 0 && *board[y+direction][x-1] != '.' && islower(*board[y+direction][x-1]) != lowercase)
            {
                moves.push_back(get_pos(y+direction, x-1));
            }

            if(x != 7 && *board[y+direction][x+1] != '.' && islower(*board[y+direction][x+1]) != lowercase)
            {
                moves.push_back(get_pos(y+direction, x+1));
            }

            if(x != 0)
            {
                if(*board[y+direction][x-1] == '.' && islower(*board[y][x-1]) != lowercase && tolower(*board[y][x-1]) == 'p')
                {
                    int lastIndex = documentedMoves.size()-1;
                    if(y == latestMove.y && x-1 == latestMove.x && documentedMoves[lastIndex].y == y+direction*2 && documentedMoves[lastIndex].x == x-1)
                    {
                        moves.push_back(get_pos(y+direction, x-1));
                    }
                }
            }   
        
            if(x != 7)
            {
                if(*board[y+direction][x+1] == '.' && islower(*board[y][x+1]) != lowercase && tolower(*board[y][x+1]) == 'p')
                {
                    int lastIndex = documentedMoves.size()-1;
                    if(y == latestMove.y && x+1 == latestMove.x && documentedMoves[lastIndex].y == y+direction*2 && documentedMoves[lastIndex].x == x+1)
                    {
                        moves.push_back(get_pos(y+direction, x+1));
                    }
                }
            }

            
            return moves;
        }

        std::vector<Position> rook_move(Position pos)
        {
            std::vector<Position> moves;
            int y = pos.y;
            int x = pos.x;
            auto lowercase = islower(*board[y][x]);
            // Directions to check
            bool directions[4] = {true, true, true, true};
            int directionValues[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            int cnt = 1;

            while(directions[0] || directions[1] || directions[2] || directions[3])
            {
                for(int i=0;i<4;i++)
                {
                    if(directions[i])
                    {
                        int newY = y+(directionValues[i][0]*cnt);
                        int newX = x+(directionValues[i][1]*cnt);
                        if(!out_of_bounds(newY, newX))
                        {
                            if(*board[newY][newX] == '.')
                            {
                                moves.push_back(get_pos(newY, newX));   
                            }
                            else
                            {
                                if(islower(*board[newY][newX]) != lowercase)
                                {
                                    moves.push_back(get_pos(newY, newX));
                                }

                                directions[i] = false;
                            }
                        }
                        else
                        {
                            directions[i] = false;
                        }
                    }
                }

                cnt+=1;
            }

            return moves;
        }

        std::vector<Position> knight_move(Position pos)
        {
            std::vector<Position> moves;
            int y = pos.y;
            int x = pos.x;
            auto lowercase = islower(*board[y][x]);
            
            int predefinedMoves[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

            for(int i=0;i<8;i++)
            {
                int newY = y+predefinedMoves[i][0];
                int newX = x+predefinedMoves[i][1];
                if(!out_of_bounds(newY, newX))
                {
                    if(islower(*board[newY][newX]) != lowercase || *board[newY][newX] == '.')
                    {
                        moves.push_back(get_pos(newY, newX));
                    }
                }
            }

            return moves;
        }

        std::vector<Position> bishop_move(Position pos)
        {
            std::vector<Position> moves;
            int y = pos.y;
            int x = pos.x;
            auto lowercase = islower(*board[y][x]);
            int cnt = 1;
            bool directions[4] = {true, true, true, true};
            int directionValues[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

            while(directions[0] || directions[1] || directions[2] || directions[3])
            {
                for(int i=0;i<4;i++)
                {
                    if(directions[i])
                    {
                        int newY = y+(directionValues[i][0]*cnt);
                        int newX = x+(directionValues[i][1]*cnt);
                        if(!out_of_bounds(newY, newX))
                        {
                            if(*board[newY][newX] == '.')
                            {
                                moves.push_back(get_pos(newY, newX));   
                            }
                            else
                            {
                                if(islower(*board[newY][newX]) != lowercase)
                                {
                                    moves.push_back(get_pos(newY, newX));
                                }

                                directions[i] = false;
                            }
                        }
                        else
                        {
                            directions[i] = false;
                        }
                    }
                }

                cnt+=1;
            }

            return moves;
        }

        std::vector<Position> king_move(Position pos)
        {
            std::vector<Position> moves;
            int y = pos.y;
            int x = pos.x;
            auto lowercase = islower(*board[y][x]);

            int predefinedMoves[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

            for(int i=0;i<8;i++)
            {
                int newY = y+predefinedMoves[i][0];
                int newX = x+predefinedMoves[i][1];
                if(!out_of_bounds(newY, newX))
                {
                    if(islower(*board[newY][newX]) != lowercase || *board[newY][newX] == '.')
                    {
                        moves.push_back(get_pos(newY, newX));
                    }
                }
            }

            // Check for potential castling-moves.
            bool castling = true;
            // If king has not been moved.
            if(!movedPosition(pos) && pos.x == 4)
            {
                for(int x: {0, 7})
                {
                    if(tolower(*board[pos.y][x]) == 'r' && !movedPosition(get_pos(pos.y, x)))
                    {
                        int gap = abs(4-x);
                        int direction = 1;
                        if(x < 4){ direction = -1; }

                        for(int i=1;i<gap;i++)
                        {
                            if(*board[pos.y][pos.x+i*direction] != '.')
                            {
                                castling = false;
                            }
                        }

                        if(castling)
                        {
                            moves.push_back(get_pos(pos.y, x));
                        }
                    }
                }   
            }

            return moves;
        }

        std::vector<Position> queen_move(Position pos)
        {
            std::vector<Position> moves;
            // Check for horizontal and vertical moves (rook).
            for(auto x: rook_move(pos))
            {
                moves.push_back(x);
            }
            // Check for diagonal moves (bishop).
            for(auto x: bishop_move(pos))
            {
                moves.push_back(x);
            }

            return moves;
        }


    public:
        std::vector<Position> get_moves(int y, int x)
        {
            std::vector<Position> moves;
            switch(tolower(*board[y][x]))
            {
                case 'p':
                    moves = this->pawn_move(get_pos(y, x));
                    break;
                case 'r':
                    moves = this->rook_move(get_pos(y, x));
                    break;
                case 'n':
                    moves = this->knight_move(get_pos(y, x));
                    break;
                case 'b':
                    moves = this->bishop_move(get_pos(y, x));
                    break;
                case 'q':
                    moves = this->queen_move(get_pos(y, x));
                    break;
                case 'k':
                    moves = this->king_move(get_pos(y, x));
                    break;
            }

            return moves;
        }

        void castle(Position start1, Position end1, Position start2, Position end2)
        {
            *board[end1.y][end1.x] = *board[start1.y][start1.x];
            *board[start1.y][start1.x] = '.';
            *board[end2.y][end2.x] = *board[start2.y][start2.x];
            *board[start2.y][start2.x] = '.';
        }

        void move_piece(Position start, Position end, bool documentMove = true)
        {
            // Set previousBoard values to *board values as *board's values will change.
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    previousBoard[i][j] = *board[i][j];
                }
            }

            // Check if current move is castling.
            if(tolower(*board[start.y][start.x]) == 'k' && tolower(*board[end.y][end.x]) == 'r')
            {
                // Add both start and end position to documented moves.
                if(documentMove)
                {
                    documentedMoves.push_back(start);
                    documentedMoves.push_back(end);
                }

                Position rook = end;
                Position king = start;

                // Kingside castling
                if(rook.x == 7)
                {
                    castle(rook, get_pos(rook.y, rook.x-2), king, get_pos(king.y, king.x+2));
                }
                // Queenside castling.
                else
                {
                    castle(rook, get_pos(rook.y, rook.x+3), king, get_pos(king.y, king.x-2));
                }
                
            }

            if(tolower(*board[start.y][start.x]) == 'p' && start.x != end.x && *board[end.y][end.x] == '.')
            {
                *board[end.y][end.x] = *board[start.y][start.x];
                *board[start.y][start.x] = '.';
                *board[start.y][start.x-(start.x-end.x)] = '.';
            }

            // Current move is a standard move (not castling).
            else
            {
                *board[end.y][end.x] = *board[start.y][start.x];
                *board[start.y][start.x] = '.';
                // Move start position to documented moves to be used to check castling possibility. 
                if(documentMove)
                {
                    documentedMoves.push_back(start);
                }
                latestMove = end;
            }
        }

        void undo_move()
        {
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    *board[i][j] = previousBoard[i][j];
                }
            }
        }

        bool pawnPromotion(Position pos)
        {
            if(tolower(*board[pos.y][pos.x]) == 'p')
            {
                if(pos.y == 0 || pos.y == 7)
                {
                    return true;
                }
            }

            return false;
        }

        void promotePawn(Position pos, char piece)
        {
            // If pawn promotion occurs for white make new piece uppercase (white)
            if(pos.y == 0)
            {
                piece = toupper(piece);
            }

            *board[pos.y][pos.x] = piece;
        }

        bool isCheck(bool lowercase)
        {
            bool check = false;
            Position kingPos;
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(lowercase && *board[i][j] == 'K' || !lowercase && *board[i][j] == 'k')
                    {
                        kingPos = get_pos(i, j);
                    }
                }
            } 

            for(Position pos: getPositions(lowercase))
            {
                for(Position move: get_moves(pos.y, pos.x))
                {
                    if(move.y == kingPos.y && move.x == kingPos.x)
                    {
                        check = true;
                        break;
                    }
                }

                if(check)
                {
                    break;
                }
            }

            return check;
        }

        std::vector<Position> filterMoves(Position pos, std::vector<Position> moves)
        {
            auto lowercase = islower(*board[pos.y][pos.x]);
            for(int i=0;i<moves.size();i++)
            {
                move_piece(pos, moves[i], false);
                if(isCheck(!lowercase))
                {
                    moves.erase(moves.begin() + i);
                    i-=1;
                }

                undo_move();
            }

            return moves;
        }

        bool checkMate(bool lowercase)
        {
            bool isCheckMate = false;
            if(isCheck(lowercase))
            {
                isCheckMate = true;

                // Check possible blocking or capturing moves to avoid check.
                for(Position pos: getPositions(!lowercase))
                {
                    for(Position move: get_moves(pos.y, pos.x))
                    {
                        move_piece(pos, move, false);
                        if(!isCheck(lowercase))
                        {
                            isCheckMate=false;
                        }
                        undo_move();
                    }
                }
            }

            return isCheckMate;
        }

        std::vector<Position> getPositions(bool lowercase)
        {
            std::vector<Position> availablePositions;
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(*board[i][j] != '.')
                    {
                        if(lowercase && islower(*board[i][j]) || !lowercase && !islower(*board[i][j])) 
                        {
                            availablePositions.push_back(get_pos(i, j));
                        }
                    }
                }
            }
            return availablePositions;
        }

        void printBoard()
        {
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    printf("%c ", *board[i][j]);
                }
                printf("\n");
            }
            printf("\n\n");
        } 
};