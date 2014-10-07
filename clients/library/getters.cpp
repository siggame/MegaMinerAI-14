#include "getters.h"

DLLEXPORT int playerGetId(_Player* ptr)
{
  return ptr->id;
}
DLLEXPORT char* playerGetPlayerName(_Player* ptr)
{
  return ptr->playerName;
}
DLLEXPORT float playerGetTime(_Player* ptr)
{
  return ptr->time;
}
DLLEXPORT int playerGetSpores(_Player* ptr)
{
  return ptr->spores;
}
DLLEXPORT int mappableGetId(_Mappable* ptr)
{
  return ptr->id;
}
DLLEXPORT int mappableGetX(_Mappable* ptr)
{
  return ptr->x;
}
DLLEXPORT int mappableGetY(_Mappable* ptr)
{
  return ptr->y;
}
DLLEXPORT int plantGetId(_Plant* ptr)
{
  return ptr->id;
}
DLLEXPORT int plantGetX(_Plant* ptr)
{
  return ptr->x;
}
DLLEXPORT int plantGetY(_Plant* ptr)
{
  return ptr->y;
}
DLLEXPORT int plantGetOwner(_Plant* ptr)
{
  return ptr->owner;
}
DLLEXPORT int plantGetMutation(_Plant* ptr)
{
  return ptr->mutation;
}
DLLEXPORT int plantGetRads(_Plant* ptr)
{
  return ptr->rads;
}
DLLEXPORT int plantGetMaxRads(_Plant* ptr)
{
  return ptr->maxRads;
}
DLLEXPORT int plantGetRange(_Plant* ptr)
{
  return ptr->range;
}
DLLEXPORT int plantGetMovementLeft(_Plant* ptr)
{
  return ptr->movementLeft;
}
DLLEXPORT int plantGetMaxMovement(_Plant* ptr)
{
  return ptr->maxMovement;
}
DLLEXPORT int plantGetStrength(_Plant* ptr)
{
  return ptr->strength;
}
DLLEXPORT int plantGetMinStrength(_Plant* ptr)
{
  return ptr->minStrength;
}
DLLEXPORT int plantGetBaseStrength(_Plant* ptr)
{
  return ptr->baseStrength;
}
DLLEXPORT int plantGetMaxStrength(_Plant* ptr)
{
  return ptr->maxStrength;
}
DLLEXPORT int plantGetStorage(_Plant* ptr)
{
  return ptr->storage;
}
DLLEXPORT int plantGetMaxStorage(_Plant* ptr)
{
  return ptr->maxStorage;
}
DLLEXPORT int plantGetSpores(_Plant* ptr)
{
  return ptr->spores;
}
DLLEXPORT int mutationGetId(_Mutation* ptr)
{
  return ptr->id;
}
DLLEXPORT char* mutationGetName(_Mutation* ptr)
{
  return ptr->name;
}
DLLEXPORT int mutationGetMutation(_Mutation* ptr)
{
  return ptr->mutation;
}
DLLEXPORT int mutationGetSpores(_Mutation* ptr)
{
  return ptr->spores;
}
DLLEXPORT int mutationGetMaxAttacks(_Mutation* ptr)
{
  return ptr->maxAttacks;
}
DLLEXPORT int mutationGetMaxHealth(_Mutation* ptr)
{
  return ptr->maxHealth;
}
DLLEXPORT int mutationGetMaxMovement(_Mutation* ptr)
{
  return ptr->maxMovement;
}
DLLEXPORT int mutationGetRange(_Mutation* ptr)
{
  return ptr->range;
}
DLLEXPORT int mutationGetMinStrength(_Mutation* ptr)
{
  return ptr->minStrength;
}
DLLEXPORT int mutationGetBaseStrength(_Mutation* ptr)
{
  return ptr->baseStrength;
}
DLLEXPORT int mutationGetMaxStrength(_Mutation* ptr)
{
  return ptr->maxStrength;
}
DLLEXPORT int mutationGetMaxStorage(_Mutation* ptr)
{
  return ptr->maxStorage;
}

