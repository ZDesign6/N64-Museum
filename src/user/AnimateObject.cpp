#include "script/userScript.h"
#include "scene/sceneManager.h"

namespace P64::Script::CCF23405C42AEA62
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

      //HOVER
      [[P64::Name("Hover On? (0=Off, 1=On)")]]
      int32_t hoverOn = 0;
      [[P64::Name("Max/Min Hover Height Offset")]]
      float heightOffset = 5.0f;
      [[P64::Name("Hover Speed")]]
      float hoverSpeed = .5f;
      //X SCALE
      [[P64::Name("X Scaling On? (0=Off, 1=On)")]]
      int32_t xScaleOn = 0;
      [[P64::Name("Max X Scale Increase")]]
      float maxXScaleIncrease = 1.0f;
      [[P64::Name("Max X Scale Decrease")]]
      float maxXScaleDecrease = 0.0f;
      [[P64::Name("X Scaling Speed")]]
      float xScaleSpeed = .005f;
      //Y SCALE
      [[P64::Name("Y Scaling On? (0=Off, 1=On)")]]
      int32_t yScaleOn = 0;
      [[P64::Name("Max Y Scale Increase")]]
      float maxYScaleIncrease = 1.0f;
      [[P64::Name("Max Y Scale Decrease")]]
      float maxYScaleDecrease = 0.0f;
      [[P64::Name("Y Scaling Speed")]]
      float yScaleSpeed = .005f;
      //Z SCALE
      [[P64::Name("Z Scaling On? (0=Off, 1=On)")]]
      int32_t zScaleOn = 0;
      [[P64::Name("Max Z Scale Increase")]]
      float maxZScaleIncrease = 1.0f;
      [[P64::Name("Max Z Scale Decrease")]]
      float maxZScaleDecrease = 0.0f;
      [[P64::Name("Z Scaling Speed")]]
      float zScaleSpeed = .005f;
      //ROTATE X
      [[P64::Name("X Rotation On? (0=Off, 1=On)")]]
      int32_t xRotOn = 0;
      [[P64::Name("X Rotation Speed")]]
      float xRotSpeed = .05f;
      //ROTATE Y
      [[P64::Name("Y Rotation On? (0=Off, 1=On)")]]
      int32_t yRotOn = 0;
      [[P64::Name("Y Rotation Speed")]]
      float yRotSpeed = .05f;
      //ROTATE Z
      [[P64::Name("Z Rotation On? (0=Off, 1=On)")]]
      int32_t zRotOn = 0;
      [[P64::Name("Z Rotation Speed")]]
      float zRotSpeed = .05f;

      // -- SCRIPT VARS --
      
      //HOVER
      //tracks if we should be ascending
      bool hoverUp;
      //tracks if we should be descending
      bool hoverDown;
      //the max Height that should be lerped toward. starting height + heightOffset
      float maxHoverHeight;
      //the min Height that should be lerped towards. Starting Height - heightOffset
      float minHoverHeight;
      //X SCALE
      //tracks if we should be growing on X
      bool xScaleUp;
      //tracks if we should be shrinking on X
      bool xScaleDown;
      //the max scale that should be grown toward. starting height + scaleOffset
      float xMaxScale;
      //the min scale that should be grown towards. Starting Height - scaleOffset
      float xMinScale;
      //Y SCALE
      //tracks if we should be growing on Y
      bool yScaleUp;
      //tracks if we should be shrinking on Y
      bool yScaleDown;
      //the max scale that should be grown toward. starting width + scaleOffset
      float yMaxScale;
      //the min scale that should be grown towards. Starting width - scaleOffset
      float yMinScale;
      //Z SCALE
      //tracks if we should be growing on Z
      bool zScaleUp;
      //tracks if we should be shrinking on Z
      bool zScaleDown;
      //the max scale that should be grown toward. starting depth + scaleOffset
      float zMaxScale;
      //the min scale that should be grown towards. Starting depth - scaleOffset
      float zMinScale;
  );

  // The following functions are called by the engine at different points in the object's lifecycle.
  // If you don't need a specific function you can remove it.

  void init(Object& obj, Data *data)
  {
    // initialization, this is called once when the object spawns
    
    //HOVER
      //set hoverUp to true by default
      data->hoverUp = true;
      //set hoverDown to false by default
      data->hoverDown = false;
      //set maxHoverHeight to startingY + heightOffset
      data->maxHoverHeight = obj.pos.y + data->heightOffset;
      //set minHoverHeight to startingY - heightOffset
      data->minHoverHeight = obj.pos.y - data->heightOffset;
    //X SCALING
      //set xScaleUp to true by default
      data->xScaleUp = true;
      //set xScaleDown to false by default
      data->xScaleDown = false;
      //set xMaxScale to starting X Scale + maxXScaleIncrease
      data->xMaxScale = obj.scale.x + data->maxXScaleIncrease;
      //set xMinScale to starting X Scale - maxXScaleDecrease
      data->xMinScale = obj.scale.x - data->maxXScaleDecrease;
    //Y SCALING
      //set yScaleUp to true by default
      data->yScaleUp = true;
      //set yScaleDown to false by default
      data->yScaleDown = false;
      //set yMaxScale to starting Y Scale + maxYScaleIncrease
      data->yMaxScale = obj.scale.y + data->maxYScaleIncrease;
      //set yMinScale to starting Y Scale - maxYScaleDecrease
      data->yMinScale = obj.scale.y - data->maxYScaleDecrease;
    //Z SCALING
      //set zScaleUp to true by default
      data->zScaleUp = true;
      //set zScaleDown to false by default
      data->zScaleDown = false;
      //set zMaxScale to starting Y Scale + maxYScaleIncrease
      data->zMaxScale = obj.scale.z + data->maxZScaleIncrease;
      //set zMinScale to starting Y Scale - maxYScaleDecrease
      data->zMinScale = obj.scale.z - data->maxZScaleDecrease;
  }

  void destroy(Object& obj, Data *data)
  {
    // clean-up, this is called when the object gets deleted
  }

  void update(Object& obj, Data *data, float deltaTime)
  {
    // this is called once every frame, put your main logic here
  
    // -- HOVER --
    
      //if hover behavior is on...
      if (data->hoverOn == 1)
      {
          //if floatUp is true...
          if (data->hoverUp == true)
          {
              //then adjust height upwards
              obj.pos.y = obj.pos.y + data->hoverSpeed;
              //then if height is greater >= maxHeight - heightTolerance
              if (obj.pos.y >= data->maxHoverHeight)
              {
                  //set floatUp to false
                  data->hoverUp = false;
                  //and set floatDown to true
                  data->hoverDown = true;
              }
          }
          //else if floatDown is true...
          else if (data->hoverDown == true)
          {
              //then adjust height downwards
              obj.pos.y = obj.pos.y - data->hoverSpeed;
              //then if height is <= minHeight + heightTolerance
              if (obj.pos.y <= data->minHoverHeight)
              {
                  //set floatUpto true
                  data->hoverUp = true;
                  //and set floatDown to false
                  data->hoverDown = false;
              }
          }
      }

      //-- X SCALING --
      
      //if X Scaling is on...
      if (data->xScaleOn == 1)
      {
          //if xScaleUp is true...
          if (data->xScaleUp == true)
          {
              //then grow in scale
              obj.scale.x = obj.scale.x + data->xScaleSpeed;
              //then if scale is  >= xMaxScale
              if (obj.scale.x >= data->xMaxScale)
              {
                  //set xScaleUp to false
                  data->xScaleUp = false;
                  //and set xScaleDown to true
                  data->xScaleDown = true;
              }
          }
          //else if xScaleDown is true...
          else if (data->xScaleDown == true)
          {
              //then shrink in scale
              obj.scale.x = obj.scale.x - data->xScaleSpeed;
              //then if scale is <= xMinScale
              if (obj.scale.x <= data->xMinScale)
              {
                  //set floatUpto true
                  data->xScaleUp = true;
                  //and set xScaleDown to false
                  data->xScaleDown = false;
              }
          }
      }

      // -- Y SCALING --
      
      //if Y Scaling is on...
      if (data->yScaleOn == 1)
      {
          //if yScaleUp is true...
          if (data->yScaleUp == true)
          {
              //then grow in scale
              obj.scale.y = obj.scale.y + data->yScaleSpeed;
              //then if scale is  >= yMaxScale
              if (obj.scale.y >= data->yMaxScale)
              {
                  //set yScaleUp to false
                  data->yScaleUp = false;
                  //and set yScaleDown to true
                  data->yScaleDown = true;
              }
          }
          //else if yScaleDown is true...
          else if (data->yScaleDown == true)
          {
              //then shrink in scale
              obj.scale.y = obj.scale.y - data->yScaleSpeed;
              //then if scale is <= xMinScale
              if (obj.scale.y <= data->yMinScale)
              {
                  //set floatUpto true
                  data->yScaleUp = true;
                  //and set xScaleDown to false
                  data->yScaleDown = false;
              }
          }
      }

      // -- Z SCALING --
      
      //if Z Scaling is on...
      if (data->zScaleOn == 1)
      {
          //if zScaleUp is true...
          if (data->zScaleUp == true)
          {
              //then grow in scale
              obj.scale.z = obj.scale.z + data->zScaleSpeed;
              //then if scale is  >= zMaxScale
              if (obj.scale.z >= data->zMaxScale)
              {
                  //set zScaleUp to false
                  data->zScaleUp = false;
                  //and set zScaleDown to true
                  data->zScaleDown = true;
              }
          }
          //else if zScaleDown is true...
          else if (data->zScaleDown == true)
          {
              //then shrink in scale
              obj.scale.z = obj.scale.z - data->zScaleSpeed;
              //then if scale is <= xMinScale
              if (obj.scale.z <= data->zMinScale)
              {
                  //set floatUpto true
                  data->zScaleUp = true;
                  //and set xScaleDown to false
                  data->zScaleDown = false;
              }
          }
      }

      // -- X ROTATION --
      
      //if xRotOn is true...
      if (data->xRotOn == 1)
      {
          //create a measurement of the degree around which axes to rotate
          constexpr fm_vec3_t rotAxis{ 0.1f, 0.0f, 0.0f };
          //apply that rotation directly to obj by dereffing it, and modify the rotation by a factor of xRotSpeed
          fm_quat_rotate(&obj.rot, &obj.rot, &rotAxis, data->xRotSpeed);
          //normalize (why?)
          fm_quat_norm(&obj.rot, &obj.rot);
      }

      // -- Y ROTATION --
      
      //if yRotOn is true...
      if (data->yRotOn == 1)
      {
          //create a measurement of the degree around which axes to rotate
          constexpr fm_vec3_t rotAxis{ 0.0f, 0.1f, 0.0f };
          //apply that rotation directly to obj by dereffing it, and modify the rotation by a factor of xRotSpeed
          fm_quat_rotate(&obj.rot, &obj.rot, &rotAxis, data->yRotSpeed);
          //normalize (why?)
          fm_quat_norm(&obj.rot, &obj.rot);
      }

      // -- Z ROTATION --

      //if zRotOn is true...
      if (data->zRotOn == 1)
      {
          //create a measurement of the degree around which axes to rotate
          constexpr fm_vec3_t rotAxis{ 0.0f, 0.0f, 0.1f };
          //apply that rotation directly to obj by dereffing it, and modify the rotation by a factor of xRotSpeed
          fm_quat_rotate(&obj.rot, &obj.rot, &rotAxis, data->zRotSpeed);
          //normalize (why?)
          fm_quat_norm(&obj.rot, &obj.rot);
      }
      
  }

  void fixedUpdate(Object& obj, Data *data, float fixedDeltaTime)
  {
    // this is called on the fixed physics timestep before collision/physics are stepped
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    // this is called once every frame, and for every active camera.
    // Put your drawing code here
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
