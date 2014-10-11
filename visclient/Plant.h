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
  ///The current amount of radiation this Plant has.
  int rads();
  ///The maximum amount of radiation this Plant can have before dying.
  int maxRads();
  ///The remaining number of times the plant can radiate.
  int radiatesLeft();
  ///The maximum number of times the plant can radiate.
  int maxRadiates();
  ///The maximum range this plant can radiate.
  int range();
  ///The remaining number of times this plant can be uprooted.
  int uprootsLeft();
  ///The maximum number of times this plant can be uprooted.
  int maxUproots();
  ///The current power of this plant.
  int strength();
  ///The minimum power of this plant.
  int minStrength();
  ///The base power of this plant.
  int baseStrength();
  ///The maximum power of this plant.
  int maxStrength();

  // Actions
  ///Allows a plant to display messages on the screen
  int talk(char* message);
  ///Command to radiate (heal, attack) another Plant.
  int radiate(int x, int y);
  ///Command to uproot a plant and move to a new location.
  int uproot(int x, int y);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Plant ob);
};

}

#endif

