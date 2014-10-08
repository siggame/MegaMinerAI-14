// -*-c++-*-

#include "Mutation.h"
#include "game.h"


namespace client
{

Mutation::Mutation(_Mutation* pointer)
{
    ptr = (void*) pointer;
}

int Mutation::id()
{
  return ((_Mutation*)ptr)->id;
}

char* Mutation::name()
{
  return ((_Mutation*)ptr)->name;
}

int Mutation::type()
{
  return ((_Mutation*)ptr)->type;
}

int Mutation::spores()
{
  return ((_Mutation*)ptr)->spores;
}

int Mutation::maxRadiates()
{
  return ((_Mutation*)ptr)->maxRadiates;
}

int Mutation::maxRads()
{
  return ((_Mutation*)ptr)->maxRads;
}

int Mutation::range()
{
  return ((_Mutation*)ptr)->range;
}

int Mutation::maxUproots()
{
  return ((_Mutation*)ptr)->maxUproots;
}

int Mutation::minStrength()
{
  return ((_Mutation*)ptr)->minStrength;
}

int Mutation::baseStrength()
{
  return ((_Mutation*)ptr)->baseStrength;
}

int Mutation::maxStrength()
{
  return ((_Mutation*)ptr)->maxStrength;
}




std::ostream& operator<<(std::ostream& stream,Mutation ob)
{
  stream << "id: " << ((_Mutation*)ob.ptr)->id  <<'\n';
  stream << "name: " << ((_Mutation*)ob.ptr)->name  <<'\n';
  stream << "type: " << ((_Mutation*)ob.ptr)->type  <<'\n';
  stream << "spores: " << ((_Mutation*)ob.ptr)->spores  <<'\n';
  stream << "maxRadiates: " << ((_Mutation*)ob.ptr)->maxRadiates  <<'\n';
  stream << "maxRads: " << ((_Mutation*)ob.ptr)->maxRads  <<'\n';
  stream << "range: " << ((_Mutation*)ob.ptr)->range  <<'\n';
  stream << "maxUproots: " << ((_Mutation*)ob.ptr)->maxUproots  <<'\n';
  stream << "minStrength: " << ((_Mutation*)ob.ptr)->minStrength  <<'\n';
  stream << "baseStrength: " << ((_Mutation*)ob.ptr)->baseStrength  <<'\n';
  stream << "maxStrength: " << ((_Mutation*)ob.ptr)->maxStrength  <<'\n';
  return stream;
}

}
