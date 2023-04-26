#ifndef BUILDER_H_
#define BUILDER_H_

#include "common.h"
#include "room.h"

class Builder
{
public:
    Builder(std::string _builderPath);

    std::string builderPath;


  std::list <Room> rooms;
  Room* currentRoom;
  Room* nextRoom = currentRoom;
};


#endif