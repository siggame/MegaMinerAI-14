using System;
using System.Runtime.InteropServices;

public class Client {
  [DllImport("client")]
  public static extern IntPtr createConnection();
  [DllImport("client")]
  public static extern int serverConnect(IntPtr connection, string host, string port);

  [DllImport("client")]
  public static extern int serverLogin(IntPtr connection, string username, string password);
  [DllImport("client")]
  public static extern int createGame(IntPtr connection);
  [DllImport("client")]
  public static extern int joinGame(IntPtr connection, int id, string playerType);

  [DllImport("client")]
  public static extern void endTurn(IntPtr connection);
  [DllImport("client")]
  public static extern void getStatus(IntPtr connection);

  [DllImport("client")]
  public static extern int networkLoop(IntPtr connection);

#region Commands
  [DllImport("client")]
  public static extern int playerGerminate(IntPtr self, int x, int y, int mutation);
  [DllImport("client")]
  public static extern int plantTalk(IntPtr self, string message);
  [DllImport("client")]
  public static extern int plantRadiate(IntPtr self, int x, int y);
  [DllImport("client")]
  public static extern int plantUproot(IntPtr self, int x, int y);
#endregion

#region Accessors
  [DllImport("client")]
  public static extern int getMapWidth(IntPtr connection);
  [DllImport("client")]
  public static extern int getMapHeight(IntPtr connection);
  [DllImport("client")]
  public static extern int getTurnNumber(IntPtr connection);
  [DllImport("client")]
  public static extern int getMaxPlants(IntPtr connection);
  [DllImport("client")]
  public static extern int getPlayerID(IntPtr connection);
  [DllImport("client")]
  public static extern int getGameNumber(IntPtr connection);
  [DllImport("client")]
  public static extern int getBumbleweedSpeed(IntPtr connection);
  [DllImport("client")]
  public static extern int getPoolDamage(IntPtr connection);
  [DllImport("client")]
  public static extern int getPoolBuff(IntPtr connection);
  [DllImport("client")]
  public static extern int getTitanDebuff(IntPtr connection);
  [DllImport("client")]
  public static extern int getSporeRate(IntPtr connection);
  [DllImport("client")]
  public static extern int getMaxSpores(IntPtr connection);

  [DllImport("client")]
  public static extern IntPtr getPlayer(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getPlayerCount(IntPtr connection);
  [DllImport("client")]
  public static extern IntPtr getMappable(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getMappableCount(IntPtr connection);
  [DllImport("client")]
  public static extern IntPtr getPlant(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getPlantCount(IntPtr connection);
  [DllImport("client")]
  public static extern IntPtr getMutation(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getMutationCount(IntPtr connection);
#endregion

#region Getters
  [DllImport("client")]
  public static extern int playerGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern IntPtr playerGetPlayerName(IntPtr ptr);
  [DllImport("client")]
  public static extern float playerGetTime(IntPtr ptr);
  [DllImport("client")]
  public static extern int playerGetSpores(IntPtr ptr);

  [DllImport("client")]
  public static extern int mappableGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern int mappableGetX(IntPtr ptr);
  [DllImport("client")]
  public static extern int mappableGetY(IntPtr ptr);

  [DllImport("client")]
  public static extern int plantGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetX(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetY(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetOwner(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetMutation(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetRads(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetMaxRads(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetRadiatesLeft(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetMaxRadiates(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetRange(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetUprootsLeft(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetMaxUproots(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetStrength(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetMinStrength(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetBaseStrength(IntPtr ptr);
  [DllImport("client")]
  public static extern int plantGetMaxStrength(IntPtr ptr);

  [DllImport("client")]
  public static extern int mutationGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern IntPtr mutationGetName(IntPtr ptr);
  [DllImport("client")]
  public static extern int mutationGetType(IntPtr ptr);
  [DllImport("client")]
  public static extern int mutationGetSpores(IntPtr ptr);
  [DllImport("client")]
  public static extern int mutationGetMaxRadiates(IntPtr ptr);
  [DllImport("client")]
  public static extern int mutationGetMaxRads(IntPtr ptr);
  [DllImport("client")]
  public static extern int mutationGetRange(IntPtr ptr);
  [DllImport("client")]
  public static extern int mutationGetMaxUproots(IntPtr ptr);
  [DllImport("client")]
  public static extern int mutationGetMinStrength(IntPtr ptr);
  [DllImport("client")]
  public static extern int mutationGetBaseStrength(IntPtr ptr);
  [DllImport("client")]
  public static extern int mutationGetMaxStrength(IntPtr ptr);

#endregion

#region Properties
#endregion
}
