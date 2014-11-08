//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include "BaseAI.h"
#include "game.h"

int BaseAI::mapWidth()
{
  return getMapWidth(c);
}
int BaseAI::mapHeight()
{
  return getMapHeight(c);
}
int BaseAI::turnNumber()
{
  return getTurnNumber(c);
}
int BaseAI::maxPlants()
{
  return getMaxPlants(c);
}
int BaseAI::playerID()
{
  return getPlayerID(c);
}
int BaseAI::gameNumber()
{
  return getGameNumber(c);
}
int BaseAI::bumbleweedSpeed()
{
  return getBumbleweedSpeed(c);
}
int BaseAI::poolDamage()
{
  return getPoolDamage(c);
}
int BaseAI::poolBuff()
{
  return getPoolBuff(c);
}
int BaseAI::sporeRate()
{
  return getSporeRate(c);
}
int BaseAI::maxSpores()
{
  return getMaxSpores(c);
}
int BaseAI::uprootRange()
{
  return getUprootRange(c);
}

bool BaseAI::startTurn()
{
  static bool initialized = false;
  int count = 0;
  count = getPlayerCount(c);
  players.clear();
  players.resize(count);
  for(int i = 0; i < count; i++)
  {
    players[i] = Player(getPlayer(c, i));
  }

  count = getMappableCount(c);
  mappables.clear();
  mappables.resize(count);
  for(int i = 0; i < count; i++)
  {
    mappables[i] = Mappable(getMappable(c, i));
  }

  count = getPlantCount(c);
  plants.clear();
  plants.resize(count);
  for(int i = 0; i < count; i++)
  {
    plants[i] = Plant(getPlant(c, i));
  }

  count = getMutationCount(c);
  mutations.clear();
  mutations.resize(count);
  for(int i = 0; i < count; i++)
  {
    mutations[i] = Mutation(getMutation(c, i));
  }

  if(!initialized)
  {
    initialized = true;
    init();
  }
  return run();
}

BaseAI::BaseAI(Connection* conn) : c(conn) {}
BaseAI::~BaseAI() {}
