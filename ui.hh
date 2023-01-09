#include <string>
#include <map>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "board.hh"

#ifndef UI_HH_INCLUDED
#define UI_HH_INCLUDED

// Window resolution
#define W 900
#define H 800

#define BOX_SIZE H/8

#define SQ_COLOR1 65, 105, 225, 255
#define SQ_COLOR2 245, 222, 179, 255

// Yellow highlight color
#define SQ_HIGHLIGHTCOLOR 255, 255, 0, 255

#define IMG_FOLDER "media/"

// Map with image name for each piece!
const std::map<char, std::string> imageMap = 
{
    { 'p', "bp" },
    { 'r', "br" },
    { 'n', "bn" },
    { 'b', "bb" },
    { 'k', "bk" },
    { 'q', "bq" },
    { 'P', "wp" },
    { 'R', "wr" },
    { 'N', "wn" },
    { 'B', "wb" },
    { 'K', "wk" },
    { 'Q', "wq" }
};

class UserInterface
{
    public:
        char *board[8][8];
        SDL_Window *screen = SDL_CreateWindow("Chess engine",
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    W, H,
                    0);

        SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);

        SDL_Event event;

        UserInterface(char arr[8][8]);

        void drawBoxes();
    
        void loadImages();

        void drawPanelBoxes();

        void loadPanelImages();
        
        void highlightPosition(int y, int x);

        void quit();

        Square mouseClick(std::vector<Square> positions);

        void updateScreen();
};

#endif