#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <cstdlib>
#include "board.hh"

class Moves
{
    private:
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
            auto lowercase = islower(board[y][x]);
            int direction = 1;
            if(!lowercase)
            {
                direction = -1;
            }

            if(board[y+direction][x] == '.')
            {
                moves.push_back(get_pos(y+direction, x));
                if(board[y+direction*2][x] == '.')
                {
                    if(lowercase && y == 1 || !lowercase && y == 6)
                    {
                        moves.push_back(get_pos(y+direction*2, x));
                    }
                }
            }

            if(x != 0 && board[y+direction][x-1] != '.' && islower(board[y+direction][x-1]) != lowercase)
            {
                moves.push_back(get_pos(y+direction, x-1));
            }

            if(x != 7 && board[y+direction][x+1] != '.' && islower(board[y+direction][x+1]) != lowercase)
            {
                moves.push_back(get_pos(y+direction, x+1));
            }
            
            return moves;
        }

        std::vector<Position> rook_move(Position pos)
        {
            std::vector<Position> moves;
            int y = pos.y;
            int x = pos.x;
            auto lowercase = islower(board[y][x]);
            // Directions to check
            bool down = true;
            bool up = true;
            bool right = true;
            bool left = true;
            int cnt = 1;

            while(down || up || right || left)
            {
                if(down)
                {
                    if(!out_of_bounds(y+cnt, x))
                    {
                        if(board[y+cnt][x] == '.')
                        {
                            moves.push_back(get_pos(y+cnt, x));
                        }

                        else
                        {
                            if(islower(board[y+cnt][x]) != lowercase)
                            {
                                moves.push_back(get_pos(y+cnt, x));
                            }
                            down = false;
                        }
                    }
                    else
                    {
                        down = false;
                    }
                }
                

                if(up)
                {
                    if(!out_of_bounds(y-cnt, x))
                    {
                        if(board[y-cnt][x] == '.')
                        {
                            moves.push_back(get_pos(y-cnt, x));
                        }

                        else
                        {
                            if(islower(board[y-cnt][x]) != lowercase)
                            {
                                moves.push_back(get_pos(y-cnt, x));
                            }
                            up = false;
                        }
                    }

                    else
                    {
                        up = false;
                    }
                }

                if(right)
                {
                    if(!out_of_bounds(y, x+cnt))
                    {
                        if(board[y][x+cnt] == '.')
                        {
                            moves.push_back(get_pos(y, x+cnt));
                        }

                        else
                        {
                            if(islower(board[y][x+cnt]) != lowercase)
                            {
                                moves.push_back(get_pos(y, x+cnt));
                            }
                            right = false;
                        }
                    }
                    
                    else
                    {
                        right = false;
                    }
                }

                if(left)
                {
                    if(!out_of_bounds(y, x-cnt))
                    {
                        if(board[y][x-cnt] == '.')
                        {
                            moves.push_back(get_pos(y, x-cnt));
                        }

                        else
                        {
                            if(islower(board[y][x-cnt]) != lowercase)
                            {
                                moves.push_back(get_pos(y, x-cnt));
                            }
                            left = false;
                        }
                    }
                    
                    else
                    {
                        left = false;
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
            auto lowercase = islower(board[y][x]);

            if(!out_of_bounds(y+1, x+2))
            {
                if(islower(board[y+1][x+2]) != lowercase)
                {
                    moves.push_back(get_pos(y+1, x+2));
                }
            }

            if(!out_of_bounds(y+1, x-2))
            {
                if(islower(board[y+1][x-2]) != lowercase)
                {
                    moves.push_back(get_pos(y+1, x-2));
                }
            }
            
            
            if(!out_of_bounds(y-1, x+2))
            {
                if(islower(board[y-1][x+2]) != lowercase)
                {
                    moves.push_back(get_pos(y-1, x+2));
                }
            }
            

            if(!out_of_bounds(y-1, x-2))
            {
                if(islower(board[y-1][x-2]) != lowercase)
                {
                    moves.push_back(get_pos(y-1, x-2));
                }
            }

            if(!out_of_bounds(y+2, x+1))
            {
                if(islower(board[y+2][x+1]) != lowercase)
                {
                    moves.push_back(get_pos(y+2, x+1));
                }
            }

            if(!out_of_bounds(y+2, x-1))
            {
                if(islower(board[y+2][x-1]) != lowercase)
                {
                    moves.push_back(get_pos(y+2, x-1));
                }
            }

            if(!out_of_bounds(y-2, x+1))
            {
                if(islower(board[y-2][x+1]) != lowercase)
                {
                    moves.push_back(get_pos(y-2, x+1));
                }
            }

            if(!out_of_bounds(y-2, x-1))
            {
                if(islower(board[y-2][x-1]) != lowercase)
                {
                    moves.push_back(get_pos(y-2, x-1));
                }
            }

            return moves;
        }

        std::vector<Position> bishop_move(Position pos)
        {
            std::vector<Position> moves;
            int y = pos.y;
            int x = pos.x;
            auto lowercase = islower(board[y][x]);
            bool upRight = true;
            bool upLeft = true;
            bool downRight = true;
            bool downLeft = true;
            int cnt = 1;

            while(upRight || upLeft || downRight || downLeft)
            {
                if(upRight)
                {
                    if(!out_of_bounds(y-cnt, x+cnt))
                    {
                        if(board[y-cnt][x+cnt] == '.')
                        {
                            moves.push_back(get_pos(y-cnt, x+cnt));
                        }
                        else
                        {
                            if(islower(board[y-cnt][x+cnt]))
                            {
                                moves.push_back(get_pos(y-cnt, x+cnt));
                            }
                            upRight = false;
                        }
                    }
                    else
                    {
                        upRight = false;
                    }
                }

                if(upLeft)
                {   
                    if(!out_of_bounds(y-cnt, x-cnt))
                    {
                        if(board[y-cnt][x-cnt] == '.')
                        {
                            moves.push_back(get_pos(y-cnt, x-cnt));
                        }
                        else
                        {
                            if(islower(board[y-cnt][x-cnt]))
                            {
                                moves.push_back(get_pos(y-cnt, x-cnt));
                            }
                            upLeft = false;
                        }
                    }
                    else
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
                            moves.push_back(get_pos(y+cnt, x+cnt));
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
                            moves.push_back(get_pos(y+cnt, x-cnt));
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

        std::vector<Position> king_move(Position pos)
        {
            std::vector<Position> moves;
            int y = pos.y;
            int x = pos.x;
            auto lowercase = islower(board[y][x]);

            try
            {
                if(islower(board[y+1][x]) != lowercase)
                {
                    moves.push_back(get_pos(y+1, x));
                }
            }
            catch(...){}

            try
            {
                if(islower(board[y-1][x]) != lowercase)
                {
                    moves.push_back(get_pos(y-1, x));
                }
            }
            catch(...){}

            try
            {
                if(islower(board[y][x+1]) != lowercase)
                {
                    moves.push_back(get_pos(y, x+1));
                }
            }
            catch(...){}

            try
            {
                if(islower(board[y][x-1]) != lowercase)
                {
                    moves.push_back(get_pos(y, x-1));
                }
            }
            catch(...){}

            try
            {
                if(islower(board[y+1][x+1]) != lowercase)
                {
                    moves.push_back(get_pos(y+1, x+1));
                }
            }
            catch(...){}

            try
            {
                if(islower(board[y+1][x-1]) != lowercase)
                {
                    moves.push_back(get_pos(y+1, x-1));
                }
            }
            catch(...){}

            try
            {
                if(islower(board[y-1][x+1]) != lowercase)
                {
                    moves.push_back(get_pos(y-1, x+1));
                }
            }
            catch(...){}

            try
            {
                if(islower(board[y-1][x-1]) != lowercase)
                {
                    moves.push_back(get_pos(y-1, x-1));
                }
            }
            catch(...){}

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
            switch(tolower(board[y][x]))
            {
                case 'p':
                    moves = this->pawn_move(get_pos(y, x));
                    break;
                case 'r':
                    moves = this->rook_move(get_pos(y, x));
                    break;
                case 'n':
                    moves = this->bishop_move(get_pos(y, x));
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
};