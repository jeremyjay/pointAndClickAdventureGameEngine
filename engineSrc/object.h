#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>
#include "common.h"

class Object
{
public:
    Object(int _x, int _y, int _width, int _height, std::string _img_source, 
                SDL_Renderer* _renderer, int _uniqueID, void (*_onClickCallback)(int value), int _value,
                void (*_onHoverCallback)(int value), int _cursorID);


    void onClick();
    void onHover();
    void onUseItem();
    int isCursorInBounds(int cursor_x, int cursor_y);
    int render();

    int x;
    int y;
    int width;
    int height;
    char *img_source;
    void (*onClickCallback)(int value);
    int value;

    int cursorID;
    void (*onHoverCallback)(int value);
    

    SDL_Renderer* renderer;
    int uniqueID;
};



#endif