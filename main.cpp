#include <SDL2/SDL.h>
#include <iostream>
#include "room.h"
#include "object.h"
#include <list>
#include "pugixml.hpp"
#include <string>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int nextRoomID = 0;

void setRoom(int roomID);
void getItem(int item);
void startDialogue(int dialogue);
void changeCursor(int cursor);

int main(int argc, char* argv[]) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Create a window
  SDL_Window* window = SDL_CreateWindow("Point and Click Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  // Create a renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Load the magnifying glass image
  SDL_Surface* cursorSurface = SDL_LoadBMP("assets/sprites/magnifying_glass.bmp");
  if (!cursorSurface) {
    std::cout << "Failed to load cursor image: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }


  // Load the magnifying glass image
  SDL_Surface* cursor2Surface = SDL_LoadBMP("assets/sprites/magnifying_glass_gold.bmp");
  if (!cursor2Surface) {
    std::cout << "Failed to load cursor image: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // set surface size


  // Create a cursor texture from the surface
  SDL_Cursor *cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
  if (!cursor) {
    std::cout << "Failed to create cursor texture: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Create a cursor texture from the surface
  SDL_Cursor *cursor2 = SDL_CreateColorCursor(cursor2Surface, 0, 0);
  if (!cursor2) {
    std::cout << "Failed to create cursor texture: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_SetCursor(cursor);



  pugi::xml_document doc;
  if(!doc.load_file("rooms/rooms.xml"))
    return -1;




  std::list <Room> rooms;
  Room* currentRoom;
  Room* nextRoom = currentRoom;

  // rooms
  for (pugi::xml_node room = doc.child("roomList").child("room"); room; room = room.next_sibling("room"))
  {

      int roomID = room.attribute("id").as_int();
      std::cout << "room " << roomID;
      //create room 0
      currentRoom = new Room(renderer, roomID);

      // objects
      for(pugi::xml_node object = room.child("object"); object; object = object.next_sibling("object"))
      {

        int objectID =  object.attribute("id").as_int();
        int x =  object.attribute("x").as_int();
        int y =  object.attribute("y").as_int();
        int w =  object.attribute("width").as_int();
        int h =  object.attribute("height").as_int();
        std::string imgPath =  object.attribute("imagepath").as_string();
        void (*_onClickCallback)(int value);
        void (*_onHoverCallback)(int value);
        // void (*_onClickCallback)(int value);
        int value;
        std::string onClickAction = object.attribute("onClick").as_string();
        std::string onHoverAction = object.attribute("onHover").as_string();

        std::cout << std::endl;
        std::cout << "object: " << objectID;
        std::cout << ", x: " << x;
        std::cout << ", y: " << y;
        std::cout << ", width: " << w;
        std::cout << ", height: " << h;
        std::cout << ", imagePath: " << imgPath;
        std::cout << ", onClick: " << onClickAction;
        std::cout << ", onClick: " << onHoverAction;

        if(onClickAction.compare("getItem") == 0) // getItem
        {
          _onClickCallback = getItem;
          value = object.attribute("item").as_int();
          std::cout << ", item: " << value;
        }
        else if(onClickAction.compare("startDialogue") == 0) // startDialogue
        {
          _onClickCallback = startDialogue;
          std::cout << ", dialogue: " << object.attribute("dialogue").as_string();
        }
        
        
        if(onHoverAction.compare("changeCursor") == 0) // changeCursor
        {
          std::cout << ", cursor: " << object.attribute("cursor").as_int();
          _onHoverCallback = changeCursor;
        }


        std::cout << ", onUseItem: " << object.attribute("onUseItem").value();
        

       
        Object mobject(x, y, w, h, imgPath, renderer, objectID, _onClickCallback, value, _onHoverCallback);
        currentRoom->addObject(mobject);
        rooms.push_front(*currentRoom);

      }

  }
  // end::data[]

  std::cout << std::endl;







  // //create objects
  // Object secret1(100, 100, 100, 100, "does not do anything at the moment", renderer, 0, getItem, 1);
  // Object secret2(250, 250, 100, 100, "does not do anything at the moment", renderer, 1, setRoom, 1);
  // room->addObject(secret1);
  // room->addObject(secret2);



  // //create room 1
  // Room room1(renderer, 1);
  // //create objects
  // Object room1secret1(0, 100, 100, 100, "does not do anything at the moment", renderer, 2, getItem, 0);
  // Object room1secret2(300, 100, 100, 100, "does not do anything at the moment", renderer, 3, setRoom, 0);
  // room1.addObject(room1secret1);
  // room1.addObject(room1secret2);


  // Room currentRoom = room;
  // Room nextRoom = currentRoom;


  // Main loop
  bool running = true;
  while (running) {
    // currentRoom = nextRoom;
    currentRoom = &rooms.front();
    SDL_Event event;
    int x, y;
    SDL_GetMouseState(&x, &y);
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {

            // Check if the click was on an object
            for(auto i : currentRoom->objects)
            {
              if(i.isCursorInBounds(x,y))
              {
                i.onClick();
              }

            }
        }

        for(auto i : currentRoom->objects)
        {
          if(i.isCursorInBounds(x,y)) {
              i.onHover();
              SDL_SetCursor(cursor2);
              break;
          }
          else
          {
              SDL_SetCursor(cursor);
          }
          
        }
    }

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw objects
    for(auto i : currentRoom->objects)
    {
      i.render();
    }

    // Update the screen
    SDL_RenderPresent(renderer);
  }

  // Clean up
  SDL_FreeCursor(cursor);
  SDL_FreeSurface(cursorSurface);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}




  void setRoom(int roomID)
  {
    nextRoomID = roomID;
    std::cout << "setting room to: " << nextRoomID << std::endl;
  }

  void getItem(int item)
  {
    std::cout << "you got item: " << item << std::endl;
  }

  void startDialogue(int dialogue)
  {
    std::cout << "starting Dialogue: " << dialogue << std::endl;
  }

  void changeCursor(int cursor)
  {
    std::cout << "we are performing a hover action here" << std::endl;
  }