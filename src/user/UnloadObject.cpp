#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "debug/debugMenu.h"
#include "debug/debugDraw.h"

namespace P64::Script::C43621A7AFC2FADF
{
  P64_DATA(
    // Put your arguments and runtime values bound to an object here.
    // If you need them to show up in the editor, add a [[P64::Name("...")]] attribute.
    //
    // Types that can be set in the editor:
    // - uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t
    // - float
    // - AssetRef<sprite_t>
    // - ObjectRef
    //
    // For unsigned integers (uint8_t/uint16_t/uint32_t) you can add a
    // [[P64::Bitmask("0=Fire, 1=Water, 2=Earth")]] attribute to edit them as a
    // named multi-select of bits instead of a plain number.
    //
    // Other types can be used but are not exposed in the editor.

    // -- EDITOR-EXPOSED VARS --

    [[P64::Name("Reference to Player Obj")]]
    ObjectRef playerRef;
    [[P64::Name("Max Viewable X Distance")]]
    float maxDifferenceX = 2000.0f;
    [[P64::Name("Max Viewable Y Distance")]]
    float maxDifferenceY = 2000.0f;
    [[P64::Name("Max Viewable Z Distance")]]
    float maxDifferenceZ = 2000.0f;
    [[P64::Name("This Obj's X Pos")]]
    float objXPos = 0.0f;
    [[P64::Name("This Obj's Y Pos")]]
    float objYPos = 0.0f;
    [[P64::Name("This Obj's Z Pos")]]
    float objZPos = 0.0f;

    // -- SCRIPT GLOBAL VARS --
  );

  // The following functions are called by the engine at different points in the object's lifecycle.
  // If you don't need a specific function you can remove it.

  void init(Object& obj, Data *data)
  {
    // initialization, this is called once when the object spawns
  }

  void destroy(Object& obj, Data *data)
  {
    // clean-up, this is called when the object gets deleted
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    // this is called once every frame, put your main logic here
  }

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
    // this is called on the fixed physics timestep before collision/physics are stepped
       //tracks if we are within the render distance. Assumed false, set true by logic. Controls visibility.
      bool withinRenderDistance = true;
      //re-calculate the difference in Z pos every frame, to avoid denormal errors
      float xDifference = data->objXPos - data->playerRef.get()->pos.x;
      float yDifference = data->objYPos - data->playerRef.get()->pos.y;
      float zDifference = data->objZPos - data->playerRef.get()->pos.z;
      // this is called once every frame, and for every active camera.
      // Put your drawing code here
      Debug::printStart();
      //printf(x, y, string w/ formatting argument, arg to format)
      Debug::printf(50, 50, "X Distance from the player: %f", xDifference);
      Debug::printf(50, 75, "Y Distance from the player: %f", yDifference);
      Debug::printf(50, 100, "Z Distance from player: %f", zDifference);

      //If object is within maxDifferenceX
      if (xDifference >= data->maxDifferenceX || xDifference <= (data->maxDifferenceX * -1))
      {
          Debug::print(50, 150, "Inside X Distance!");
          //set obj as inside of Render distance
          withinRenderDistance = false;

      }
      //If objeect is outside maxDifferenceX
      else
      {
          Debug::print(50, 150, "Exceeded X Distance!");
      }
      //If object is within maxDifferenceY
      if (yDifference >= data->maxDifferenceY || yDifference <= (data->maxDifferenceY * -1))
      {
          Debug::print(50, 175, "Within Y Distance!");
          //flag as inside render distance
          withinRenderDistance = false;
      }
      //If objeect is outside maxDifferenceY
      else
      {
          Debug::print(50, 175, "Exceeded Y Distance!");
      }
      //If object is within maxDifferenceZ
      if (zDifference >= data->maxDifferenceZ || zDifference <= (data->maxDifferenceZ * -1))
      {
          Debug::print(50, 200, "Within Z Distance!");
          //flag as inside render distance
          withinRenderDistance = false;
      }
      //If object is outside maxDifferenceZ
      else
      {
          Debug::print(50, 200, "Exceeded Z Distance!");
      }
      //RENDERING

      //if player is within any of the axes' render distances, render the object
      if (withinRenderDistance == true)
      {
          //set obj to visible
          obj.setVisible(true);
      }
      //if player is outside of all render axes, do not render the object
      else
      {
          //set obj to not visible this frame
          obj.setVisible(false);
      }
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
     
  }

  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {
    // generic events an object can receive
    switch(event.type)
    {
      case EVENT_TYPE_READY: // object is fully initialized, no update call has happened yet
      break;
      case EVENT_TYPE_ENABLE: // object got enabled
      break;
      case EVENT_TYPE_DISABLE: // object got disabled
      break;

      // you can check for your own custom types here too
    }
  }

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
    // collision callbacks, only used if any collider is attached
  }
}
