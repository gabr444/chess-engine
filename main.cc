#include <iostream>
#include "board.hh"
#include "moves.hh"
#include "ui.hh"
#include "engine.hh"
#include <vector>
#include <time.h>

/* 
Gymnasiearbete frågeställningar
1 - fråga - svar - 0.754000 sekunder (4) - 13.482000 sekunder (5) - 1.363000 (4) 11.18900(5) 
2 - fråga - 74.095000 sekunder - 61.430000 sekunder - 10.215000 sekunder

r . b . . r k . 
p p p . . p . p
. . . . . . . .
. P . N . . . P
P b . p . . P .
. P . . . . . .
. B . q P . . .
R . . K . B . R

3 - fråga - 15000 kombinationer/sekunden
*/ 

std::map<int, char> sidePanelMap = 
{
    {0, 'r' },
    {1, 'n' },
    {2, 'b' },
    {3, 'q' }
};

bool valueInVector(std::vector<Square> vec, Square value)
{
    for(Square x: vec)
    {
        if(x.y == value.y && x.x == value.x)
        {
            return true;
        }
    }
    
    return false;
}

int main()
{
    Board chessBoard;
    Moves moves(chessBoard.board);
    UserInterface interface(chessBoard.board);
    Engine eg(chessBoard.board);
    int round = 0;
    // Take time for both players
    clock_t start, end;
    double engineTime = 0;
    double playerTime = 0;

    // Possible screen positions when choosing piece for pawn promotion.
    std::vector<Square> sidePanelPositions {get_pos(0, 8), get_pos(1, 8), get_pos(2, 8), get_pos(3, 8)};
    while(!moves.checkMate(true) && !moves.checkMate(false))
    {
        printf("Runda %d:\n", round+1);
        // Player choice.
        if(round % 2 == 0)
        {
            // Check for stalemate.
            if(moves.staleMate(false))
            {
                std::cout << "Inga möjliga drag resulterar i stalemate!" << std::endl;
                break;
            }
            start = clock();
    
            Square pieceToMove = get_pos(-1, -1);
            while(1)
            {
                std::vector<Square> whitePositions = moves.getPositions(islower('R'));

                // Get chosen piece to move.
                if(pieceToMove.y == -1)
                {
                    pieceToMove = interface.mouseClick(whitePositions);
                }

                std::vector<Square> possible_moves = moves.filterMoves(pieceToMove, moves.get_moves(pieceToMove.y, pieceToMove.x));

                if(possible_moves.size() > 0)
                {
                    // Highlight possible moves.
                    for(Square x: possible_moves)
                    {
                        interface.highlightPosition(x.y, x.x);
                    }
                    // Get position of choice.
                    whitePositions.insert(whitePositions.end(), possible_moves.begin(), possible_moves.end());
                    Square mouse_pos = interface.mouseClick(whitePositions);
                    // If player clicks on movable square then move the piece.
                    if(valueInVector(possible_moves, mouse_pos))
                    {
                        // Update board array.
                        moves.move_piece(pieceToMove, mouse_pos);

                        // Check for eventual pawn promotion.
                        if(moves.pawnPromotion(mouse_pos))
                        {
                            interface.updateScreen();
                            Square promoted_piece = interface.mouseClick(sidePanelPositions);
                            moves.promotePawn(mouse_pos, sidePanelMap.at(promoted_piece.y));
                        }
                        end = clock();
                        playerTime+=((double)(end-start))/CLOCKS_PER_SEC;
                        printf("Total tid för spelare: %f\n", playerTime);
                        break;
                    }

                    else if(valueInVector(whitePositions, mouse_pos))
                    {
                        pieceToMove = mouse_pos;
                        interface.updateScreen();
                    }
                }
                else
                {
                    pieceToMove = interface.mouseClick(whitePositions);
                }
            }
        }
        
        else
        {
            // Check for stalemate.
            if(moves.staleMate(true))
            {
                std::cout << "Inga möjliga drag resulterar i stalemate!" << std::endl;
                break;
            }
            
            start = clock();
            std::vector<Square> best = eg.bestMove(moves, 4);
            moves.move_piece(best[0], best[1]);
            // Check for eventual pawn promotion.
            if(moves.pawnPromotion(best[1]))
            {
                moves.promotePawn(best[1], 'q');
            }
            end = clock();
            engineTime+=((double)(end-start))/CLOCKS_PER_SEC;
            printf("Total tid för bot: %f\n", engineTime);
            
            /*
            start = clock();
    
            Position pieceToMove = get_pos(-1, -1);
            while(1)
            {
                std::vector<Position> whitePositions = moves.getPositions(islower('r'));

                // Get chosen piece to move.
                if(pieceToMove.y == -1)
                {
                    pieceToMove = interface.mouseClick(whitePositions);
                }

                std::vector<Position> possible_moves = moves.filterMoves(pieceToMove, moves.get_moves(pieceToMove.y, pieceToMove.x));
                std::cout << possible_moves.size() << std::endl;

                if(possible_moves.size() > 0)
                {
                    // Highlight possible moves.
                    for(Position x: possible_moves)
                    {
                        interface.highlightPosition(x.y, x.x);
                    }
                    // Get position of choice.
                    whitePositions.insert(whitePositions.end(), possible_moves.begin(), possible_moves.end());
                    Position mouse_pos = interface.mouseClick(whitePositions);
                    // If player clicks on movable square then move the piece.
                    if(valueInVector(possible_moves, mouse_pos))
                    {
                        // Update board array.
                        moves.move_piece(pieceToMove, mouse_pos);

                        // Check for eventual pawn promotion.
                        if(moves.pawnPromotion(mouse_pos))
                        {
                            interface.updateScreen();
                            Position promoted_piece = interface.mouseClick(sidePanelPositions);
                            moves.promotePawn(mouse_pos, sidePanelMap.at(promoted_piece.y));
                        }
                        end = clock();
                        playerTime+=((double)(end-start))/CLOCKS_PER_SEC;
                        std::cout << playerTime << std::endl;
                        break;
                    }

                    else if(valueInVector(whitePositions, mouse_pos))
                    {
                        pieceToMove = mouse_pos;
                        interface.updateScreen();
                    }
                }
                else
                {
                    pieceToMove = interface.mouseClick(whitePositions);
                }
            }*/
        }

        // Redraw boxes and images.
        interface.updateScreen();

        /*chessBoard.printBoard();
        for(Position x: moves.documentedMoves)
        {
            printf("%d %d\n", x.y, x.x);
        }*/
        
        round+=1;
    }

    moves.printBoard();
    SDL_Delay(2000);
    
    if(moves.checkMate(true))
    {
        printf("Bot vinner med totala tiden %f!\n", engineTime);
    }
    if(moves.checkMate(false))
    {
        printf("Du vinner med totala tiden %f!\n", playerTime);
    }

    return 0;
}