//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Connection;
struct _Player;
struct _Mappable;
struct _Plant;
struct _Mutation;


struct _Player
{
  Connection* _c;
  int id;
  char* playerName;
  float time;
  int spores;
};
struct _Mappable
{
  Connection* _c;
  int id;
  int x;
  int y;
};
struct _Plant
{
  Connection* _c;
  int id;
  int x;
  int y;
  int owner;
  int mutation;
  int rads;
  int maxRads;
  int range;
  int movementLeft;
  int maxMovement;
  int strength;
  int minStrength;
  int baseStrength;
  int maxStrength;
  int storage;
  int maxStorage;
  int spores;
};
struct _Mutation
{
  Connection* _c;
  int id;
  char* name;
  int mutation;
  int spores;
  int maxAttacks;
  int maxHealth;
  int maxMovement;
  int range;
  int minStrength;
  int baseStrength;
  int maxStrength;
  int maxStorage;
};

#endif
