#include "cursor.h"
#include "room.h"
#include "object.h"
#include <list>
#include "pugixml.hpp"
#include <string>
#include "builder.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

    typedef struct 
    {
      std::string roomPath;
      int roomID;
    } roomHolder_t;

int nextRoomID = 0;
int currentRoomID = 0;
    //TODO: this will cause problems eventually
    roomHolder_t roomHolderArray[10];
    

SDL_Renderer* renderer;
Room* currentRoom;


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
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }


  Cursor mCursor(renderer, 64, 64, 
                "assets/sprites/magnifying_glass.png", 
                "assets/sprites/magnifying_glass_gold.png", 
                "assets/sprites/redArrowLeft.png", 
                "assets/sprites/redArrowRight.png");


  if (mCursor.load()) {
    std::cout << "Failed to load cursor image: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }


  // pugi::xml_document doc;
  // if(!doc.load_file("rooms/rooms.xml"))
  //   return -1;


  // Builder builder("builder.xml");

    // Builder builder("builder.xml");

    pugi::xml_document doc;
    if(!doc.load_file("assets/rooms/builder.xml"))
        return -1;

    

    int numRooms=0;
    //Get a list of all the rooms
    for (pugi::xml_node room = doc.child("rooms").child("room"); room; room = room.next_sibling("room"))
    {
      // roomHolderArray[numRooms] = malloc(sizeof(roomHolder_t));
      roomHolderArray[numRooms].roomID = room.attribute("roomID").as_int();
      roomHolderArray[numRooms].roomPath = room.attribute("roomPath").as_string();
      numRooms++;
    }


  //build room
  // Room testRoom(renderer, roomHolderArray[0].roomID, roomHolderArray[0].roomPath);
  // testRoom.load();

  // std::list <Room> rooms;
  currentRoom = new Room(renderer, roomHolderArray[0].roomID, roomHolderArray[0].roomPath);
  currentRoom->load();
  // Room* nextRoom = currentRoom;

  

  // currentRoom = &rooms.front();
  
  if (currentRoom->load()) {
    std::cout << "Failed to load room: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Main loop
  bool running = true;
  while (running) {


    if(currentRoomID != nextRoomID)
    {
      //destroy old room
      currentRoom->~Room();

      //load new room
      currentRoom = new Room(renderer, roomHolderArray[nextRoomID].roomID, roomHolderArray[nextRoomID].roomPath);
      currentRoom->load();
      currentRoomID = nextRoomID;
    }

    // currentRoom = nextRoom;
    // currentRoom = &rooms.front();
    SDL_Event event;
    int x, y;
    SDL_GetMouseState(&x, &y);
    // while (SDL_PollEvent(&event)) {
      if(SDL_WaitEvent(&event)) {
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
              mCursor.setCursor(i.cursorID);
              break;
          }
          else
          {
              mCursor.setCursor(0); /* reset to default cursor */
          }
          
        }
    }

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw room
    currentRoom->render();

    // Update the screen
    SDL_RenderPresent(renderer);
    SDL_Delay(10);

  }

  // Clean up
  mCursor.cleanUp();
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

  void goToRoom(int roomID)
  {
    std::cout << "go to roomID: " << roomID << std::endl;
    nextRoomID = roomID;
  }

  void changeCursor(int cursor)
  {
    std::cout << "we are performing a hover action here" << std::endl;

  }