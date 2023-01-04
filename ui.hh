#include <string>
#include <map>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

// Window resolution
#define W 900
#define H 800

#define BOX_SIZE H/8

#define IMG_FOLDER "media/"

// Map with image name for each piece!
std::map<char, std::string> imageMap = 
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

        UserInterface(char arr[8][8])
        {
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    board[i][j] = &arr[i][j];
                }
            }
            
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            this->updateScreen();
        }

        void drawBoxes()
        {
            SDL_Rect r;
            int cnt=0;
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<9;j++)
                {   
                    r.x = BOX_SIZE*j;
                    r.y = BOX_SIZE*i;
                    r.w = BOX_SIZE;
                    r.h = BOX_SIZE;

                    if((j+cnt) % 2 == 0)
                    {
                        SDL_SetRenderDrawColor( renderer, 139, 69, 19, 255 );
                    }
                    else
                    {
                        SDL_SetRenderDrawColor( renderer, 245, 222, 179, 255 );
                    }

                    // Render rect
                    SDL_RenderFillRect(renderer, &r );
                }
                cnt+=1;
            }
            // Render the rect to the screen
            SDL_RenderPresent(renderer);
        }

        void loadImages()
        {
            SDL_Texture *img;
            SDL_Rect r; 
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {   
                    if(*board[i][j] != '.')
                    {
                        r.x = BOX_SIZE*j;
                        r.y = BOX_SIZE*i;
                        r.w = BOX_SIZE;
                        r.h = BOX_SIZE;
                        std::string src = IMG_FOLDER+imageMap.at(*board[i][j])+".png";
                        char charSrc[src.length()];
                        strcpy(charSrc, src.c_str());
                        img = IMG_LoadTexture(renderer, charSrc);
                        SDL_RenderCopy(renderer, img, NULL, &r);
                    }
                }
                // Render rect
                SDL_RenderPresent(renderer);
            }
        }

        void drawPanelBoxes()
        {
            SDL_Rect r;
            int cnt=0;
            for(int i=0;i<8;i++)
            {   
                r.x = BOX_SIZE*8;
                r.y = BOX_SIZE*i;
                r.w = BOX_SIZE;
                r.h = BOX_SIZE;

                if(i < 4)
                {
                    SDL_SetRenderDrawColor( renderer, 147, 112, 219, 255);
                }
                else
                {
                    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                }

                // Render rect
                SDL_RenderFillRect(renderer, &r );
            }
            // Render the rect to the screen
            SDL_RenderPresent(renderer);
        }

        void loadPanelImages()
        {
            SDL_Texture *img;
            SDL_Rect r; 

            std::string panelPieces[] = {"wr", "wn", "wb", "wq"};

            for(int i=0;i<4;i++)
            {
                r.x = BOX_SIZE*8;
                r.y = BOX_SIZE*i;
                r.w = BOX_SIZE;
                r.h = BOX_SIZE;
                std::string src = IMG_FOLDER+panelPieces[i]+".png";
                char charSrc[src.length()];
                strcpy(charSrc, src.c_str());
                img = IMG_LoadTexture(renderer, charSrc);
                SDL_RenderCopy(renderer, img, NULL, &r);
            }
            
            // Render rect
            SDL_RenderPresent(renderer);
        }

        void highlightPosition(int y, int x)
        {
            SDL_Rect r{x*BOX_SIZE, y*BOX_SIZE, BOX_SIZE, BOX_SIZE};
            SDL_SetRenderDrawColor( renderer, BOX_SIZE, 150, 0, 0 );
            SDL_RenderFillRect(renderer, &r );
            SDL_RenderPresent(renderer);
            // Since SDL rendering overlaps the images we load the images again.
            loadImages();
        }

        void quit()
        {
            SDL_DestroyWindow(screen);
            SDL_Quit();
        }

        Position mouseClick(std::vector<Position> positions)
        {
            int mouse_x, mouse_y;
            Position mouse_pos;
            bool clicked = false;
            while(1)
            {
                if(SDL_PollEvent(&event))
                {
                    if(SDL_MOUSEMOTION == event.type)
                    {
                        SDL_GetMouseState(&mouse_x, &mouse_y);
                    }

                    for(auto pos: positions)
                    {
                        if(mouse_y < pos.y*BOX_SIZE+100 && mouse_y > pos.y*BOX_SIZE && mouse_x < pos.x*BOX_SIZE+100 && mouse_x > pos.x*BOX_SIZE)
                        {
                            if(SDL_MOUSEBUTTONDOWN == event.type)
                            {
                                if(SDL_BUTTON_LEFT == event.button.button)
                                {
                                    mouse_pos = pos;
                                    clicked = true;
                                }
                            }
                        }
                    }

                    if(clicked)
                    {
                        break;
                    }
                }
            }

            return mouse_pos;
        }

        void updateScreen()
        {
            this->drawBoxes();
            this->drawPanelBoxes();
            this->loadImages();
            this->loadPanelImages();
        }
};