using System;
using System.Runtime.InteropServices;

/// <summary>
/// 
/// </summary>
public class Player
{
  public IntPtr ptr;
  protected int ID;
  protected int iteration;

  public Player()
  {
  }

  public Player(IntPtr p)
  {
    ptr = p;
    ID = Client.playerGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.players.Length; i++)
    {
      if(BaseAI.players[i].ID == ID)
      {
        ptr = BaseAI.players[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }

  #region Commands
  /// <summary>
  /// Allows a player to germinate a new Plant.
  /// </summary>
  public bool germinate(int x, int y, int mutation)
  {
    validify();
    return (Client.playerGerminate(ptr, x, y, mutation) == 0) ? false : true;
  }
  #endregion

  #region Getters
  /// <summary>
  /// Unique Identifier
  /// </summary>
  public int Id
  {
    get
    {
      validify();
      int value = Client.playerGetId(ptr);
      return value;
    }
  }

  /// <summary>
  /// Player's Name
  /// </summary>
  public string PlayerName
  {
    get
    {
      validify();
      IntPtr value = Client.playerGetPlayerName(ptr);
      return Marshal.PtrToStringAuto(value);
    }
  }

  /// <summary>
  /// Time remaining, updated at start of turn
  /// </summary>
  public float Time
  {
    get
    {
      validify();
      float value = Client.playerGetTime(ptr);
      return value;
    }
  }

  /// <summary>
  /// Number of spores this player has to spawn a new unit
  /// </summary>
  public int Spores
  {
    get
    {
      validify();
      int value = Client.playerGetSpores(ptr);
      return value;
    }
  }

  #endregion

  #region Properties
  #endregion
}
