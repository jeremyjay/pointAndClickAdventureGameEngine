#ifndef COMMON_H_
#define COMMON_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


void setRoom(int roomID);
void getItem(int item);
void startDialogue(int dialogue);
void goToRoom(int roomID);
void changeCursor(int cursor);

SDL_Surface* resizeSurface(SDL_Surface* surface, int w, int h);




#endif