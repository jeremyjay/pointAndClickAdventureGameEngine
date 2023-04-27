#include "common.h"


SDL_Surface* resizeSurface(SDL_Surface* surface, int w, int h) {
  if (!surface) {
    return nullptr;
  }
  
  // Create a new surface with the desired width and height
  //see here if issues - https://stackoverflow.com/questions/40850196/sdl2-resize-a-surface

  SDL_Surface *newSurface = SDL_CreateRGBSurface(
      surface->flags,
      w,
      h,
      32,
      surface->format->Rmask,
      surface->format->Gmask,
      surface->format->Bmask,
      surface->format->Amask);  
  
  if (!newSurface) {
    SDL_FreeSurface(surface);
    return nullptr;
  }

  // Use SDL to resize the original surface onto the new surface
  SDL_Rect rect = { 0, 0, w, h };
  if (SDL_BlitScaled(surface, nullptr, newSurface, &rect) != 0) {
    SDL_FreeSurface(surface);
    SDL_FreeSurface(newSurface);
    return nullptr;
  }

  // Free the original surface and return the new one
  SDL_FreeSurface(surface);
  return newSurface;
}
