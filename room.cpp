#include "room.h"



Room::Room(SDL_Renderer* _renderer, int _uniqueID, std::string _imagePath)
{
    renderer = _renderer;
    uniqueID = _uniqueID;
    imagePath = _imagePath;

}

int Room::load()
{

    char charArr[imagePath.length()];

    int i=0;
    while (i < imagePath.length()) {
        charArr[i] = imagePath[i];
        i++;
    }


    // Load the background image
    // bkImageSurface = IMG_Load(charArr);
    // bkImageSurface = IMG_Load("assets/sprites/magnifying_glass_gold.png");
    bkImageSurface = IMG_Load("assets/rooms/0/tableset.png");
    if (!bkImageSurface) {
        return 1;
    }

    // resize to max window size 
    bkImageSurface = resizeSurface(bkImageSurface, 800, 600);
    if (!bkImageSurface) {
        return 1;
    }


    bkImageTexture = SDL_CreateTextureFromSurface(renderer, bkImageSurface);

    return 0;

}

void Room::addObject(Object _object)
{
    objects.push_front(_object);
}

void Room::render()
{

    // background image
    SDL_RenderCopy(renderer, bkImageTexture, NULL, NULL);


    // objects
    for(auto i : objects)
    {
      i.render();
    }
}