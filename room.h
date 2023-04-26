#ifndef ROOM_H_
#define ROOM_H_

#include "common.h"
#include <list>
#include "object.h"

class Room
{
    
public:
    Room(SDL_Renderer* _renderer, int uniqueID, std::string imagePath);

    std::list <Object> objects;

    int load();
    void render();
    void addObject(Object _object);

    SDL_Renderer* renderer;
    int uniqueID;
    std::string imagePath;
    SDL_Surface* bkImageSurface;
    SDL_Texture * bkImageTexture;

};


#endif
