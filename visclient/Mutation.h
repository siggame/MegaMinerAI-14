// -*-c++-*-

#ifndef MUTATION_H
#define MUTATION_H

#include <iostream>
#include "vc_structures.h"


namespace client
{


///Represents a mutation of Plant.
class Mutation {
  public:
  void* ptr;
  Mutation(_Mutation* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The name of this mutation of Plant.
  char* name();
  ///The mutation of this Plant. This value is unique for all Mutations.
  int type();
  ///The current amount of radiation this Plant has.
  int spores();
  ///The maximum number of times the Plant can radiate.
  int maxRadiates();
  ///The maximum amount of radiation this Plant can have before dying.
  int maxRads();
  ///The maximum range this plant can radiate.
  int range();
  ///The maximum number of times this plant can be uprooted.
  int maxUproots();
  ///The minimum power of this plant.
  int minStrength();
  ///The base power of this plant.
  int baseStrength();
  ///The maximum power of this plant.
  int maxStrength();

  // Actions

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Mutation ob);
};

}

#endif

