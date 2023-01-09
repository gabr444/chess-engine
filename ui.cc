#include "ui.hh"

UserInterface::UserInterface(char arr[8][8])
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

void UserInterface::drawBoxes()
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
                SDL_SetRenderDrawColor( renderer, SQ_COLOR1 );
            }
            else
            {
                SDL_SetRenderDrawColor( renderer, SQ_COLOR2 );
            }

            // Render rect
            SDL_RenderFillRect(renderer, &r );
        }
        cnt+=1;
    }
    // Render the rect to the screen
    SDL_RenderPresent(renderer);
}

void UserInterface::loadImages()
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

void UserInterface::drawPanelBoxes()
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
            SDL_SetRenderDrawColor( renderer, SQ_COLOR2);
        }
        else
        {
            SDL_SetRenderDrawColor( renderer, SQ_COLOR1);
        }

        // Render rect
        SDL_RenderFillRect(renderer, &r );
    }
    // Render the rect to the screen
    SDL_RenderPresent(renderer);
}

void UserInterface::loadPanelImages()
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

void UserInterface::highlightPosition(int y, int x)
{
    SDL_Rect r{x*BOX_SIZE, y*BOX_SIZE, BOX_SIZE, BOX_SIZE};
    SDL_SetRenderDrawColor( renderer, SQ_HIGHLIGHTCOLOR );
    SDL_RenderFillRect(renderer, &r );
    SDL_RenderPresent(renderer);
    // Since SDL rendering overlaps the images we load the images again.
    loadImages();
}

void UserInterface::quit()
{
    SDL_DestroyWindow(screen);
    SDL_Quit();
}

Square UserInterface::mouseClick(std::vector<Square> positions)
{
    int mouse_x, mouse_y;
    Square mouse_pos;
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

void UserInterface::updateScreen()
{
    this->drawBoxes();
    this->drawPanelBoxes();
    this->loadImages();
    this->loadPanelImages();
}