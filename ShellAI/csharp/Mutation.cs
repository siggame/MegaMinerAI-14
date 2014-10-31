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
  /// The mutation of this Plant. This value is unique for all Mutations.
  /// </summary>
  public int Type
  {
    get
    {
      validify();
      int value = Client.mutationGetType(ptr);
      return value;
    }
  }

  /// <summary>
  /// The current amount of radiation this Plant has.
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
  /// The maximum number of times the Plant can radiate.
  /// </summary>
  public int MaxRadiates
  {
    get
    {
      validify();
      int value = Client.mutationGetMaxRadiates(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum amount of radiation this Plant can have before dying.
  /// </summary>
  public int MaxRads
  {
    get
    {
      validify();
      int value = Client.mutationGetMaxRads(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum range this plant can radiate.
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
  /// The maximum number of times this plant can be uprooted.
  /// </summary>
  public int MaxUproots
  {
    get
    {
      validify();
      int value = Client.mutationGetMaxUproots(ptr);
      return value;
    }
  }

  /// <summary>
  /// The minimum power of this plant.
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
  /// The base power of this plant.
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
  /// The maximum power of this plant.
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

  #endregion

  #region Properties
  #endregion
}
