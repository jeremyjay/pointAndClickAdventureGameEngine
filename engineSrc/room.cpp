#include "room.h"
#include "pugixml.hpp"


Room::Room(SDL_Renderer* _renderer, int _roomID, std::string _roomPath)
{
    renderer = _renderer;
    roomID = _roomID;
    roomPath = _roomPath;






}

int Room::load()
{



  pugi::xml_document doc;
  if(!doc.load_file(roomPath.c_str()))
    return -1;

  // parse xml
    pugi::xml_node room=doc.child("room");
    int roomID = room.attribute("id").as_int();
    std::cout << "room " << roomID;
    std::string roomImagePath = room.attribute("imagepath").as_string();
    //create room 0

    // objects
    for(pugi::xml_node object = room.child("object"); object; object = object.next_sibling("object"))
    {

        int objectID =  object.attribute("id").as_int();
        int x =  object.attribute("x").as_int();
        int y =  object.attribute("y").as_int();
        int w =  object.attribute("width").as_int();
        int h =  object.attribute("height").as_int();
        std::string imgPath =  object.attribute("imagepath").as_string();
        int cursorID = object.attribute("cursorID").as_int();
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
        std::cout << ", onHover: " << onHoverAction;
        std::cout << ", cursodIR: " << cursorID;



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
        else if(onClickAction.compare("goToRoom") == 0) // goToRoom
        {
            _onClickCallback = goToRoom;
            value = object.attribute("nextRoomID").as_int();
            std::cout << ", nextRoomID: " << value;
        }


        if(onHoverAction.compare("changeCursor") == 0) // changeCursor
        {
            std::cout << ", cursor: " << object.attribute("cursor").as_int();
            _onHoverCallback = changeCursor;
        }


        std::cout << ", onUseItem: " << object.attribute("onUseItem").value();



        Object mobject(x, y, w, h, imgPath, renderer, objectID, _onClickCallback, value, _onHoverCallback, cursorID);
        this->addObject(mobject);

    }
  // end::data[]

  std::cout << std::endl;










    char charArr[imagePath.length()];

    int i=0;
    while (i < imagePath.length()) {
        charArr[i] = imagePath[i];
        i++;
    }


    // Load the background image
    // bkImageSurface = IMG_Load(charArr);
    // bkImageSurface = IMG_Load("assets/sprites/magnifying_glass_gold.png");
    bkImageSurface = IMG_Load(roomImagePath.c_str());
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

Room::~Room() {
  // Destroy all objects in the list
  for (auto& obj : objects) {
    obj.~Object();
  }

  // Free the background image surface and texture
  SDL_DestroyTexture(bkImageTexture);
  SDL_FreeSurface(bkImageSurface);

}
