#ifndef ROOM_H_
#define ROOM_H_

#include <SDL2/SDL.h>
#include <list>
#include "object.h"

class Room
{
    
public:
    Room(SDL_Renderer* _renderer, int uniqueID);

    std::list <Object> objects;

    void render();
    void addObject(Object _object);

    SDL_Renderer* renderer;
    int uniqueID;

};


#endif
