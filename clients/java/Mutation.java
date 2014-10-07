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
  ///The Mutation specific id representing this mutation of Plant.
  public int getMutation()
  {
    validify();
    return Client.INSTANCE.mutationGetMutation(ptr);
  }
  ///The spore cost to spawn this Plant mutation into the game.
  public int getSpores()
  {
    validify();
    return Client.INSTANCE.mutationGetSpores(ptr);
  }
  ///The maximum number of times the Plant can attack.
  public int getMaxAttacks()
  {
    validify();
    return Client.INSTANCE.mutationGetMaxAttacks(ptr);
  }
  ///The maximum amount of this health this Plant can have
  public int getMaxHealth()
  {
    validify();
    return Client.INSTANCE.mutationGetMaxHealth(ptr);
  }
  ///The maximum number of moves this Plant can move.
  public int getMaxMovement()
  {
    validify();
    return Client.INSTANCE.mutationGetMaxMovement(ptr);
  }
  ///The range of this Plant's attack.
  public int getRange()
  {
    validify();
    return Client.INSTANCE.mutationGetRange(ptr);
  }
  ///The minimum strength of this mutation's attack/heal/buff
  public int getMinStrength()
  {
    validify();
    return Client.INSTANCE.mutationGetMinStrength(ptr);
  }
  ///The base strength of this mutation's attack/heal/buff
  public int getBaseStrength()
  {
    validify();
    return Client.INSTANCE.mutationGetBaseStrength(ptr);
  }
  ///The power of this plant's attack/heal/buff
  public int getMaxStrength()
  {
    validify();
    return Client.INSTANCE.mutationGetMaxStrength(ptr);
  }
  ///The power of this Plant mutation's attack.
  public int getMaxStorage()
  {
    validify();
    return Client.INSTANCE.mutationGetMaxStorage(ptr);
  }

}
