// -*-c++-*-

#include "Player.h"
#include "game.h"


namespace client
{

Player::Player(_Player* pointer)
{
    ptr = (void*) pointer;
}

int Player::id()
{
  return ((_Player*)ptr)->id;
}

char* Player::playerName()
{
  return ((_Player*)ptr)->playerName;
}

float Player::time()
{
  return ((_Player*)ptr)->time;
}

int Player::spores()
{
  return ((_Player*)ptr)->spores;
}


int Player::talk(char* message)
{
  return playerTalk( (_Player*)ptr, message);
}

int Player::spawnPlant(int x, int y, int mutation)
{
  return playerSpawnPlant( (_Player*)ptr, x, y, mutation);
}



std::ostream& operator<<(std::ostream& stream,Player ob)
{
  stream << "id: " << ((_Player*)ob.ptr)->id  <<'\n';
  stream << "playerName: " << ((_Player*)ob.ptr)->playerName  <<'\n';
  stream << "time: " << ((_Player*)ob.ptr)->time  <<'\n';
  stream << "spores: " << ((_Player*)ob.ptr)->spores  <<'\n';
  return stream;
}

}
