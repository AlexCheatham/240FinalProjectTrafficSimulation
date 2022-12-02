#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

//constructor
VehicleBase::VehicleBase(VehicleType type, Direction direction)
    : vehicleID(VehicleBase::vehicleCount++), 
      vehicleType(type),
      vehicleDirection(direction)
{}

//copy constructor
VehicleBase::VehicleBase(const VehicleBase& other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection)
{}

//copy assignment operator
VehicleBase& VehicleBase::operator=(const VehicleBase& other) {
  if(this == &other) {
    return *this;
  }
  this->vehicleCount = other.vehicleCount;
  this->vehicleID = other.vehicleID;
  this->vehicleType = other.vehicleType;
  this->vehicleDirection = other.vehicleDirection;
  return *this;
}

//move constructor
VehicleBase::VehicleBase(VehicleBase&& other) noexcept
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection) 
      {
        other.vehicleID = 0;
        other.vehicleType = NULLVEHICLETYPE;
        other.vehicleDirection = NULLDIRECTION;
}

//move assignment operator
VehicleBase& VehicleBase::operator=(VehicleBase&& other)noexcept {
  if(this == &other) {
    return *this;
  }
  vehicleID = other.vehicleID;
  vehicleType = other.vehicleType;
  vehicleDirection = other.vehicleDirection;

  other.vehicleID = 0;
  other.vehicleType = NULLVEHICLETYPE;
  other.vehicleDirection = NULLDIRECTION;
  return *this;
}

//destructor
VehicleBase::~VehicleBase() {

}

#endif