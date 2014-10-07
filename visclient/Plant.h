// -*-c++-*-

#ifndef PLANT_H
#define PLANT_H

#include <iostream>
#include "vc_structures.h"

#include "Mappable.h"

namespace client
{


///Represents a single Plant on the map.
class Plant : public Mappable {
  public:
  Plant(_Plant* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///X position of the object
  int x();
  ///Y position of the object
  int y();
  ///The owner of this Plant.
  int owner();
  ///The mutation of this Plant. This mutation refers to list of MutationSpecifications.
  int mutation();
  ///The current amount health this Plant has remaining.
  int rads();
  ///The maximum amount of this health this Plant can have
  int maxRads();
  ///The maximum range this plant can radiate
  int range();
  ///The distance this plant has left to move
  int movementLeft();
  ///The maximum distance this plant can move each turn
  int maxMovement();
  ///The current power of this plant's radiation
  int strength();
  ///The minimum power of this plant's radiation
  int minStrength();
  ///The base power of this plant's radiation
  int baseStrength();
  ///The maximum power of this plant's radiation
  int maxStrength();
  ///The current amount of radiation this Plant can have
  int storage();
  ///The maximum amount of radiation this Plant can have
  int maxStorage();
  ///The number of spores required to spawn this unit
  int spores();

  // Actions
  ///Command to radiate (heal, attack) another Plant.
  int radiate(int x, int y);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Plant ob);
};

}

#endif

