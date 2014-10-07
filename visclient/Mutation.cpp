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

int Mutation::mutation()
{
  return ((_Mutation*)ptr)->mutation;
}

int Mutation::spores()
{
  return ((_Mutation*)ptr)->spores;
}

int Mutation::maxAttacks()
{
  return ((_Mutation*)ptr)->maxAttacks;
}

int Mutation::maxHealth()
{
  return ((_Mutation*)ptr)->maxHealth;
}

int Mutation::maxMovement()
{
  return ((_Mutation*)ptr)->maxMovement;
}

int Mutation::range()
{
  return ((_Mutation*)ptr)->range;
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

int Mutation::maxStorage()
{
  return ((_Mutation*)ptr)->maxStorage;
}




std::ostream& operator<<(std::ostream& stream,Mutation ob)
{
  stream << "id: " << ((_Mutation*)ob.ptr)->id  <<'\n';
  stream << "name: " << ((_Mutation*)ob.ptr)->name  <<'\n';
  stream << "mutation: " << ((_Mutation*)ob.ptr)->mutation  <<'\n';
  stream << "spores: " << ((_Mutation*)ob.ptr)->spores  <<'\n';
  stream << "maxAttacks: " << ((_Mutation*)ob.ptr)->maxAttacks  <<'\n';
  stream << "maxHealth: " << ((_Mutation*)ob.ptr)->maxHealth  <<'\n';
  stream << "maxMovement: " << ((_Mutation*)ob.ptr)->maxMovement  <<'\n';
  stream << "range: " << ((_Mutation*)ob.ptr)->range  <<'\n';
  stream << "minStrength: " << ((_Mutation*)ob.ptr)->minStrength  <<'\n';
  stream << "baseStrength: " << ((_Mutation*)ob.ptr)->baseStrength  <<'\n';
  stream << "maxStrength: " << ((_Mutation*)ob.ptr)->maxStrength  <<'\n';
  stream << "maxStorage: " << ((_Mutation*)ob.ptr)->maxStorage  <<'\n';
  return stream;
}

}
