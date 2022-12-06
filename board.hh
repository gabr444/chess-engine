#include <string>
#include <vector>

#define H 8
#define W 8

char board[8][8];

class Board
{
    public:
        std::string fen; 

        Board()
        {
            parse_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        }

        std::string get_FEN()
        {
            fen = "";
            int empty_cnt = 0;
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(board[i][j] == '.')
                    {
                        empty_cnt+=1;
                    }
                    else
                    {
                        if(empty_cnt > 0)
                        {
                            fen+=std::to_string(empty_cnt);
                            empty_cnt = 0;
                        }

                        fen+=board[i][j];
                    }
                }
                if(empty_cnt > 0)
                {
                    fen+=std::to_string(empty_cnt);
                    empty_cnt=0;
                }
                fen+='/';
            }

            fen.pop_back();

            return fen;
        }

        // FEN Input e.g: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
        void parse_FEN(std::string input_fen)
        {
            fen = input_fen;
            int idx = 0;
            int cnt = 0;
            for(int i=0;i<fen.length();i++)
            {
                if(fen[i] == '/')
                {
                    idx += 1;
                    cnt = 0;
                }
                else if(std::isdigit(fen[i]))
                {
                    int empty = (fen[i]-'0');
                    for(int j=0;j<empty;j++)
                    {
                        board[idx][cnt+j] = '.';
                    }
                    cnt+=empty;
                }

                else
                {
                    board[idx][cnt] = fen[i];
                    cnt+=1;
                }
            }
        }

        void printBoard()
        {
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    printf("%c ", board[i][j]);
                }
                printf("\n");
            }
        }
};