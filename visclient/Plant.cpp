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

int Plant::radiatesLeft()
{
  return ((_Plant*)ptr)->radiatesLeft;
}

int Plant::maxRadiates()
{
  return ((_Plant*)ptr)->maxRadiates;
}

int Plant::range()
{
  return ((_Plant*)ptr)->range;
}

int Plant::uprootsLeft()
{
  return ((_Plant*)ptr)->uprootsLeft;
}

int Plant::maxUproots()
{
  return ((_Plant*)ptr)->maxUproots;
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


int Plant::talk(char* message)
{
  return plantTalk( (_Plant*)ptr, message);
}

int Plant::radiate(int x, int y)
{
  return plantRadiate( (_Plant*)ptr, x, y);
}

int Plant::uproot(int x, int y)
{
  return plantUproot( (_Plant*)ptr, x, y);
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
  stream << "radiatesLeft: " << ((_Plant*)ob.ptr)->radiatesLeft  <<'\n';
  stream << "maxRadiates: " << ((_Plant*)ob.ptr)->maxRadiates  <<'\n';
  stream << "range: " << ((_Plant*)ob.ptr)->range  <<'\n';
  stream << "uprootsLeft: " << ((_Plant*)ob.ptr)->uprootsLeft  <<'\n';
  stream << "maxUproots: " << ((_Plant*)ob.ptr)->maxUproots  <<'\n';
  stream << "strength: " << ((_Plant*)ob.ptr)->strength  <<'\n';
  stream << "minStrength: " << ((_Plant*)ob.ptr)->minStrength  <<'\n';
  stream << "baseStrength: " << ((_Plant*)ob.ptr)->baseStrength  <<'\n';
  stream << "maxStrength: " << ((_Plant*)ob.ptr)->maxStrength  <<'\n';
  return stream;
}

}
