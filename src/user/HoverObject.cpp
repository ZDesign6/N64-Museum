#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "debug/debugMenu.h"
#include "debug/debugDraw.h"
namespace P64::Script::CE4BBCAA4E3707A9
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
    [[P64::Name("Max/Min Height Offset")]]
    float heightOffset = 5.0f;
    [[P64::Name("Move Speed")]]
    float moveSpeed = .5f;
    // -- SCRIPT VARS --
    //tracks if we should be ascending
    bool floatUp;
    //tracks if we should be descending
    bool floatDown;
    //the max Height that should be lerped toward. starting height + heightOffset
    float maxHeight;
    //the min Height that should be lerped towards. Starting Height - heightOffset
    float minHeight;
  );

  // The following functions are called by the engine at different points in the object's lifecycle.
  // If you don't need a specific function you can remove it.

  void init(Object& obj, Data *data)
  {
    // initialization, this is called once when the object spawns
      //set floatUp to true by default
      data->floatUp = true;
      //set floatDown to false by default
      data->floatDown = false;
      //set maxHeight to startingY + heightOffset
      data->maxHeight = obj.pos.y + data->heightOffset;
      //set minHeight to startingY - heightOffset
      data->minHeight = obj.pos.y - data->heightOffset;

  }

  void destroy(Object& obj, Data *data)
  {
    // clean-up, this is called when the object gets deleted
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    // this is called once every frame, put your main logic here

      //if floatUp is true...
      if (data->floatUp == true)
      {
          //then adjust height upwards
          obj.pos.y = obj.pos.y + data->moveSpeed;
          //then if height is greater >= maxHeight - heightTolerance
          if (obj.pos.y >= data->maxHeight)
          {
              //set floatUp to false
              data->floatUp = false;
              //and set floatDown to true
              data->floatDown = true;
          }
      }
      //else if floatDown is true...
      else if (data->floatDown == true)
      {
          //then adjust height downwards
          obj.pos.y = obj.pos.y - data->moveSpeed;
            //then if height is <= minHeight + heightTolerance
          if (obj.pos.y <= data->minHeight)
          {
              //set floatUpto true
              data->floatUp = true;
                //and set floatDown to false
              data->floatDown = false;
          }
      }
  }

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
    // this is called on the fixed physics timestep before collision/physics are stepped
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
      //prep for debug printing
      //Debug::printStart();
      ////print the running height
      //Debug::printf(100, 100, "currentHeight: %f", obj.pos.y);
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
