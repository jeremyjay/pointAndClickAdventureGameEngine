
#include "cursor.h"

Cursor::Cursor(SDL_Renderer* renderer, int _width, int _height, std::string _cursor_path, std::string _cursor_secret_path, std::string _cursor_arrow_left, std::string _cursor_arrow_right)
{

    width = _width;
    height = _height;
    cursor_path = _cursor_path;
    cursor_secret_path = _cursor_secret_path;
    cursor_arrow_left = _cursor_arrow_left;
    cursor_arrow_right = _cursor_arrow_right;

}


int Cursor::load()
{


    //load all the cursors
    // Default Cursor
    // Load the magnifying glass image
    std::cout << "loading default cursor at path: " << cursor_path << std::endl;
    cursorDefaultSurface = IMG_Load(cursor_path.c_str());
    if (!cursorDefaultSurface) {
        return 1;
    }
    // set surface size
    // Resize the image to 64x64
    cursorDefaultSurface = resizeSurface(cursorDefaultSurface, width, height);
    if (!cursorDefaultSurface) {
        return 1;
    }
    // Create a cursor texture from the surface
    cursorDefault = SDL_CreateColorCursor(cursorDefaultSurface, 0, 0);
    if (!cursorDefault) {
        return 1;
    }


    // Hover Secret Cursor
    std::cout << "loading secret cursor" << std::endl;
    cursorHoverSecretSurface = IMG_Load(cursor_secret_path.c_str());
    if (!cursorHoverSecretSurface) {
        return 1;
    }
    cursorHoverSecretSurface = resizeSurface(cursorHoverSecretSurface, width, height);
    if (!cursorHoverSecretSurface) {
        return 1;
    }
    cursorHoverSecret = SDL_CreateColorCursor(cursorHoverSecretSurface, 0, 0);
    if (!cursorHoverSecret) {
        return 1;
    }



    // Arrow Left Cursor
    std::cout << "loading left arrow cursor" << std::endl;
    cursorArrowLeftSurface = IMG_Load(cursor_arrow_left.c_str());
    if (!cursorArrowLeftSurface) {
        return 1;
    }
    cursorArrowLeftSurface = resizeSurface(cursorArrowLeftSurface, width, height);
    if (!cursorArrowLeftSurface) {
        return 1;
    }
    cursorArrowLeft = SDL_CreateColorCursor(cursorArrowLeftSurface, 0, 0);
    if (!cursorArrowLeft) {
        return 1;
    }




    // Arrow Right Cursor
    std::cout << "loading right arrow cursor" << std::endl;
    cursorArrowRightSurface = IMG_Load(cursor_arrow_right.c_str());
    if (!cursorArrowRightSurface) {
        return 1;
    }
    cursorArrowRightSurface = resizeSurface(cursorArrowRightSurface, width, height);
    if (!cursorArrowRightSurface) {
        return 1;
    }
    cursorArrowRight = SDL_CreateColorCursor(cursorArrowRightSurface, 0, 0);
    if (!cursorArrowRight) {
        return 1;
    }


  SDL_SetCursor(cursorDefault);
  return 0;

}

void Cursor::setCursor(int cursorID)
{
    SDL_Cursor *nextCursor = cursorDefault;
    switch (cursorID)
    {
        case 0:
        nextCursor = cursorDefault;
        break;

        case 1:
        nextCursor = cursorHoverSecret;
        break;

        case 2:
        nextCursor = cursorArrowLeft;
        break;

        case 3:
        nextCursor = cursorArrowRight;
        break;

        default:
        nextCursor = cursorDefault;
        break;
    }
    SDL_SetCursor(nextCursor);
}


// void Cursor::click()
// {

// }

void Cursor::cleanUp()
{
    SDL_FreeCursor(cursorDefault);
    SDL_FreeCursor(cursorHoverSecret);
    SDL_FreeCursor(cursorArrowLeft);
    SDL_FreeCursor(cursorArrowRight);

    SDL_FreeSurface(cursorDefaultSurface);
    SDL_FreeSurface(cursorHoverSecretSurface);
    SDL_FreeSurface(cursorArrowLeftSurface);
    SDL_FreeSurface(cursorArrowRightSurface);
}

