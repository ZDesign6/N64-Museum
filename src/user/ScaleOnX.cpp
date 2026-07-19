#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "debug/debugMenu.h"
#include "debug/debugDraw.h"
namespace P64::Script::C0A26995DDA298E6
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
        [[P64::Name("Max X Scale Increase")]]
    float maxScaleIncrease = 1.0f;
    [[P64::Name("Max X Scale Decrease")]]
    float maxScaleDecrease = 0.0f;
    [[P64::Name("Grow Speed")]]
    float growSpeed = .005f;
    // -- SCRIPT VARS --
    //tracks if we should be ascending
    bool scaleUp;
    //tracks if we should be descending
    bool scaleDown;
    //the max Height that should be lerped toward. starting height + scaleOffset
    float maxScale;
    //the min Height that should be lerped towards. Starting Height - scaleOffset
    float minScale;
    );

    // The following functions are called by the engine at different points in the object's lifecycle.
    // If you don't need a specific function you can remove it.

    void init(Object& obj, Data* data)
    {
        // initialization, this is called once when the object spawns
          //set scaleUp to true by default
        data->scaleUp = true;
        //set scaleDown to false by default
        data->scaleDown = false;
        //set maxScale to starting X Scale + maxScaleIncrease
        data->maxScale = obj.scale.x + data->maxScaleIncrease;
        //set minScale to starting X Scale - maxScaleDecrease
        data->minScale = obj.scale.x - data->maxScaleDecrease;

    }

    void destroy(Object& obj, Data* data)
    {
        // clean-up, this is called when the object gets deleted
    }

    void update(Object& obj, Data* data, float deltaTime)
    {
        // this is called once every frame, put your main logic here

          //if scaleUp is true...
        //if (data->scaleUp == true)
        //{
        //    //then grow in scale
        //    obj.scale.x = obj.scale.x + data->growSpeed;
        //    //then if scale is  >= maxScale
        //    if (obj.scale.x >= data->maxScale)
        //    {
        //        //set scaleUp to false
        //        data->scaleUp = false;
        //        //and set scaleDown to true
        //        data->scaleDown = true;
        //    }
        //}
        ////else if scaleDown is true...
        //else if (data->scaleDown == true)
        //{
        //    //then shrink in scale
        //    obj.scale.x = obj.scale.x - data->growSpeed;
        //    //then if scale is <= minScale
        //    if (obj.scale.x <= data->minScale)
        //    {
        //        //set floatUpto true
        //        data->scaleUp = true;
        //        //and set scaleDown to false
        //        data->scaleDown = false;
        //    }
        //}
    }

    void fixedUpdate(Object& obj, Data* data, float fixedDeltaTime)
    {
        // this is called on the fixed physics timestep before collision/physics are stepped
    }

    void draw(Object& obj, Data* data, float deltaTime)
    {
        //prep for debug printing
        //Debug::printStart();
        ////print the running height
        //Debug::printf(100, 100, "currentHeight: %f", obj.pos.y);
    }

    void onEvent(Object& obj, Data* data, const ObjectEvent& event)
    {
        // generic events an object can receive
        switch (event.type)
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

    void onCollision(Object& obj, Data* data, const Coll::CollEvent& event)
    {
        // collision callbacks, only used if any collider is attached
    }
}
