#include "interactiveObject.h"

void OnClickExample(InteractiveObject &object)
{
    std::cout << "Object with ID " << object.GetId() << " clicked!" << std::endl;
}

void OnHoverExample(InteractiveObject &object)
{
    std::cout << "Object with ID " << object.GetId() << " hovered!" << std::endl;
}

void OnUseItemExample(InteractiveObject &object)
{
    std::cout << "Used item on object with ID " << object.GetId() << std::endl;
}

int interactiveObjectTest()
{
    InteractiveObject exampleObject(
        1,                           // ID
        "path/to/image.png",         // Image path
        50, 50,                      // x, y coordinates
        100, 100,                    // Width, height
        0,                           // Cursor ID
        OnClickExample,              // onClick callback
        OnHoverExample,              // onHover callback
        OnUseItemExample             // onUseItem callback
    );

    // Test the callbacks
    exampleObject.Click();
    exampleObject.Hover();
    exampleObject.UseItem();

    return 0;
}
