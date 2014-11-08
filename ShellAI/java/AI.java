import com.sun.jna.Pointer;
import java.util.ArrayList;
import java.util.Random;

///The class implementing gameplay logic.
public class AI extends BaseAI
{
  public static final int MOTHER = 0,
                          SPAWNER = 1,
                          CHOKER = 2,
                          SOAKER = 3,
                          TUMBLEWEED = 4,
                          ARALIA = 5,
                          TITAN = 6,
                          POOL = 7;

  private Player me;
  private Plant mother;
  private int directionOfEnemy; //moving in this direction moves you to the enemy's side
  private Random rand = new Random();        
          
  public String username()
  {
    return "Shell AI";
  }
  public String password()
  {
    return "password";
  }

  //This function is called each time it is your turn
  //Return true to end your turn, return false to ask the server for updated information
  public boolean run()
  {
    ArrayList<Plant> myPlants = getMyPlants();
  
    //for every plant we own, move them forward and attack if it finds an enemy
    for (Plant plant : myPlants)
    {
      //move them if we can
      if (plant.getUprootsLeft() > 0 &&
          getPlantAt(plant.getX()+directionOfEnemy, plant.getY()) == null &&
          withinSpawnerRange(plant.getX()+directionOfEnemy, plant.getY()))
      {
        //move them straight to the other side. no regrets.
        plant.uproot(plant.getX()+directionOfEnemy, plant.getY());
      }
      
      //if we can't attack, don't bother trying.
      if (plant.getRadiatesLeft() == 0)
      {
        continue;
      }
      
      //if there's anyone around, attaaaaaaaaaaack!!
      for (int i = 0; i < plants.length; i++)
      {
        Plant foe = plants[i];
        
        //let's not kill our own men, shall we?
        //also no pools
        if (foe.getOwner() == me.getId() && foe.getMutation() != POOL)
        { 
          continue;
        }
        
        //if we're within range...
        if (distance(plant.getX(), plant.getY(), foe.getX(), foe.getY()) < plant.getRange())
        {
          //get 'im!
          plant.radiate(foe.getX(), foe.getY());
        }
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
      Plant plant = myPlants.get(i);
      //remove all plants in our list except for mothers and spawners
      if (!(plant.getMutation() == MOTHER || plant.getMutation() == SPAWNER))
      {
        myPlants.remove(i);
      }
    }
    
    //get a random spawner or mother plant
    Plant spawnerPlant = myPlants.get(rand.nextInt(myPlants.size()));
    
    //get a new position centered around that spawner within its range
    //also, keep generating new coordinates until they become valid ones
    //Remember from trig:
    //(random x inside a circle) = centerX + rand(0,1)*radius*cos(angle)
    int spawnCheckLimit = 0;
    while (!withinBounds(spawnX, spawnY) || getPlantAt(spawnX, spawnY) != null)
    {
      angle = rand.nextDouble()* 2 * Math.PI;
      while (spawnX < 0 || spawnX >= mapWidth())
      {
        spawnX = spawnerPlant.getX() + (int)Math.floor(
          rand.nextFloat() * spawnerPlant.getRange() * Math.cos(angle));
      }
      while (spawnY < 0 || spawnY >= mapHeight())
      {
        spawnY = spawnerPlant.getY() + (int)Math.floor(
          rand.nextFloat() * spawnerPlant.getRange() * Math.sin(angle));
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
    int mutationType = rand.nextInt(6)+1;
    if (me.getSpores() >= mutations[mutationType].getSpores() &&
        withinSpawnerRange(spawnX, spawnY))
    {
      me.germinate(spawnX, spawnY, mutationType);  
    }
    return true;
  }

  //This function is called once, before your first turn
  public void init() 
  { 
    //set up me field
    me = players[playerID()];
    //set up mother field
    mother = getMyPlants().get(0);
    
    //set up directionOfEnemy field
    //if our mother is on the left side of the map, the enemy must be on the right side
    //and vice versa of course
    if (mother.getX() < mapWidth()/2)
    {
      directionOfEnemy = 1;
    }
    else
    {
      directionOfEnemy = -1;
    }
  }

  //This function is called once, after your last turn
  public void end() {}
  
  //Helper function to get all of the plants owned
  private ArrayList<Plant> getMyPlants()
  {
    ArrayList<Plant> myPlants = new ArrayList<Plant>();
    for (int i = 0; i < plants.length; i++)
    {
      if (plants[i].getOwner() == playerID())
      {
        myPlants.add(plants[i]);
      }
    }
    return myPlants;
  }
  
  //Helper function to get distance as a whole number
  private int distance(int x1, int y1, int x2, int y2)
  {
    return (int)(Math.floor(Math.sqrt(Math.pow(x1-x2,2)+Math.pow(y1-y2,2))));
  }
  
  //Helper function to get a Plant at a point
  //Returns null if no plant found
  private Plant getPlantAt(int x, int y)
  {
    //if it's out of bounds, we don't need to check anything
    if (!withinBounds(x, y))
    {
      return null;
    }
      
    //for every plant, if a plant is at the position we want, return it
    for (int i = 0; i < plants.length; i++)
    {
      if (plants[i].getX() == x && plants[i].getY() == y)
      {
        return plants[i];
      }
    }
    return null;
  }
  
  //Helper function for bounds checking
  private boolean withinBounds(int x, int y)
  {
    if (x < 0 || x >= mapWidth() || y < 0 || y >= mapHeight())
    {
      return false;
    }
    
    return true;
  }
  
  //Helper function to check if we're within range of a Spawner or Mother
  private boolean withinSpawnerRange(int x, int y)
  {
    //No need to check if we're not within the bounds of the map
    if (!withinBounds(x, y))
    {
      return false;
    }
      
    //for every plant
    for (int i = 0; i < plants.length; i++)
    {
      Plant plant = plants[i];
      
      //check for ownership and correct mutation
      if (plant.getOwner() == me.getId() &&
          (plant.getMutation() == SPAWNER || plant.getMutation() == MOTHER))
      {
        //if we're within range, we're good
        if (distance(x, y, plant.getX(), plant.getY()) < plant.getRange())
        {
          return true;
        }    
      }
    }
    
    //if we found none, nope
    return false;
  }
  
  public AI(Pointer c)
  {
    super(c);
  }
}
