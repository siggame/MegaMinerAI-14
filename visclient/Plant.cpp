// -*-c++-*-

#include "Plant.h"
#include "game.h"


namespace client
{

Plant::Plant(_Plant* pointer)
{
    ptr = (void*) pointer;
}

int Plant::id()
{
  return ((_Plant*)ptr)->id;
}

int Plant::x()
{
  return ((_Plant*)ptr)->x;
}

int Plant::y()
{
  return ((_Plant*)ptr)->y;
}

int Plant::owner()
{
  return ((_Plant*)ptr)->owner;
}

int Plant::mutation()
{
  return ((_Plant*)ptr)->mutation;
}

int Plant::rads()
{
  return ((_Plant*)ptr)->rads;
}

int Plant::maxRads()
{
  return ((_Plant*)ptr)->maxRads;
}

int Plant::range()
{
  return ((_Plant*)ptr)->range;
}

int Plant::movementLeft()
{
  return ((_Plant*)ptr)->movementLeft;
}

int Plant::maxMovement()
{
  return ((_Plant*)ptr)->maxMovement;
}

int Plant::strength()
{
  return ((_Plant*)ptr)->strength;
}

int Plant::minStrength()
{
  return ((_Plant*)ptr)->minStrength;
}

int Plant::baseStrength()
{
  return ((_Plant*)ptr)->baseStrength;
}

int Plant::maxStrength()
{
  return ((_Plant*)ptr)->maxStrength;
}

int Plant::storage()
{
  return ((_Plant*)ptr)->storage;
}

int Plant::maxStorage()
{
  return ((_Plant*)ptr)->maxStorage;
}

int Plant::spores()
{
  return ((_Plant*)ptr)->spores;
}


int Plant::radiate(int x, int y)
{
  return plantRadiate( (_Plant*)ptr, x, y);
}



std::ostream& operator<<(std::ostream& stream,Plant ob)
{
  stream << "id: " << ((_Plant*)ob.ptr)->id  <<'\n';
  stream << "x: " << ((_Plant*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Plant*)ob.ptr)->y  <<'\n';
  stream << "owner: " << ((_Plant*)ob.ptr)->owner  <<'\n';
  stream << "mutation: " << ((_Plant*)ob.ptr)->mutation  <<'\n';
  stream << "rads: " << ((_Plant*)ob.ptr)->rads  <<'\n';
  stream << "maxRads: " << ((_Plant*)ob.ptr)->maxRads  <<'\n';
  stream << "range: " << ((_Plant*)ob.ptr)->range  <<'\n';
  stream << "movementLeft: " << ((_Plant*)ob.ptr)->movementLeft  <<'\n';
  stream << "maxMovement: " << ((_Plant*)ob.ptr)->maxMovement  <<'\n';
  stream << "strength: " << ((_Plant*)ob.ptr)->strength  <<'\n';
  stream << "minStrength: " << ((_Plant*)ob.ptr)->minStrength  <<'\n';
  stream << "baseStrength: " << ((_Plant*)ob.ptr)->baseStrength  <<'\n';
  stream << "maxStrength: " << ((_Plant*)ob.ptr)->maxStrength  <<'\n';
  stream << "storage: " << ((_Plant*)ob.ptr)->storage  <<'\n';
  stream << "maxStorage: " << ((_Plant*)ob.ptr)->maxStorage  <<'\n';
  stream << "spores: " << ((_Plant*)ob.ptr)->spores  <<'\n';
  return stream;
}

}
