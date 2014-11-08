#include "AI.h"
#include "util.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "Shell AI";
}

const char* AI::password()
{
  return "password";
}

//This function is run once, before your first turn.
void AI::init()
{
  srand(time(NULL));
  //set up me field
  me = &players[playerID()];
  //set up mother field
  mother = getMyPlants()[0];

  //set up directionOfEnemy field
  //if our mother is on the left side of the map, the enemy must be on the right side
  //and vice versa of course
  if (mother->x() < mapWidth()/2)
  {
    directionOfEnemy = 1;
  }
  else
  {
    directionOfEnemy = -1;
  }
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  std::vector<Plant*> myPlants = getMyPlants();

  //for every plant we own, move them forward and attack if it finds an enemy
  for (int j = 0; j < myPlants.size(); j++)
  {
    Plant& plant = *myPlants[j];
    //only try radiating if it's possible
    if(plant.radiatesLeft() > 0)
    {
      //only heal or buff allies and attack enemies
      int targetOwner = 1 - playerID();
      if(plant.mutation() == BUMBLEWEED || plant.mutation() == SOAKER)
      {
        targetOwner = playerID();
      }
      for (int i = 0; i < plants.size(); i++)
      {
        Plant foe = plants[i];

        //if it's dead skip it
        if(foe.rads() >= foe.maxRads())
        {
          continue;
        }

        //don't mess with pools
        if(foe.mutation() == POOL)
        {
          continue;
        }

        //if it's not the right target
        if(foe.owner() != targetOwner)
        {
          continue;
        }

        //if a healer or soaker can't effect the mother weed
        if(targetOwner == playerID() && foe.mutation() == MOTHER)
        {
          continue;
        }

        //if a soaker can't effect other soakers
        if(plant.mutation() == SOAKER && foe.mutation() == SOAKER)
        {
          continue;
        }

        //if we're within range...
        if (distance(plant.x(), plant.y(), foe.x(), foe.y()) < plant.range())
        {
          //get 'im!
          plant.radiate(foe.x(), foe.y());
          break;
        }
      }
    }
    //move them straight to the other side. no regrets.
    //move as far as possible, as long as it's not off the map
    int wantedX = plant.x();
    if(plant.mutation() == BUMBLEWEED)
    {
      wantedX += directionOfEnemy * bumbleweedSpeed();
    }
    else
    {
      wantedX += directionOfEnemy * uprootRange();
    }
    if (plant.uprootsLeft() > 0 &&
        getPlantAt(wantedX, plant.y()) == NULL &&
        wantedX >= 0 && wantedX < mapWidth())
    {
      plant.uproot(wantedX, plant.y());
    }
  }

  //make a new plant every turn, because why not?

  //first, check if we can actually do that
  if (myPlants.size() >= maxPlants())
  {
    //end turn
    return true;
  }

  int spawnX = -1, spawnY = -1;
  double angle = 0;
  for (int i = 0; i < myPlants.size(); i++)
  {
    Plant plant = *myPlants[i];
    //remove all plants in our list except for mothers and spawners
    if (!(plant.mutation() == MOTHER || plant.mutation() == SPAWNER))
    {
      myPlants.erase(myPlants.begin() + i);
    }
  }

  //get a random spawner or mother plant
  Plant& spawnerPlant = *myPlants[rand() % myPlants.size()];

  //get a new position centered around that spawner within its range
  //also, keep generating new coordinates until they become valid ones
  //Remember from trig:
  //(random x inside a circle) = centerX + rand(0,1)*radius*cos(angle)
  int spawnCheckLimit = 0;
  while (!withinBounds(spawnX, spawnY) || getPlantAt(spawnX, spawnY) != NULL)
  {
    angle = ((double)rand()/RAND_MAX) * 2 * M_PI;
    while (spawnX < 0 || spawnX >= mapWidth())
    {
      spawnX = spawnerPlant.x() + (int)(((float)rand()/RAND_MAX) * spawnerPlant.range() * cos(angle));
    }
    while (spawnY < 0 || spawnY >= mapHeight())
    {
      spawnY = spawnerPlant.y() + (int)(((float)rand()/RAND_MAX) * spawnerPlant.range() * sin(angle));
    }
    spawnCheckLimit++;

    //if we try to spawn too many times, just give up and end the turn
    if (spawnCheckLimit > 10)
    {
      return true;
    }
  }

  //spawn a random type of plant that isn't a mother or a pool at the coordinates we made
  //of course, make sure we have enough spores to do the job!
  int mutationType = (rand()%6)+1;
  if (me->spores() >= mutations[mutationType].spores() &&
      withinSpawnerRange(spawnX, spawnY))
  {
    me->germinate(spawnX, spawnY, mutationType);
  }
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
