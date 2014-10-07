using System;
using System.Runtime.InteropServices;

/// <summary>
/// Represents a single Plant on the map.
/// </summary>
public class Plant: Mappable
{

  public Plant()
  {
  }

  public Plant(IntPtr p)
  {
    ptr = p;
    ID = Client.plantGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public override bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.plants.Length; i++)
    {
      if(BaseAI.plants[i].ID == ID)
      {
        ptr = BaseAI.plants[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }

  #region Commands
  /// <summary>
  /// Command to radiate (heal, attack) another Plant.
  /// </summary>
  public bool radiate(int x, int y)
  {
    validify();
    return (Client.plantRadiate(ptr, x, y) == 0) ? false : true;
  }
  #endregion

  #region Getters
  /// <summary>
  /// Unique Identifier
  /// </summary>
  public new int Id
  {
    get
    {
      validify();
      int value = Client.plantGetId(ptr);
      return value;
    }
  }

  /// <summary>
  /// X position of the object
  /// </summary>
  public new int X
  {
    get
    {
      validify();
      int value = Client.plantGetX(ptr);
      return value;
    }
  }

  /// <summary>
  /// Y position of the object
  /// </summary>
  public new int Y
  {
    get
    {
      validify();
      int value = Client.plantGetY(ptr);
      return value;
    }
  }

  /// <summary>
  /// The owner of this Plant.
  /// </summary>
  public int Owner
  {
    get
    {
      validify();
      int value = Client.plantGetOwner(ptr);
      return value;
    }
  }

  /// <summary>
  /// The mutation of this Plant. This mutation refers to list of MutationSpecifications.
  /// </summary>
  public int Mutation
  {
    get
    {
      validify();
      int value = Client.plantGetMutation(ptr);
      return value;
    }
  }

  /// <summary>
  /// The current amount health this Plant has remaining.
  /// </summary>
  public int Rads
  {
    get
    {
      validify();
      int value = Client.plantGetRads(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum amount of this health this Plant can have
  /// </summary>
  public int MaxRads
  {
    get
    {
      validify();
      int value = Client.plantGetMaxRads(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum range this plant can radiate
  /// </summary>
  public int Range
  {
    get
    {
      validify();
      int value = Client.plantGetRange(ptr);
      return value;
    }
  }

  /// <summary>
  /// The distance this plant has left to move
  /// </summary>
  public int MovementLeft
  {
    get
    {
      validify();
      int value = Client.plantGetMovementLeft(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum distance this plant can move each turn
  /// </summary>
  public int MaxMovement
  {
    get
    {
      validify();
      int value = Client.plantGetMaxMovement(ptr);
      return value;
    }
  }

  /// <summary>
  /// The current power of this plant's radiation
  /// </summary>
  public int Strength
  {
    get
    {
      validify();
      int value = Client.plantGetStrength(ptr);
      return value;
    }
  }

  /// <summary>
  /// The minimum power of this plant's radiation
  /// </summary>
  public int MinStrength
  {
    get
    {
      validify();
      int value = Client.plantGetMinStrength(ptr);
      return value;
    }
  }

  /// <summary>
  /// The base power of this plant's radiation
  /// </summary>
  public int BaseStrength
  {
    get
    {
      validify();
      int value = Client.plantGetBaseStrength(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum power of this plant's radiation
  /// </summary>
  public int MaxStrength
  {
    get
    {
      validify();
      int value = Client.plantGetMaxStrength(ptr);
      return value;
    }
  }

  /// <summary>
  /// The current amount of radiation this Plant can have
  /// </summary>
  public int Storage
  {
    get
    {
      validify();
      int value = Client.plantGetStorage(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum amount of radiation this Plant can have
  /// </summary>
  public int MaxStorage
  {
    get
    {
      validify();
      int value = Client.plantGetMaxStorage(ptr);
      return value;
    }
  }

  /// <summary>
  /// The number of spores required to spawn this unit
  /// </summary>
  public int Spores
  {
    get
    {
      validify();
      int value = Client.plantGetSpores(ptr);
      return value;
    }
  }

  #endregion

  #region Properties
  #endregion
}
