import com.sun.jna.Pointer;

///Represents a single Plant on the map.
class Plant extends Mappable
{
  public Plant(Pointer p)
  {
    super(p);
  }
  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.plants.length; i++)
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

    //commands

  ///Command to radiate (heal, attack) another Plant.
  boolean radiate(int x, int y)
  {
    validify();
    return (Client.INSTANCE.plantRadiate(ptr, x, y) == 0) ? false : true;
  }

    //getters

  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.plantGetId(ptr);
  }
  ///X position of the object
  public int getX()
  {
    validify();
    return Client.INSTANCE.plantGetX(ptr);
  }
  ///Y position of the object
  public int getY()
  {
    validify();
    return Client.INSTANCE.plantGetY(ptr);
  }
  ///The owner of this Plant.
  public int getOwner()
  {
    validify();
    return Client.INSTANCE.plantGetOwner(ptr);
  }
  ///The mutation of this Plant. This mutation refers to list of MutationSpecifications.
  public int getMutation()
  {
    validify();
    return Client.INSTANCE.plantGetMutation(ptr);
  }
  ///The current amount health this Plant has remaining.
  public int getRads()
  {
    validify();
    return Client.INSTANCE.plantGetRads(ptr);
  }
  ///The maximum amount of this health this Plant can have
  public int getMaxRads()
  {
    validify();
    return Client.INSTANCE.plantGetMaxRads(ptr);
  }
  ///The maximum range this plant can radiate
  public int getRange()
  {
    validify();
    return Client.INSTANCE.plantGetRange(ptr);
  }
  ///The distance this plant has left to move
  public int getMovementLeft()
  {
    validify();
    return Client.INSTANCE.plantGetMovementLeft(ptr);
  }
  ///The maximum distance this plant can move each turn
  public int getMaxMovement()
  {
    validify();
    return Client.INSTANCE.plantGetMaxMovement(ptr);
  }
  ///The current power of this plant's radiation
  public int getStrength()
  {
    validify();
    return Client.INSTANCE.plantGetStrength(ptr);
  }
  ///The minimum power of this plant's radiation
  public int getMinStrength()
  {
    validify();
    return Client.INSTANCE.plantGetMinStrength(ptr);
  }
  ///The base power of this plant's radiation
  public int getBaseStrength()
  {
    validify();
    return Client.INSTANCE.plantGetBaseStrength(ptr);
  }
  ///The maximum power of this plant's radiation
  public int getMaxStrength()
  {
    validify();
    return Client.INSTANCE.plantGetMaxStrength(ptr);
  }
  ///The current amount of radiation this Plant can have
  public int getStorage()
  {
    validify();
    return Client.INSTANCE.plantGetStorage(ptr);
  }
  ///The maximum amount of radiation this Plant can have
  public int getMaxStorage()
  {
    validify();
    return Client.INSTANCE.plantGetMaxStorage(ptr);
  }
  ///The number of spores required to spawn this unit
  public int getSpores()
  {
    validify();
    return Client.INSTANCE.plantGetSpores(ptr);
  }

}
