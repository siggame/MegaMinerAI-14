from base import *
from matchUtils import *
from objects import *
import networking.config.config
from collections import defaultdict
from networking.sexpr.sexpr import *
import os
import itertools
import scribe
import jsonLogger
import math
import random

Scribe = scribe.Scribe

def loadClassDefaults(cfgFile = "config/defaults.cfg"):
  cfg = networking.config.config.readConfig(cfgFile)
  for className in cfg.keys():
    for attr in cfg[className]:
      setattr(eval(className), attr, cfg[className][attr])

class Match(DefaultGameWorld):
  def __init__(self, id, controller):
    self.id = int(id)
    self.controller = controller
    DefaultGameWorld.__init__(self)
    self.scribe = Scribe(self.logPath())
    if( self.logJson ):
      self.jsonLogger = jsonLogger.JsonLogger(self.logPath())
      self.jsonAnimations = []
      self.dictLog = dict(gameName = "Plants", turns = [])
    self.addPlayer(self.scribe, "spectator")

    self.turnNumber = -1
    self.playerID = -1
    self.gameNumber = id

    self.mapWidth = self.mapWidth
    self.mapHeight = self.mapHeight
    self.turnNumber = self.turnNumber
    self.maxPlants = self.maxPlants
    self.playerID = self.playerID

  #this is here to be wrapped
  def __del__(self):
    pass

  def getMutation(self, type):
    if 0 <= type < len(self.objects.mutations):
      return self.objects.mutations[type]
    else:
      return None

  def dist(self, x1, y1, x2, y2):
    return int(math.hypot(x1-x2, y1-y2))

  def addPlayer(self, connection, type="player"):
    connection.type = type
    if len(self.players) >= 2 and type == "player":
      return "Game is full"
    if type == "player":
      self.players.append(connection)
      try:
        #handle spores in next turn
        self.addObject(Player, [connection.screenName, self.startTime, 0])
      except TypeError:
        raise TypeError("Someone forgot to add the extra attributes to the Player object initialization")
    elif type == "spectator":
      self.spectators.append(connection)
      #If the game has already started, send them the ident message
      if (self.turn is not None):
        self.sendIdent([connection])
    return True

  def removePlayer(self, connection):
    if connection in self.players:
      if self.turn is not None:
        winner = self.players[1 - self.getPlayerIndex(connection)]
        self.declareWinner(winner, 'Opponent Disconnected')
      self.players.remove(connection)
    else:
      self.spectators.remove(connection)

  def start(self):
    if len(self.players) < 2:
      return "Game is not full"
    if self.winner is not None or self.turn is not None:
      return "Game has already begun"

    #TODO: START STUFF
    self.turn = self.players[-1]
    self.turnNumber = -1

    #make mutation types
    statList = ['name', 'type', 'spores', 'maxRadiates', 'maxRads', 'range', 'maxUproots', 'minStrength', 'baseStrength', 'maxStrength']
    mutationsMake = cfgMutations.values()
    mutationsMake.sort(key=lambda variant: variant['type'])
    for t in mutationsMake:
      self.addObject(Mutation, [t[value] for value in statList])

    #make some Mother Weeds
    mutation = self.objects.mutations[0]
    #do this later? [Russley says to use static location]
    #y = random.randint(0, self.game.mapHeight)
    #x = random.randint(0, self.game.mapWidth/10)
    y = self.mapHeight/2
    x = 0 + mutation.range + 1
    self.addObject(Plant, [x, y, 0, mutation.type, 0, mutation.maxRads, 0, mutation.maxRadiates, mutation.range, 0, mutation.maxUproots, mutation.baseStrength, mutation.minStrength, mutation.baseStrength, mutation.maxStrength])
    #player 2 plant
    x = self.mapWidth - x
    self.addObject(Plant, [x, y, 1, mutation.type, 0, mutation.maxRads, 0, mutation.maxRadiates, mutation.range, 0, mutation.maxUproots, mutation.baseStrength, mutation.minStrength, mutation.baseStrength, mutation.maxStrength])

    self.nextTurn()
    return True


  def nextTurn(self):
    self.turnNumber += 1
    if self.turn == self.players[0]:
      self.turn = self.players[1]
      self.playerID = 1
    elif self.turn == self.players[1]:
      self.turn = self.players[0]
      self.playerID = 0

    else:
      return "Game is over."

    for obj in self.objects.values():
      obj.nextTurn()

    self.checkWinner()
    if self.winner is None:
      self.sendStatus([self.turn] +  self.spectators)
    else:
      self.sendStatus(self.spectators)

    if( self.logJson ):
      self.dictLog['turns'].append(
        dict(
          mapWidth = self.mapWidth,
          mapHeight = self.mapHeight,
          turnNumber = self.turnNumber,
          maxPlants = self.maxPlants,
          playerID = self.playerID,
          gameNumber = self.gameNumber,
          Players = [i.toJson() for i in self.objects.values() if i.__class__ is Player],
          Mappables = [i.toJson() for i in self.objects.values() if i.__class__ is Mappable],
          Plants = [i.toJson() for i in self.objects.values() if i.__class__ is Plant],
          Mutations = [i.toJson() for i in self.objects.values() if i.__class__ is Mutation],
          animations = self.jsonAnimations
        )
      )
      self.jsonAnimations = []

    self.animations = ["animations"]
    return True

  def checkWinner(self):
    # mother dead, mother health, most plants, lowest total rads,
    # total strength, coin flip
    motherDead1 = True  # true if player 1's mother plant is dead
    motherDead2 = True  # true if player 2's mother plant is dead
    random.seed()

    # 0 = mother
    for plant in self.objects.mutations:
      if plant.owner == 0 and plant.rads <= plant.maxRad and plant.mutation == 0:
        motherDead1 = False
      if plant.owner == 1 and plant.rads <= plant.maxRad and plant.mutation == 0:
        motherDead2 = False

    if motherDead1:
      self.declareWinner(self.players[1], "Player 1\'s mother plant is dead")
    elif motherDead2:
      self.declareWinner(self.players[0], "Player 2\'s mother plant is dead")
    elif self.turnNumber >= self.turnLimit:
      motherRad1 = 0
      motherRad2 = 0
      totalPlants1 = 0
      totalPlants2 = 0
      totalRads1 = 0
      totalRads2 = 0
      totalStrength1 = 0
      totalStrength2 = 0
      for plant in self.objects.mutations:
        if plant.owner == 0:
          totalPlants1 += 1
          totalRads1 += plant.rads
          totalStrength1 += plant.strength
          if plant.mutation == 0:
            motherRad1 = plant.rads
        if plant.owner == 1:
          totalPlants2 += 1
          totalRads2 += plant.rads
          totalStrength2 += plant.strength
          if plant.mutation == 0:
            motherRad2 = plant.rads
      if motherRad1 < motherRad2:
        self.declareWinner(self.players[0], "Player 1\'s mother plant has less rads")
      elif motherRad1 > motherRad2:
        self.declareWinner(self.players[1], "Player 2\'s mother plant has less rads")
      elif totalPlants1 > totalPlants2:
        self.declareWinner(self.players[0], "Player 1 has more plants")
      elif totalPlants1 < totalPlants2:
        self.declareWinner(self.players[1], "Player 2 has more plants")
      elif totalRads1 < totalRads2:
        self.declareWinner(self.players[0], "Player 1 has less total rads")
      elif totalRads1 > totalRads2:
        self.declareWinner(self.players[1], "Player 2 has less total rads")
      elif totalStrength1 > totalStrength2:
        self.declareWinner(self.players[0], "Player 1 has more total strength")
      elif totalStrength1 < totalStrength2:
        self.declareWinner(self.players[1], "Player 2 has more total strength")
      else:
        self.declareWinner(self.players[random.randint(0, 1)], "Coin flip since players are tied")


  def declareWinner(self, winner, reason=''):
    print "Player", self.getPlayerIndex(self.winner), "wins game", self.id
    self.winner = winner

    msg = ["game-winner", self.id, self.winner.user, self.getPlayerIndex(self.winner), reason]

    if( self.logJson ):
      self.dictLog["winnerID"] =  self.getPlayerIndex(self.winner)
      self.dictLog["winReason"] = reason
      self.jsonLogger.writeLog( self.dictLog )

    self.scribe.writeSExpr(msg)
    self.scribe.finalize()
    self.removePlayer(self.scribe)

    for p in self.players + self.spectators:
      p.writeSExpr(msg)

    self.sendStatus([self.turn])
    self.playerID ^= 1
    self.sendStatus([self.players[self.playerID]])
    self.playerID ^= 1
    self.turn = None
    self.objects.clear()

  def logPath(self):
    return "logs/" + str(self.id)

  @derefArgs(Player, None, None, None)
  def germinate(self, object, x, y, mutation):
    return object.germinate(x, y, mutation, )

  @derefArgs(Plant, None)
  def talk(self, object, message):
    return object.talk(message, )

  @derefArgs(Plant, None, None)
  def radiate(self, object, x, y):
    return object.radiate(x, y, )

  @derefArgs(Plant, None, None)
  def uproot(self, object, x, y):
    return object.uproot(x, y, )


  def sendIdent(self, players):
    if len(self.players) < 2:
      return False
    list = []
    for i in itertools.chain(self.players, self.spectators):
      list += [[self.getPlayerIndex(i), i.user, i.screenName, i.type]]
    for i in players:
      i.writeSExpr(['ident', list, self.id, self.getPlayerIndex(i)])

  def getPlayerIndex(self, player):
    try:
      playerIndex = self.players.index(player)
    except ValueError:
      playerIndex = -1
    return playerIndex

  def sendStatus(self, players):
    for i in players:
      i.writeSExpr(self.status())
      i.writeSExpr(self.animations)
    return True


  def status(self):
    msg = ["status"]

    msg.append(["game", self.mapWidth, self.mapHeight, self.turnNumber, self.maxPlants, self.playerID, self.gameNumber])

    typeLists = []
    typeLists.append(["Player"] + [i.toList() for i in self.objects.values() if i.__class__ is Player])
    typeLists.append(["Mappable"] + [i.toList() for i in self.objects.values() if i.__class__ is Mappable])
    typeLists.append(["Plant"] + [i.toList() for i in self.objects.values() if i.__class__ is Plant])
    updated = [i for i in self.objects.values() if i.__class__ is Mutation and i.updatedAt > self.turnNumber-3]
    if updated:
      typeLists.append(["Mutation"] + [i.toList() for i in updated])

    msg.extend(typeLists)

    return msg

  def addAnimation(self, anim):
    # generate the sexp
    self.animations.append(anim.toList())
    # generate the json
    if( self.logJson ):
      self.jsonAnimations.append(anim.toJson())



loadClassDefaults()
