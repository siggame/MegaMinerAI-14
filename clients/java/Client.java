import com.sun.jna.Library;
import com.sun.jna.Pointer;
import com.sun.jna.Native;

public interface Client extends Library {
  Client INSTANCE = (Client)Native.loadLibrary("client", Client.class);
  Pointer createConnection();
  boolean serverConnect(Pointer connection, String host, String port);

  boolean serverLogin(Pointer connection, String username, String password);
  int createGame(Pointer connection);
  int joinGame(Pointer connection, int id, String playerType);

  void endTurn(Pointer connection);
  void getStatus(Pointer connection);

  int networkLoop(Pointer connection);


    //commands
  int playerTalk(Pointer object, String message);
  int playerSpawnPlant(Pointer object, int x, int y, int mutation);
  int plantRadiate(Pointer object, int x, int y);

    //accessors
  int getMapWidth(Pointer connection);
  int getMapHeight(Pointer connection);
  int getTurnNumber(Pointer connection);
  int getMaxPlants(Pointer connection);
  int getPlayerID(Pointer connection);
  int getGameNumber(Pointer connection);

  Pointer getPlayer(Pointer connection, int num);
  int getPlayerCount(Pointer connection);
  Pointer getMappable(Pointer connection, int num);
  int getMappableCount(Pointer connection);
  Pointer getPlant(Pointer connection, int num);
  int getPlantCount(Pointer connection);
  Pointer getMutation(Pointer connection, int num);
  int getMutationCount(Pointer connection);


    //getters
  int playerGetId(Pointer ptr);
  String playerGetPlayerName(Pointer ptr);
  float playerGetTime(Pointer ptr);
  int playerGetSpores(Pointer ptr);

  int mappableGetId(Pointer ptr);
  int mappableGetX(Pointer ptr);
  int mappableGetY(Pointer ptr);

  int plantGetId(Pointer ptr);
  int plantGetX(Pointer ptr);
  int plantGetY(Pointer ptr);
  int plantGetOwner(Pointer ptr);
  int plantGetMutation(Pointer ptr);
  int plantGetRads(Pointer ptr);
  int plantGetMaxRads(Pointer ptr);
  int plantGetRange(Pointer ptr);
  int plantGetMovementLeft(Pointer ptr);
  int plantGetMaxMovement(Pointer ptr);
  int plantGetStrength(Pointer ptr);
  int plantGetMinStrength(Pointer ptr);
  int plantGetBaseStrength(Pointer ptr);
  int plantGetMaxStrength(Pointer ptr);
  int plantGetStorage(Pointer ptr);
  int plantGetMaxStorage(Pointer ptr);
  int plantGetSpores(Pointer ptr);

  int mutationGetId(Pointer ptr);
  String mutationGetName(Pointer ptr);
  int mutationGetMutation(Pointer ptr);
  int mutationGetSpores(Pointer ptr);
  int mutationGetMaxAttacks(Pointer ptr);
  int mutationGetMaxHealth(Pointer ptr);
  int mutationGetMaxMovement(Pointer ptr);
  int mutationGetRange(Pointer ptr);
  int mutationGetMinStrength(Pointer ptr);
  int mutationGetBaseStrength(Pointer ptr);
  int mutationGetMaxStrength(Pointer ptr);
  int mutationGetMaxStorage(Pointer ptr);


    //properties

}
