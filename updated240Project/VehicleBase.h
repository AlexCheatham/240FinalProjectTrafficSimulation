#ifndef __VEHICLE_BASE_H__
#define __VEHICLE_BASE_H__

// enum: see http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-enum
enum class Direction   {north, south, east, west};
enum class VehicleType {car, suv, truck};
enum class LightColor  {green, yellow, red};
Direction NULLDIRECTION;
VehicleType NULLVEHICLETYPE;

class VehicleBase
{
   public:
      static int vehicleCount;

   private:
      int         vehicleID;
      VehicleType vehicleType;
      Direction   vehicleDirection;

   public:
      VehicleBase(VehicleType type, Direction originalDirection);    //constructor
      VehicleBase(const VehicleBase& other);                         //copy constructor
      VehicleBase& operator=(const VehicleBase& other);              //copy assignment operator
      VehicleBase(VehicleBase&& other)noexcept;                      //move constructor
      VehicleBase& operator=(VehicleBase&& other)noexcept;           //move assignment operator
      ~VehicleBase();                                                //destructor

      inline int getVehicleID() const { return this->vehicleID; }

      inline VehicleType getVehicleType() const { return this->vehicleType; }
      inline Direction   getVehicleOriginalDirection() const { return this->vehicleDirection; }
};

#endif