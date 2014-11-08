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
  stream << "radiatesLeft: " << ob.radiatesLeft  <<'\n';
  stream << "maxRadiates: " << ob.maxRadiates  <<'\n';
  stream << "range: " << ob.range  <<'\n';
  stream << "uprootsLeft: " << ob.uprootsLeft  <<'\n';
  stream << "maxUproots: " << ob.maxUproots  <<'\n';
  stream << "strength: " << ob.strength  <<'\n';
  stream << "minStrength: " << ob.minStrength  <<'\n';
  stream << "baseStrength: " << ob.baseStrength  <<'\n';
  stream << "maxStrength: " << ob.maxStrength  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Mutation ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "name: " << ob.name  <<'\n';
  stream << "type: " << ob.type  <<'\n';
  stream << "spores: " << ob.spores  <<'\n';
  stream << "maxRadiates: " << ob.maxRadiates  <<'\n';
  stream << "maxRads: " << ob.maxRads  <<'\n';
  stream << "range: " << ob.range  <<'\n';
  stream << "maxUproots: " << ob.maxUproots  <<'\n';
  stream << "minStrength: " << ob.minStrength  <<'\n';
  stream << "baseStrength: " << ob.baseStrength  <<'\n';
  stream << "maxStrength: " << ob.maxStrength  <<'\n';
  return stream;
}



std::ostream& operator<<(std::ostream& stream, soak ob)
{
  stream << "soak" << "\n";
  stream << "actingID: " << ob.actingID  <<'\n';
  stream << "targetID: " << ob.targetID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, uproot ob)
{
  stream << "uproot" << "\n";
  stream << "actingID: " << ob.actingID  <<'\n';
  stream << "fromX: " << ob.fromX  <<'\n';
  stream << "fromY: " << ob.fromY  <<'\n';
  stream << "toX: " << ob.toX  <<'\n';
  stream << "toY: " << ob.toY  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, heal ob)
{
  stream << "heal" << "\n";
  stream << "actingID: " << ob.actingID  <<'\n';
  stream << "targetID: " << ob.targetID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, plantTalk ob)
{
  stream << "plantTalk" << "\n";
  stream << "actingID: " << ob.actingID  <<'\n';
  stream << "message: " << ob.message  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, attack ob)
{
  stream << "attack" << "\n";
  stream << "actingID: " << ob.actingID  <<'\n';
  stream << "targetID: " << ob.targetID  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, germinate ob)
{
  stream << "germinate" << "\n";
  stream << "actingID: " << ob.actingID  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
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
  stream << "bumbleweedSpeed: " << ob.bumbleweedSpeed  <<'\n';
  stream << "poolDamage: " << ob.poolDamage  <<'\n';
  stream << "poolBuff: " << ob.poolBuff  <<'\n';
  stream << "sporeRate: " << ob.sporeRate  <<'\n';
  stream << "maxSpores: " << ob.maxSpores  <<'\n';
  stream << "uprootRange: " << ob.uprootRange  <<'\n';

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
//    if((*(*i)).type == SOAK)
//      stream << *((soak*)*i) << "\n";
//    if((*(*i)).type == UPROOT)
//      stream << *((uproot*)*i) << "\n";
//    if((*(*i)).type == HEAL)
//      stream << *((heal*)*i) << "\n";
//    if((*(*i)).type == PLANTTALK)
//      stream << *((plantTalk*)*i) << "\n";
//    if((*(*i)).type == ATTACK)
//      stream << *((attack*)*i) << "\n";
//    if((*(*i)).type == GERMINATE)
//      stream << *((germinate*)*i) << "\n";
  }
  

  }
  return stream;
}

Game::Game()
{
  winner = -1;
}

} // parser
