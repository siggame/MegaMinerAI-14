using System;
using System.Runtime.InteropServices;

/// <summary>
/// Represents a mutation of Plant.
/// </summary>
public class Mutation
{
  public IntPtr ptr;
  protected int ID;
  protected int iteration;

  public Mutation()
  {
  }

  public Mutation(IntPtr p)
  {
    ptr = p;
    ID = Client.mutationGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.mutations.Length; i++)
    {
      if(BaseAI.mutations[i].ID == ID)
      {
        ptr = BaseAI.mutations[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }

  #region Commands
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
      int value = Client.mutationGetId(ptr);
      return value;
    }
  }

  /// <summary>
  /// The name of this mutation of Plant.
  /// </summary>
  public string Name
  {
    get
    {
      validify();
      IntPtr value = Client.mutationGetName(ptr);
      return Marshal.PtrToStringAuto(value);
    }
  }

  /// <summary>
  /// The Mutation specific id representing this mutation of Plant.
  /// </summary>
  public int Mutation
  {
    get
    {
      validify();
      int value = Client.mutationGetMutation(ptr);
      return value;
    }
  }

  /// <summary>
  /// The spore cost to spawn this Plant mutation into the game.
  /// </summary>
  public int Spores
  {
    get
    {
      validify();
      int value = Client.mutationGetSpores(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum number of times the Plant can attack.
  /// </summary>
  public int MaxAttacks
  {
    get
    {
      validify();
      int value = Client.mutationGetMaxAttacks(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum amount of this health this Plant can have
  /// </summary>
  public int MaxHealth
  {
    get
    {
      validify();
      int value = Client.mutationGetMaxHealth(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum number of moves this Plant can move.
  /// </summary>
  public int MaxMovement
  {
    get
    {
      validify();
      int value = Client.mutationGetMaxMovement(ptr);
      return value;
    }
  }

  /// <summary>
  /// The range of this Plant's attack.
  /// </summary>
  public int Range
  {
    get
    {
      validify();
      int value = Client.mutationGetRange(ptr);
      return value;
    }
  }

  /// <summary>
  /// The minimum strength of this mutation's attack/heal/buff
  /// </summary>
  public int MinStrength
  {
    get
    {
      validify();
      int value = Client.mutationGetMinStrength(ptr);
      return value;
    }
  }

  /// <summary>
  /// The base strength of this mutation's attack/heal/buff
  /// </summary>
  public int BaseStrength
  {
    get
    {
      validify();
      int value = Client.mutationGetBaseStrength(ptr);
      return value;
    }
  }

  /// <summary>
  /// The power of this plant's attack/heal/buff
  /// </summary>
  public int MaxStrength
  {
    get
    {
      validify();
      int value = Client.mutationGetMaxStrength(ptr);
      return value;
    }
  }

  /// <summary>
  /// The power of this Plant mutation's attack.
  /// </summary>
  public int MaxStorage
  {
    get
    {
      validify();
      int value = Client.mutationGetMaxStorage(ptr);
      return value;
    }
  }

  #endregion

  #region Properties
  #endregion
}
