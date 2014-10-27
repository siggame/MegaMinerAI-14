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
  /// Allows a plant to display messages on the screen
  /// </summary>
  public bool talk(string message)
  {
    validify();
    return (Client.plantTalk(ptr, message) == 0) ? false : true;
  }
  /// <summary>
  /// Command to radiate (heal, attack) another Plant.
  /// </summary>
  public bool radiate(int x, int y)
  {
    validify();
    return (Client.plantRadiate(ptr, x, y) == 0) ? false : true;
  }
  /// <summary>
  /// Command to uproot a plant and move to a new location.
  /// </summary>
  public bool uproot(int x, int y)
  {
    validify();
    return (Client.plantUproot(ptr, x, y) == 0) ? false : true;
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
  /// The current amount of radiation this Plant has.
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
  /// The maximum amount of radiation this Plant can have before dying.
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
  /// The remaining number of times the plant can radiate.
  /// </summary>
  public int RadiatesLeft
  {
    get
    {
      validify();
      int value = Client.plantGetRadiatesLeft(ptr);
      return value;
    }
  }

  /// <summary>
  /// The maximum number of times the plant can radiate.
  /// </summary>
  public int MaxRadiates
  {
    get
    {
      validify();
      int value = Client.plantGetMaxRadiates(ptr);
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
      int value = Client.plantGetRange(ptr);
      return value;
    }
  }

  /// <summary>
  /// The remaining number of times this plant can be uprooted.
  /// </summary>
  public int UprootsLeft
  {
    get
    {
      validify();
      int value = Client.plantGetUprootsLeft(ptr);
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
      int value = Client.plantGetMaxUproots(ptr);
      return value;
    }
  }

  /// <summary>
  /// The current power of this plant.
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
  /// The minimum power of this plant.
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
  /// The base power of this plant.
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
  /// The maximum power of this plant.
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

  #endregion

  #region Properties
  #endregion
}
