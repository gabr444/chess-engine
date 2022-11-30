#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <cstdlib>

class Moves
{
    char **board;


    Moves(char **pointerBoard)
    {
        board = pointerBoard;
    }

    private:
        bool is_out_of_bounds(int y, int x)
        {
            bool out_of_bounds = false;
            if(y > 7 || y < 0 || x > 7 || x < 0)
            {
                out_of_bounds = true;
            }
        }

    public:
        std::vector<std::tuple<int, int>> pawn_move(std::tuple<int, int> pos)
            {
                std::vector<std::tuple<int, int>> moves;
                bool lowercase = islower(board[std::get<0>(pos)][std::get<1>(pos)]);
                int y = std::get<0>(pos);
                int x = std::get<1>(pos);
                int direction = 1;
                if(!lowercase)
                {
                    direction = -1;
                }

                if(board[y+direction][x] == '.')
                {
                    moves.push_back(std::tuple<int, int>(y+direction, x));
                    if(board[y+direction*2][x] == '.')
                    {
                        if(!lowercase && y == 1 || lowercase && y == 7)
                        {
                            moves.push_back(std::tuple<int, int>(y+direction*2, x));
                        }
                    }
                }

                if(x != 0 && board[y+direction][x-1] != '.' && islower(board[y+direction][x-1]) != lowercase)
                {
                    moves.push_back(std::tuple<int, int>(y+direction, x-1));
                }

                if(x != 7 && board[y+direction][x+1] != '.' && islower(board[y+direction][x+1]) != lowercase)
                {
                    moves.push_back(std::tuple<int, int>(y+direction, x+1));
                }
                
                return moves;
            }

            std::vector<std::tuple<int, int>> rook_move(std::tuple<int, int> pos)
            {
                std::vector<std::tuple<int, int>> moves;
                bool lowercase = islower(board[std::get<0>(pos)][std::get<1>(pos)]);
                int y = std::get<0>(pos);
                int x = std::get<1>(pos);
                // Directions to check
                bool down = true;
                bool up = true;
                bool right = true;
                bool left = true;
                bool cnt = 1;

                while(down && up && right && left)
                {
                    if(down)
                    {
                        try
                        {
                            if(board[y+1][x] == '.')
                            {
                                moves.push_back(std::tuple<int, int>(y+1, x));
                            }

                            if(islower(board[y+1][x]) != lowercase)
                            {
                                moves.push_back(std::tuple<int, int>(y+1, x));
                                throw;
                            }
                        }

                        catch(...)
                        {
                            down = false;
                        }
                    }

                    if(up)
                    {
                        try
                        {
                            if(board[y-1][x] == '.')
                            {
                                moves.push_back(std::tuple<int, int>(y-1, x));
                            }

                            if(islower(board[y-1][x]) != lowercase)
                            {
                                moves.push_back(std::tuple<int, int>(y-1, x));
                                throw;
                            }
                        }
                        
                        catch(...)
                        {
                            up = false;
                        }
                    }

                    if(right)
                    {
                        try
                        {
                            if(board[y][x+1] == '.')
                            {
                                moves.push_back(std::tuple<int, int>(y, x+1));
                            }

                            if(islower(board[y][x+1]) != lowercase)
                            {
                                moves.push_back(std::tuple<int, int>(y, x+1));
                                throw;
                            }
                        }
                        
                        catch(...)
                        {
                            right = false;
                        }
                    }

                    if(left)
                    {
                        try
                        {
                            if(board[y][x-1] == '.')
                            {
                                moves.push_back(std::tuple<int, int>(y, x-1));
                            }

                            if(islower(board[y][x-1]) != lowercase)
                            {
                                moves.push_back(std::tuple<int, int>(y, x-1));
                                throw;
                            }
                        }
                        
                        catch(...)
                        {
                            left = false;
                        }
                    }

                    cnt+=1;
                }

                return moves;
            }

            std::vector<std::tuple<int, int>> knight_move(std::tuple<int, int> pos)
            {
                std::vector<std::tuple<int, int>> moves;
                bool lowercase = islower(board[std::get<0>(pos)][std::get<1>(pos)]);
                int y = std::get<0>(pos);
                int x = std::get<1>(pos);

                try
                {
                    if(islower(board[y+1][x+2]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y+1, x+2));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y+1][x-2]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y+1, x-2));
                    }
                }
                catch(...){}
                
                try
                {
                    if(islower(board[y-1][x+2]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y-1, x+2));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y-1][x-2]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y-1, x-2));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y+2][x+1]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y+2, x+1));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y+2][x-1]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y+2, x-1));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y-2][x+1]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y-2, x+1));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y-2][x-1]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y-2, x-1));
                    }
                }
                catch(...){}

                return moves;
            }

            std::vector<std::tuple<int, int>> bishop_move(std::tuple<int, int> pos)
            {
                std::vector<std::tuple<int, int>> moves;
                bool lowercase = islower(board[std::get<0>(pos)][std::get<1>(pos)]);
                int y = std::get<0>(pos);
                int x = std::get<1>(pos);
                bool upRight = true;
                bool upLeft = true;
                bool downRight = true;
                bool downLeft = true;
                int cnt = 1;

                while(upRight && upLeft && downRight && downLeft)
                {
                    if(upRight)
                    {
                        try
                        {
                            if(islower(board[y-cnt][x+cnt]) != lowercase)
                            {
                                moves.push_back(std::tuple<int, int>(y-cnt, x+cnt));
                            }
                        }
                        catch(...)
                        {
                            upRight = false;
                        }
                    }

                    if(upLeft)
                    {
                        try
                        {
                            if(islower(board[y-cnt][x-cnt]) != lowercase)
                            {
                                moves.push_back(std::tuple<int, int>(y-cnt, x-cnt));
                            }
                        }
                        catch(...)
                        {
                            upLeft = false;
                        }
                    }

                    if(downRight)
                    {
                        try
                        {
                            if(islower(board[y+cnt][x+cnt]) != lowercase)
                            {
                                moves.push_back(std::tuple<int, int>(y+cnt, x+cnt));
                            }
                        }
                        catch(...)
                        {
                            downRight = false;
                        }
                    }

                    if(downLeft)
                    {
                        try
                        {
                            if(islower(board[y+cnt][x-cnt]) != lowercase)
                            {
                                moves.push_back(std::tuple<int, int>(y+cnt, x-cnt));
                            }
                        }
                        catch(...)
                        {
                            downLeft = false;
                        }
                    }

                    cnt+=1;
                }

                return moves;
            }

            std::vector<std::tuple<int, int>> king_move(std::tuple<int, int> pos)
            {
                std::vector<std::tuple<int, int>> moves;
                bool lowercase = islower(board[std::get<0>(pos)][std::get<1>(pos)]);
                int y = std::get<0>(pos);
                int x = std::get<1>(pos);

                try
                {
                    if(islower(board[y+1][x]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y+1, x));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y-1][x]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y-1, x));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y][x+1]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y, x+1));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y][x-1]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y, x-1));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y+1][x+1]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y+1, x+1));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y+1][x-1]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y+1, x-1));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y-1][x+1]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y-1, x+1));
                    }
                }
                catch(...){}

                try
                {
                    if(islower(board[y-1][x-1]) != lowercase)
                    {
                        moves.push_back(std::tuple<int, int>(y-1, x-1));
                    }
                }
                catch(...){}

                return moves;
            }

            std::vector<std::tuple<int, int>> queen_move(std::tuple<int, int> pos)
            {
                std::vector<std::tuple<int, int>> moves;
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
};