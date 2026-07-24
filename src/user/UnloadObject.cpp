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
    float maxDifferenceX;
    [[P64::Name("Max Viewable Y Distance")]]
    float maxDifferenceY;
    [[P64::Name("Max Viewable Z Distance")]]
    float maxDifferenceZ;

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
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
      //re-calculate the difference in Z pos every frame, to avoid denormal errors
      float xDifference = obj.pos.x - data->playerRef.get()->pos.x;
      float yDifference = obj.pos.y - data->playerRef.get()->pos.y;
      float zDifference = obj.pos.z - data->playerRef.get()->pos.z;
    // this is called once every frame, and for every active camera.
    // Put your drawing code here
      Debug::printStart();
      //printf(x, y, string w/ formatting argument, arg to format)
      Debug::printf(50,50,"X Distance from the player: %f", xDifference);
      Debug::printf(50, 75, "Y Distance from the player: %f", yDifference);
      //Debug::printf(50, 100, "Z Distance from player: %f", obj.pos.z - data->playerRef.get()->pos.z);
      Debug::printf(50, 100, "Z Distance from player: %f", zDifference);

      //If object is beyond maxDifferenceX
      if (xDifference >= data->maxDifferenceX || xDifference <= (data->maxDifferenceX * -1))
      {
          Debug::print(50, 150, "Exceeded X Distance!");

      }
      //If object is beyond maxDifferenceY
      if (yDifference >= data->maxDifferenceY || yDifference <= (data->maxDifferenceY * -1))
      {
          Debug::print(50, 175, "Exceeded Y Distance!");
      }
      //If object is beyond maxDifferenceZ
      if (zDifference >= data->maxDifferenceZ || zDifference <= (data->maxDifferenceZ * -1))
      {
          Debug::print(50, 200, "Exceeded Z Distance!");
      }

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
