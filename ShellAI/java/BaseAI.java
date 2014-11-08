import com.sun.jna.Pointer;

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of builer-plate code out of the way
///The provided AI class does just that.
public abstract class BaseAI
{
  static Player[] players;
  static Mappable[] mappables;
  static Plant[] plants;
  static Mutation[] mutations;
  Pointer connection;
  static int iteration;
  boolean initialized;

  public BaseAI(Pointer c)
  {
    connection = c;
  }
    
  ///
  ///Make this your username, which should be provided.
  public abstract String username();
  ///
  ///Make this your password, which should be provided.
  public abstract String password();
  ///
  ///This is run on turn 1 before run
  public abstract void init();
  ///
  ///This is run every turn . Return true to end the turn, return false
  ///to request a status update from the server and then immediately rerun this function with the
  ///latest game status.
  public abstract boolean run();

  ///
  ///This is run on after your last turn.
  public abstract void end();


  public boolean startTurn()
  {
    iteration++;
    int count = 0;
    count = Client.INSTANCE.getPlayerCount(connection);
    players = new Player[count];
    for(int i = 0; i < count; i++)
    {
      players[i] = new Player(Client.INSTANCE.getPlayer(connection, i));
    }
    count = Client.INSTANCE.getMappableCount(connection);
    mappables = new Mappable[count];
    for(int i = 0; i < count; i++)
    {
      mappables[i] = new Mappable(Client.INSTANCE.getMappable(connection, i));
    }
    count = Client.INSTANCE.getPlantCount(connection);
    plants = new Plant[count];
    for(int i = 0; i < count; i++)
    {
      plants[i] = new Plant(Client.INSTANCE.getPlant(connection, i));
    }
    count = Client.INSTANCE.getMutationCount(connection);
    mutations = new Mutation[count];
    for(int i = 0; i < count; i++)
    {
      mutations[i] = new Mutation(Client.INSTANCE.getMutation(connection, i));
    }

    if(!initialized)
    {
      initialized = true;
      init();
    }
    return run();
  }


  ///The width of the total map.
  int mapWidth()
  {
    return Client.INSTANCE.getMapWidth(connection);
  }
  ///The height of the total map.
  int mapHeight()
  {
    return Client.INSTANCE.getMapHeight(connection);
  }
  ///The current turn number.
  int turnNumber()
  {
    return Client.INSTANCE.getTurnNumber(connection);
  }
  ///The maximum number of Plants allowed per player.
  int maxPlants()
  {
    return Client.INSTANCE.getMaxPlants(connection);
  }
  ///The id of the current player.
  int playerID()
  {
    return Client.INSTANCE.getPlayerID(connection);
  }
  ///What number game this is for the server.
  int gameNumber()
  {
    return Client.INSTANCE.getGameNumber(connection);
  }
  ///The maximum distance that a bumbleweed can move during an uproot
  int bumbleweedSpeed()
  {
    return Client.INSTANCE.getBumbleweedSpeed(connection);
  }
  ///The damage taken from standing in a pool
  int poolDamage()
  {
    return Client.INSTANCE.getPoolDamage(connection);
  }
  ///The strength buff taken from standing in a pool
  int poolBuff()
  {
    return Client.INSTANCE.getPoolBuff(connection);
  }
  ///The rate which your spores return to maxSpores
  int sporeRate()
  {
    return Client.INSTANCE.getSporeRate(connection);
  }
  ///The maximum number of spores a player can have
  int maxSpores()
  {
    return Client.INSTANCE.getMaxSpores(connection);
  }
  ///The uproot range
  int uprootRange()
  {
    return Client.INSTANCE.getUprootRange(connection);
  }
}
