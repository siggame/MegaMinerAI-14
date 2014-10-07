// -*-c++-*-

#ifndef MUTATION_H
#define MUTATION_H

#include <iostream>
#include "structures.h"


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
  ///The Mutation specific id representing this mutation of Plant.
  int mutation();
  ///The spore cost to spawn this Plant mutation into the game.
  int spores();
  ///The maximum number of times the Plant can attack.
  int maxAttacks();
  ///The maximum amount of this health this Plant can have
  int maxHealth();
  ///The maximum number of moves this Plant can move.
  int maxMovement();
  ///The range of this Plant's attack.
  int range();
  ///The minimum strength of this mutation's attack/heal/buff
  int minStrength();
  ///The base strength of this mutation's attack/heal/buff
  int baseStrength();
  ///The power of this plant's attack/heal/buff
  int maxStrength();
  ///The power of this Plant mutation's attack.
  int maxStorage();

  // Actions

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Mutation ob);
};

#endif

