#include "room.h"


Room::Room(SDL_Renderer* _renderer, int _uniqueID)
{
    renderer = _renderer;
    uniqueID = _uniqueID;
}

void Room::addObject(Object _object)
{
    objects.push_front(_object);
}

void Room::render()
{

}