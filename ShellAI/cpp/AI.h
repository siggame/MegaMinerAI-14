#ifndef AI_H
#define AI_H

#include <cmath>
#include <vector>

#include "BaseAI.h"

///The class implementing gameplay logic.
class AI: public BaseAI
{
  enum
  {
    MOTHER = 0,
    SPAWNER,
    CHOKER,
    SOAKER,
    TUMBLEWEED,
    ARALIA,
    TITAN,
    POOL
  };
public:
  AI(Connection* c);
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  virtual void end();

  //returns the distance between two points
  int distance(int x1, int y1, int x2, int y2)
  {
    return static_cast<int>(floor(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))));
  }
  Player* me;
  Plant* mother;
  int directionOfEnemy;
  //Helper function to get all of the plants owned
  std::vector<Plant*> getMyPlants()
  {
    std::vector<Plant*> myPlants;
    for (int i = 0; i < plants.size(); i++)
    {
      if (plants[i].owner() == playerID())
      {
        myPlants.push_back(&plants[i]);
      }
    }
    return myPlants;
  }

  //Helper function to get a Plant at a point
  //Returns null if no plant found
  Plant* getPlantAt(int x, int y)
  {
    //if it's out of bounds, we don't need to check anything
    if (!withinBounds(x, y))
    {
      return NULL;
    }

    //for every plant, if a plant is at the position we want, return it
    for (int i = 0; i < plants.size(); i++)
    {
      if (plants[i].x() == x && plants[i].y() == y)
      {
        return &plants[i];
      }
    }
    return NULL;
  }

  //Helper function for bounds checking
  bool withinBounds(int x, int y)
  {
    if (x < 0 || x >= mapWidth() || y < 0 || y >= mapHeight())
    {
      return false;
    }

    return true;
  }

  //Helper function to check if we're within range of a Spawner or Mother
  bool withinSpawnerRange(int x, int y)
  {
    //No need to check if we're not within the bounds of the map
    if (!withinBounds(x, y))
    {
      return false;
    }

    //for every plant
    for (int i = 0; i < plants.size(); i++)
    {
      Plant plant = plants[i];

      //check for ownership and correct mutation
      if (plant.owner() == me->id() &&
          (plant.mutation() == SPAWNER || plant.mutation() == MOTHER))
      {
        //if we're within range, we're good
        if (distance(x, y, plant.x(), plant.y()) < plant.range())
        {
          return true;
        }
      }
    }

    //if we found none, nope
    return false;
  }
};

#endif
