// -*-c++-*-

#include "structures.h"

#include <iostream>

namespace parser
{


std::ostream& operator<<(std::ostream& stream, Player ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "playerName: " << ob.playerName  <<'\n';
  stream << "time: " << ob.time  <<'\n';
  stream << "spores: " << ob.spores  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Mappable ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Plant ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "mutation: " << ob.mutation  <<'\n';
  stream << "rads: " << ob.rads  <<'\n';
  stream << "maxRads: " << ob.maxRads  <<'\n';
  stream << "range: " << ob.range  <<'\n';
  stream << "movementLeft: " << ob.movementLeft  <<'\n';
  stream << "maxMovement: " << ob.maxMovement  <<'\n';
  stream << "strength: " << ob.strength  <<'\n';
  stream << "minStrength: " << ob.minStrength  <<'\n';
  stream << "baseStrength: " << ob.baseStrength  <<'\n';
  stream << "maxStrength: " << ob.maxStrength  <<'\n';
  stream << "storage: " << ob.storage  <<'\n';
  stream << "maxStorage: " << ob.maxStorage  <<'\n';
  stream << "spores: " << ob.spores  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Mutation ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "name: " << ob.name  <<'\n';
  stream << "mutation: " << ob.mutation  <<'\n';
  stream << "spores: " << ob.spores  <<'\n';
  stream << "maxAttacks: " << ob.maxAttacks  <<'\n';
  stream << "maxHealth: " << ob.maxHealth  <<'\n';
  stream << "maxMovement: " << ob.maxMovement  <<'\n';
  stream << "range: " << ob.range  <<'\n';
  stream << "minStrength: " << ob.minStrength  <<'\n';
  stream << "baseStrength: " << ob.baseStrength  <<'\n';
  stream << "maxStrength: " << ob.maxStrength  <<'\n';
  stream << "maxStorage: " << ob.maxStorage  <<'\n';
  return stream;
}



std::ostream& operator<<(std::ostream& stream, spawn ob)
{
  stream << "spawn" << "\n";
  stream << "sourceID: " << ob.sourceID  <<'\n';
  stream << "unitID: " << ob.unitID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, repair ob)
{
  stream << "repair" << "\n";
  stream << "actingID: " << ob.actingID  <<'\n';
  stream << "targetID: " << ob.targetID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, move ob)
{
  stream << "move" << "\n";
  stream << "actingID: " << ob.actingID  <<'\n';
  stream << "fromX: " << ob.fromX  <<'\n';
  stream << "fromY: " << ob.fromY  <<'\n';
  stream << "toX: " << ob.toX  <<'\n';
  stream << "toY: " << ob.toY  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, hack ob)
{
  stream << "hack" << "\n";
  stream << "actingID: " << ob.actingID  <<'\n';
  stream << "targetID: " << ob.targetID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, orbitalDrop ob)
{
  stream << "orbitalDrop" << "\n";
  stream << "sourceID: " << ob.sourceID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, attack ob)
{
  stream << "attack" << "\n";
  stream << "actingID: " << ob.actingID  <<'\n';
  stream << "targetID: " << ob.targetID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, GameState ob)
{
  stream << "mapWidth: " << ob.mapWidth  <<'\n';
  stream << "mapHeight: " << ob.mapHeight  <<'\n';
  stream << "turnNumber: " << ob.turnNumber  <<'\n';
  stream << "maxPlants: " << ob.maxPlants  <<'\n';
  stream << "playerID: " << ob.playerID  <<'\n';
  stream << "gameNumber: " << ob.gameNumber  <<'\n';

  stream << "\n\nPlayers:\n";
  for(std::map<int,Player>::iterator i = ob.players.begin(); i != ob.players.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nMappables:\n";
  for(std::map<int,Mappable>::iterator i = ob.mappables.begin(); i != ob.mappables.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nPlants:\n";
  for(std::map<int,Plant>::iterator i = ob.plants.begin(); i != ob.plants.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nMutations:\n";
  for(std::map<int,Mutation>::iterator i = ob.mutations.begin(); i != ob.mutations.end(); i++)
    stream << i->second << '\n';
  stream << "\nAnimation\n";
  for
    (
    std::map< int, std::vector< SmartPointer< Animation > > >::iterator j = ob.animations.begin(); 
    j != ob.animations.end(); 
    j++ 
    )
  {
  for(std::vector< SmartPointer< Animation > >::iterator i = j->second.begin(); i != j->second.end(); i++)
  {
//    if((*(*i)).type == SPAWN)
//      stream << *((spawn*)*i) << "\n";
//    if((*(*i)).type == REPAIR)
//      stream << *((repair*)*i) << "\n";
//    if((*(*i)).type == MOVE)
//      stream << *((move*)*i) << "\n";
//    if((*(*i)).type == HACK)
//      stream << *((hack*)*i) << "\n";
//    if((*(*i)).type == ORBITALDROP)
//      stream << *((orbitalDrop*)*i) << "\n";
//    if((*(*i)).type == ATTACK)
//      stream << *((attack*)*i) << "\n";
  }
  

  }
  return stream;
}

Game::Game()
{
  winner = -1;
}

} // parser
