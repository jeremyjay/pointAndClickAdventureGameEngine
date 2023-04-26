#include "builder.h"
#include "pugixml.hpp"

Builder::Builder(std::string _builderPath)
{
    builderPath = _builderPath;
}

Builder::builderInit()
{
    pugi::xml_document doc;
    if(!doc.load_file(builderPath.c_str()))
        return -1;

    //Get a list of all the rooms
    for (pugi::xml_node room = doc.child("rooms").child("room"); room; room = room.next_sibling("room"))
    {
        int roomID = room.attribute("roomID").as_int();
        std::string roomImagePath = room.attribute("roomPath").as_string();
    }

}