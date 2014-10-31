import com.sun.jna.Pointer;
import java.util.ArrayList;

///The class implementing gameplay logic.
public class AI extends BaseAI
{
  public static final int MOTHER = 0,
                          SPAWNER = 1,
                          CHOKER = 2,
                          TUMBLEWEED = 4,
                          ARALIA = 5,
                          TITAN = 6,
                          POOL = 7;

  private Player me = players[playerID()];
  private Plant mother;
                          
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
    me.germinate(mother.getX(), mother.getY(), SPAWNER);
    
    return true;
  }


  //This function is called once, before your first turn
  public void init() 
  { 
    mother = getMyPlants().get(0);
  }

  //This function is called once, after your last turn
  public void end() {}
  
  //Helper function to get all of the plants owned
  private ArrayList<Plant> getMyPlants()
  {
    ArrayList<Plant> myPlants = new ArrayList<Plant>();
    for (int i = 0; i < droids.length; i++)
    {
      if (plants[i].owner = playerID())
        myPlants.add(plants[i]);
    }
    return myPlants;
  }
  
  private int distance(float x1, float y1, float x2, float y2)
  {
    return (int)(Math.floor(Math.sqrt(Math.pow(x1-x2,2)+Math.pow(y1-y2,2))));
  }
  
  public AI(Pointer c)
  {
    super(c);
  }
}
