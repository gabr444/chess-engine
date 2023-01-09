#include "board.hh"

Square get_pos(int y, int x)
{
    Square pos = {y, x};

    return pos; 
}

Board::Board()
{
    // Parse standard fen to board.
    //k5qr/8/2n4B/p1P5/P7/8/r7/7K
    //rnbqkbnr/pppppppp/8/8/8/8/P3PPPP/RNBQKBNR
    //6k1/5ppp/ppr2q2/8/P5P1/1QNP3P/1P1BP3/3RKBNR 
    //4k3/3ppp2/8/8/8/8/8/R3Q2R 
    // r1b1k2r/1pppNppp/p2bp3/q3N3/P1Pn2P1/4P3/1P1P1P1P/R1BQKB1R
    // k5qr/8/2n4B/p1P5/P7/8/r7/7K
    parse_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

std::string Board::get_FEN()
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

    // Remove last '/' from fen.
    fen.pop_back();

    return fen;
}

// FEN Input e.g: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
void Board::parse_FEN(std::string input_fen)
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
