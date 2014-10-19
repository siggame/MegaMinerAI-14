//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "smartpointer.h"

namespace parser
{

const int SOAK = 0;
const int UPROOT = 1;
const int HEAL = 2;
const int ATTACK = 3;
const int GERMINATE = 4;

struct Player
{
  int id;
  char* playerName;
  float time;
  int spores;

  friend std::ostream& operator<<(std::ostream& stream, Player obj);
};

struct Mappable
{
  int id;
  int x;
  int y;

  friend std::ostream& operator<<(std::ostream& stream, Mappable obj);
};

struct Plant: public Mappable 
{
  int owner;
  int mutation;
  int rads;
  int maxRads;
  int radiatesLeft;
  int maxRadiates;
  int range;
  int uprootsLeft;
  int maxUproots;
  int strength;
  int minStrength;
  int baseStrength;
  int maxStrength;

  friend std::ostream& operator<<(std::ostream& stream, Plant obj);
};

struct Mutation
{
  int id;
  char* name;
  int type;
  int spores;
  int maxRadiates;
  int maxRads;
  int range;
  int maxUproots;
  int minStrength;
  int baseStrength;
  int maxStrength;

  friend std::ostream& operator<<(std::ostream& stream, Mutation obj);
};


struct Animation
{
  int type;
};

struct soak : public Animation
{
  int actingID;
  int targetID;

  friend std::ostream& operator<<(std::ostream& stream, soak obj);
};

struct uproot : public Animation
{
  int actingID;
  int fromX;
  int fromY;
  int toX;
  int toY;

  friend std::ostream& operator<<(std::ostream& stream, uproot obj);
};

struct heal : public Animation
{
  int actingID;
  int targetID;

  friend std::ostream& operator<<(std::ostream& stream, heal obj);
};

struct attack : public Animation
{
  int actingID;
  int targetID;

  friend std::ostream& operator<<(std::ostream& stream, attack obj);
};

struct germinate : public Animation
{
  int actingID;
  int x;
  int y;

  friend std::ostream& operator<<(std::ostream& stream, germinate obj);
};


struct AnimOwner: public Animation
{
  int owner;
};

struct GameState
{
  std::map<int,Player> players;
  std::map<int,Mappable> mappables;
  std::map<int,Plant> plants;
  std::map<int,Mutation> mutations;

  int mapWidth;
  int mapHeight;
  int turnNumber;
  int maxPlants;
  int playerID;
  int gameNumber;
  int bumbleweedSpeed;
  int poolDamage;
  int poolBuff;
  int titanDebuff;

  std::map< int, std::vector< SmartPointer< Animation > > > animations;
  friend std::ostream& operator<<(std::ostream& stream, GameState obj);
};

struct Game
{
  std::vector<GameState> states;
  std::string players[2];
  int winner;
	std::string winReason;

  Game();
};

} // parser

#endif
