#ifndef CURSOR_H_
#define CURSOR_H_

#include <string>
#include "common.h"


class Cursor {
public:
    Cursor(SDL_Renderer* renderer, int _width, int _height, std::string _cursor_path, std::string _cursor_secret_path, std::string _cursor_arrow_left, std::string _cursor_arrow_right);


    SDL_Cursor * getCursorFromID(int cursorID);
    
    int load();

    void setCursor(int cursorID);

    void cleanUp();

    int width;
    int height;
    
    std::string cursor_path;
    std::string cursor_secret_path;
    std::string cursor_arrow_left;
    std::string cursor_arrow_right;


    SDL_Cursor *cursorDefault;
    SDL_Cursor *cursorHoverSecret;
    SDL_Cursor *cursorArrowLeft;
    SDL_Cursor *cursorArrowRight;

    SDL_Surface *cursorDefaultSurface;
    SDL_Surface *cursorHoverSecretSurface;
    SDL_Surface *cursorArrowLeftSurface;
    SDL_Surface *cursorArrowRightSurface;


};

#endif