using System;
using System.Runtime.InteropServices;

/// <summary>
/// This class implements most the code an AI would need to interface with the lower-level game code.
/// AIs should extend this class to get a lot of builer-plate code out of the way. The provided AI class does just that.
/// </summary>
public abstract class BaseAI
{
  public static Player[] players;
  public static Mappable[] mappables;
  public static Plant[] plants;
  public static Mutation[] mutations;

  IntPtr connection;
  public static int iteration;
  bool initialized;

  public BaseAI(IntPtr c)
  {
    connection = c;
  }

  /// <summary>
  /// Make this your username, which should be provided.
  /// </summary>
  /// <returns>Returns the username of the player.</returns>
  public abstract String username();

  /// <summary>
  /// Make this your password, which should be provided.
  /// </summary>
  /// <returns>Returns the password of the player.</returns>
  public abstract String password();

  /// <summary>
  /// This is run once on turn one before run().
  /// </summary>
  public abstract void init();

  /// <summary>
  /// This is run every turn.
  /// </summary>
  /// <returns>
  /// Return true to end turn, false to resynchronize with the 
  /// server and run again.
  /// </returns>
  public abstract bool run();

  /// <summary>
  /// This is run once after your last turn.
  /// </summary>
  public abstract void end();

  /// <summary>
  /// Synchronizes with the server, then calls run().
  /// </summary>
  /// <returns>
  /// Return true to end turn, false to resynchronize with the 
  /// server and run again.
  /// </returns>
  public bool startTurn()
  {
    int count = 0;
    iteration++;

    count = Client.getPlayerCount(connection);
    players = new Player[count];
    for(int i = 0; i < count; i++)
      players[i] = new Player(Client.getPlayer(connection, i));

    count = Client.getMappableCount(connection);
    mappables = new Mappable[count];
    for(int i = 0; i < count; i++)
      mappables[i] = new Mappable(Client.getMappable(connection, i));

    count = Client.getPlantCount(connection);
    plants = new Plant[count];
    for(int i = 0; i < count; i++)
      plants[i] = new Plant(Client.getPlant(connection, i));

    count = Client.getMutationCount(connection);
    mutations = new Mutation[count];
    for(int i = 0; i < count; i++)
      mutations[i] = new Mutation(Client.getMutation(connection, i));

    if(!initialized)
    {
      initialized = true;
      init();
    }

    return run();
  }

  /// <summary>
  /// The width of the total map.
  /// </summary>
  /// <returns>Returns the width of the total map.</returns>
  public int mapWidth()
  {
    int value = Client.getMapWidth(connection);
    return value;
  }

  /// <summary>
  /// The height of the total map.
  /// </summary>
  /// <returns>Returns the height of the total map.</returns>
  public int mapHeight()
  {
    int value = Client.getMapHeight(connection);
    return value;
  }

  /// <summary>
  /// The current turn number.
  /// </summary>
  /// <returns>Returns the current turn number.</returns>
  public int turnNumber()
  {
    int value = Client.getTurnNumber(connection);
    return value;
  }

  /// <summary>
  /// The maximum number of Plants allowed per player.
  /// </summary>
  /// <returns>Returns the maximum number of Plants allowed per player.</returns>
  public int maxPlants()
  {
    int value = Client.getMaxPlants(connection);
    return value;
  }

  /// <summary>
  /// The id of the current player.
  /// </summary>
  /// <returns>Returns the id of the current player.</returns>
  public int playerID()
  {
    int value = Client.getPlayerID(connection);
    return value;
  }

  /// <summary>
  /// What number game this is for the server.
  /// </summary>
  /// <returns>Returns what number game this is for the server.</returns>
  public int gameNumber()
  {
    int value = Client.getGameNumber(connection);
    return value;
  }

  /// <summary>
  /// The maximum distance that a bumbleweed can move during an uproot
  /// </summary>
  /// <returns>Returns the maximum distance that a bumbleweed can move during an uproot</returns>
  public int bumbleweedSpeed()
  {
    int value = Client.getBumbleweedSpeed(connection);
    return value;
  }

  /// <summary>
  /// The damage taken from standing in a pool
  /// </summary>
  /// <returns>Returns the damage taken from standing in a pool</returns>
  public int poolDamage()
  {
    int value = Client.getPoolDamage(connection);
    return value;
  }

  /// <summary>
  /// The strength buff taken from standing in a pool
  /// </summary>
  /// <returns>Returns the strength buff taken from standing in a pool</returns>
  public int poolBuff()
  {
    int value = Client.getPoolBuff(connection);
    return value;
  }

  /// <summary>
  /// The strength debuff caused by an enemy Titan
  /// </summary>
  /// <returns>Returns the strength debuff caused by an enemy Titan</returns>
  public int titanDebuff()
  {
    int value = Client.getTitanDebuff(connection);
    return value;
  }

  /// <summary>
  /// The rate which your spores return to maxSpores
  /// </summary>
  /// <returns>Returns the rate which your spores return to maxSpores</returns>
  public int sporeRate()
  {
    int value = Client.getSporeRate(connection);
    return value;
  }

  /// <summary>
  /// The maximum number of spores a player can have
  /// </summary>
  /// <returns>Returns the maximum number of spores a player can have</returns>
  public int maxSpores()
  {
    int value = Client.getMaxSpores(connection);
    return value;
  }

  /// <summary>
  /// The range of uproot
  /// </summary>
  /// <returns>Returns the range of uproot</returns>
  public int uprootRange()
  {
    int value = Client.getUprootRange(connection);
    return value;
  }
}
