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

  ///Allows a plant to display messages on the screen
  boolean talk(String message)
  {
    validify();
    return (Client.INSTANCE.plantTalk(ptr, message) == 0) ? false : true;
  }
  ///Command to radiate (heal, attack) another Plant.
  boolean radiate(int x, int y)
  {
    validify();
    return (Client.INSTANCE.plantRadiate(ptr, x, y) == 0) ? false : true;
  }
  ///Command to uproot a plant and move to a new location.
  boolean uproot(int x, int y)
  {
    validify();
    return (Client.INSTANCE.plantUproot(ptr, x, y) == 0) ? false : true;
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
  ///The current amount of radiation this Plant has.
  public int getRads()
  {
    validify();
    return Client.INSTANCE.plantGetRads(ptr);
  }
  ///The maximum amount of radiation this Plant can have before dying.
  public int getMaxRads()
  {
    validify();
    return Client.INSTANCE.plantGetMaxRads(ptr);
  }
  ///The remaining number of times the plant can radiate.
  public int getRadiatesLeft()
  {
    validify();
    return Client.INSTANCE.plantGetRadiatesLeft(ptr);
  }
  ///The maximum number of times the plant can radiate.
  public int getMaxRadiates()
  {
    validify();
    return Client.INSTANCE.plantGetMaxRadiates(ptr);
  }
  ///The maximum range this plant can radiate.
  public int getRange()
  {
    validify();
    return Client.INSTANCE.plantGetRange(ptr);
  }
  ///The remaining number of times this plant can be uprooted.
  public int getUprootsLeft()
  {
    validify();
    return Client.INSTANCE.plantGetUprootsLeft(ptr);
  }
  ///The maximum number of times this plant can be uprooted.
  public int getMaxUproots()
  {
    validify();
    return Client.INSTANCE.plantGetMaxUproots(ptr);
  }
  ///The current power of this plant.
  public int getStrength()
  {
    validify();
    return Client.INSTANCE.plantGetStrength(ptr);
  }
  ///The minimum power of this plant.
  public int getMinStrength()
  {
    validify();
    return Client.INSTANCE.plantGetMinStrength(ptr);
  }
  ///The base power of this plant.
  public int getBaseStrength()
  {
    validify();
    return Client.INSTANCE.plantGetBaseStrength(ptr);
  }
  ///The maximum power of this plant.
  public int getMaxStrength()
  {
    validify();
    return Client.INSTANCE.plantGetMaxStrength(ptr);
  }

}
