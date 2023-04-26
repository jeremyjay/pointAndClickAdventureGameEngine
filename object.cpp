
#include "object.h"
#include "stdio.h"


Object::Object(int _x, int _y, int _width, int _height, std::string _img_source, 
                SDL_Renderer* _renderer, int _uniqueID, void (*_onClickCallback)(int value), int _value,
                void (*_onHoverCallback)(int value), int _cursorID)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    // img_source = _img_source;
    renderer = _renderer;
    uniqueID = _uniqueID;
    onClickCallback = _onClickCallback;
    value = _value;
    onHoverCallback = _onHoverCallback;
    cursorID = _cursorID;
}

void Object::onClick()
{
    // std::cout << "Object clicked - Unique ID is: " << uniqueID << std::endl;
    onClickCallback(value);

    /*TODO: Remove Object from room?*/
}

void Object::onHover()
{
    // std::cout << "Object hovered - Unique ID is: " << uniqueID << std::endl;
    onHoverCallback(value);
}

void Object::onUseItem()
{
    std::cout << "item used on object - you should probably override this function" << std::endl;
}

int Object::isCursorInBounds(int cursor_x, int cursor_y)
{
    int ret = 0;
    if (cursor_x > x && cursor_x < x+width && cursor_y > y && cursor_y < y+height) {
        ret = 1;
    }
    return ret;
}

int Object::render()
{
    int ret = 0;

    SDL_Rect objectRect = { x, y, width, height };
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    // SDL_RenderFillRect(renderer, &objectRect);

    return ret;
}

