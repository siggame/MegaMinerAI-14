import com.sun.jna.Pointer;

///Represents a mutation of Plant.
class Mutation
{
  Pointer ptr;
  int ID;
  int iteration;
  public Mutation(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.mutationGetId(ptr);
    iteration = BaseAI.iteration;
  }
  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.mutations.length; i++)
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

    //commands


    //getters

  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.mutationGetId(ptr);
  }
  ///The name of this mutation of Plant.
  public String getName()
  {
    validify();
    return Client.INSTANCE.mutationGetName(ptr);
  }
  ///The mutation of this Plant. This value is unique for all Mutations.
  public int getType()
  {
    validify();
    return Client.INSTANCE.mutationGetType(ptr);
  }
  ///The current amount of radiation this Plant has.
  public int getSpores()
  {
    validify();
    return Client.INSTANCE.mutationGetSpores(ptr);
  }
  ///The maximum number of times the Plant can radiate.
  public int getMaxRadiates()
  {
    validify();
    return Client.INSTANCE.mutationGetMaxRadiates(ptr);
  }
  ///The maximum amount of radiation this Plant can have before dying.
  public int getMaxRads()
  {
    validify();
    return Client.INSTANCE.mutationGetMaxRads(ptr);
  }
  ///The maximum range this plant can radiate.
  public int getRange()
  {
    validify();
    return Client.INSTANCE.mutationGetRange(ptr);
  }
  ///The maximum number of times this plant can be uprooted.
  public int getMaxUproots()
  {
    validify();
    return Client.INSTANCE.mutationGetMaxUproots(ptr);
  }
  ///The minimum power of this plant.
  public int getMinStrength()
  {
    validify();
    return Client.INSTANCE.mutationGetMinStrength(ptr);
  }
  ///The base power of this plant.
  public int getBaseStrength()
  {
    validify();
    return Client.INSTANCE.mutationGetBaseStrength(ptr);
  }
  ///The maximum power of this plant.
  public int getMaxStrength()
  {
    validify();
    return Client.INSTANCE.mutationGetMaxStrength(ptr);
  }

}
