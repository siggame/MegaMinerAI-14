class Player(object):
  game_state_attributes = ['id', 'playerName', 'time', 'spores']
  def __init__(self, game, id, playerName, time, spores):
    self.game = game
    self.id = id
    self.playerName = playerName
    self.time = time
    self.spores = spores
    self.updatedAt = game.turnNumber

  def toList(self):
    return [self.id, self.playerName, self.time, self.spores, ]
  
  # This will not work if the object has variables other than primitives
  def toJson(self):
    return dict(id = self.id, playerName = self.playerName, time = self.time, spores = self.spores, )
  
  def nextTurn(self):
    pass

  def talk(self, message):
    pass

  def spawnPlant(self, x, y, mutation):
    pass

  def __setattr__(self, name, value):
      if name in self.game_state_attributes:
        object.__setattr__(self, 'updatedAt', self.game.turnNumber)
      object.__setattr__(self, name, value)

class Mappable(object):
  game_state_attributes = ['id', 'x', 'y']
  def __init__(self, game, id, x, y):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.updatedAt = game.turnNumber

  def toList(self):
    return [self.id, self.x, self.y, ]
  
  # This will not work if the object has variables other than primitives
  def toJson(self):
    return dict(id = self.id, x = self.x, y = self.y, )
  
  def nextTurn(self):
    pass

  def __setattr__(self, name, value):
      if name in self.game_state_attributes:
        object.__setattr__(self, 'updatedAt', self.game.turnNumber)
      object.__setattr__(self, name, value)

class Plant(Mappable):
  game_state_attributes = ['id', 'x', 'y', 'owner', 'mutation', 'rads', 'maxRads', 'range', 'movementLeft', 'maxMovement', 'strength', 'minStrength', 'baseStrength', 'maxStrength', 'storage', 'maxStorage', 'spores']
  def __init__(self, game, id, x, y, owner, mutation, rads, maxRads, range, movementLeft, maxMovement, strength, minStrength, baseStrength, maxStrength, storage, maxStorage, spores):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.mutation = mutation
    self.rads = rads
    self.maxRads = maxRads
    self.range = range
    self.movementLeft = movementLeft
    self.maxMovement = maxMovement
    self.strength = strength
    self.minStrength = minStrength
    self.baseStrength = baseStrength
    self.maxStrength = maxStrength
    self.storage = storage
    self.maxStorage = maxStorage
    self.spores = spores
    self.updatedAt = game.turnNumber

  def toList(self):
    return [self.id, self.x, self.y, self.owner, self.mutation, self.rads, self.maxRads, self.range, self.movementLeft, self.maxMovement, self.strength, self.minStrength, self.baseStrength, self.maxStrength, self.storage, self.maxStorage, self.spores, ]
  
  # This will not work if the object has variables other than primitives
  def toJson(self):
    return dict(id = self.id, x = self.x, y = self.y, owner = self.owner, mutation = self.mutation, rads = self.rads, maxRads = self.maxRads, range = self.range, movementLeft = self.movementLeft, maxMovement = self.maxMovement, strength = self.strength, minStrength = self.minStrength, baseStrength = self.baseStrength, maxStrength = self.maxStrength, storage = self.storage, maxStorage = self.maxStorage, spores = self.spores, )
  
  def nextTurn(self):
    pass

  def radiate(self, x, y):
    pass

  def __setattr__(self, name, value):
      if name in self.game_state_attributes:
        object.__setattr__(self, 'updatedAt', self.game.turnNumber)
      object.__setattr__(self, name, value)

class Mutation(object):
  game_state_attributes = ['id', 'name', 'mutation', 'spores', 'maxAttacks', 'maxHealth', 'maxMovement', 'range', 'minStrength', 'baseStrength', 'maxStrength', 'maxStorage']
  def __init__(self, game, id, name, mutation, spores, maxAttacks, maxHealth, maxMovement, range, minStrength, baseStrength, maxStrength, maxStorage):
    self.game = game
    self.id = id
    self.name = name
    self.mutation = mutation
    self.spores = spores
    self.maxAttacks = maxAttacks
    self.maxHealth = maxHealth
    self.maxMovement = maxMovement
    self.range = range
    self.minStrength = minStrength
    self.baseStrength = baseStrength
    self.maxStrength = maxStrength
    self.maxStorage = maxStorage
    self.updatedAt = game.turnNumber

  def toList(self):
    return [self.id, self.name, self.mutation, self.spores, self.maxAttacks, self.maxHealth, self.maxMovement, self.range, self.minStrength, self.baseStrength, self.maxStrength, self.maxStorage, ]
  
  # This will not work if the object has variables other than primitives
  def toJson(self):
    return dict(id = self.id, name = self.name, mutation = self.mutation, spores = self.spores, maxAttacks = self.maxAttacks, maxHealth = self.maxHealth, maxMovement = self.maxMovement, range = self.range, minStrength = self.minStrength, baseStrength = self.baseStrength, maxStrength = self.maxStrength, maxStorage = self.maxStorage, )
  
  def nextTurn(self):
    pass

  def __setattr__(self, name, value):
      if name in self.game_state_attributes:
        object.__setattr__(self, 'updatedAt', self.game.turnNumber)
      object.__setattr__(self, name, value)


# The following are animations and do not need to have any logic added
class SpawnAnimation:
  def __init__(self, sourceID, unitID):
    self.sourceID = sourceID
    self.unitID = unitID

  def toList(self):
    return ["spawn", self.sourceID, self.unitID, ]

  def toJson(self):
    return dict(type = "spawn", sourceID = self.sourceID, unitID = self.unitID)

class RepairAnimation:
  def __init__(self, actingID, targetID):
    self.actingID = actingID
    self.targetID = targetID

  def toList(self):
    return ["repair", self.actingID, self.targetID, ]

  def toJson(self):
    return dict(type = "repair", actingID = self.actingID, targetID = self.targetID)

class MoveAnimation:
  def __init__(self, actingID, fromX, fromY, toX, toY):
    self.actingID = actingID
    self.fromX = fromX
    self.fromY = fromY
    self.toX = toX
    self.toY = toY

  def toList(self):
    return ["move", self.actingID, self.fromX, self.fromY, self.toX, self.toY, ]

  def toJson(self):
    return dict(type = "move", actingID = self.actingID, fromX = self.fromX, fromY = self.fromY, toX = self.toX, toY = self.toY)

class HackAnimation:
  def __init__(self, actingID, targetID):
    self.actingID = actingID
    self.targetID = targetID

  def toList(self):
    return ["hack", self.actingID, self.targetID, ]

  def toJson(self):
    return dict(type = "hack", actingID = self.actingID, targetID = self.targetID)

class OrbitalDropAnimation:
  def __init__(self, sourceID):
    self.sourceID = sourceID

  def toList(self):
    return ["orbitalDrop", self.sourceID, ]

  def toJson(self):
    return dict(type = "orbitalDrop", sourceID = self.sourceID)

class AttackAnimation:
  def __init__(self, actingID, targetID):
    self.actingID = actingID
    self.targetID = targetID

  def toList(self):
    return ["attack", self.actingID, self.targetID, ]

  def toJson(self):
    return dict(type = "attack", actingID = self.actingID, targetID = self.targetID)

