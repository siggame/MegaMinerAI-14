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

  def germinate(self, x, y, mutation):
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
  game_state_attributes = ['id', 'x', 'y', 'owner', 'mutation', 'rads', 'maxRads', 'radiatesLeft', 'maxRadiates', 'range', 'uprootsLeft', 'maxUproots', 'strength', 'minStrength', 'baseStrength', 'maxStrength']
  def __init__(self, game, id, x, y, owner, mutation, rads, maxRads, radiatesLeft, maxRadiates, range, uprootsLeft, maxUproots, strength, minStrength, baseStrength, maxStrength):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.mutation = mutation
    self.rads = rads
    self.maxRads = maxRads
    self.radiatesLeft = radiatesLeft
    self.maxRadiates = maxRadiates
    self.range = range
    self.uprootsLeft = uprootsLeft
    self.maxUproots = maxUproots
    self.strength = strength
    self.minStrength = minStrength
    self.baseStrength = baseStrength
    self.maxStrength = maxStrength
    self.updatedAt = game.turnNumber

  def toList(self):
    return [self.id, self.x, self.y, self.owner, self.mutation, self.rads, self.maxRads, self.radiatesLeft, self.maxRadiates, self.range, self.uprootsLeft, self.maxUproots, self.strength, self.minStrength, self.baseStrength, self.maxStrength, ]
  
  # This will not work if the object has variables other than primitives
  def toJson(self):
    return dict(id = self.id, x = self.x, y = self.y, owner = self.owner, mutation = self.mutation, rads = self.rads, maxRads = self.maxRads, radiatesLeft = self.radiatesLeft, maxRadiates = self.maxRadiates, range = self.range, uprootsLeft = self.uprootsLeft, maxUproots = self.maxUproots, strength = self.strength, minStrength = self.minStrength, baseStrength = self.baseStrength, maxStrength = self.maxStrength, )
  
  def nextTurn(self):
    pass

  def talk(self, message):
    pass

  def radiate(self, x, y):
    pass

  def radiate(self, x, y):
    pass

  def uproot(self, x, y, mutation):
    pass

  def __setattr__(self, name, value):
      if name in self.game_state_attributes:
        object.__setattr__(self, 'updatedAt', self.game.turnNumber)
      object.__setattr__(self, name, value)

class Mutation(object):
  game_state_attributes = ['id', 'name', 'type', 'spores', 'maxRadiates', 'maxRads', 'range', 'maxUproots', 'minStrength', 'baseStrength', 'maxStrength']
  def __init__(self, game, id, name, type, spores, maxRadiates, maxRads, range, maxUproots, minStrength, baseStrength, maxStrength):
    self.game = game
    self.id = id
    self.name = name
    self.type = type
    self.spores = spores
    self.maxRadiates = maxRadiates
    self.maxRads = maxRads
    self.range = range
    self.maxUproots = maxUproots
    self.minStrength = minStrength
    self.baseStrength = baseStrength
    self.maxStrength = maxStrength
    self.updatedAt = game.turnNumber

  def toList(self):
    return [self.id, self.name, self.type, self.spores, self.maxRadiates, self.maxRads, self.range, self.maxUproots, self.minStrength, self.baseStrength, self.maxStrength, ]
  
  # This will not work if the object has variables other than primitives
  def toJson(self):
    return dict(id = self.id, name = self.name, type = self.type, spores = self.spores, maxRadiates = self.maxRadiates, maxRads = self.maxRads, range = self.range, maxUproots = self.maxUproots, minStrength = self.minStrength, baseStrength = self.baseStrength, maxStrength = self.maxStrength, )
  
  def nextTurn(self):
    pass

  def __setattr__(self, name, value):
      if name in self.game_state_attributes:
        object.__setattr__(self, 'updatedAt', self.game.turnNumber)
      object.__setattr__(self, name, value)


# The following are animations and do not need to have any logic added
class UprootAnimation:
  def __init__(self, actingID, fromX, fromY, toX, toY):
    self.actingID = actingID
    self.fromX = fromX
    self.fromY = fromY
    self.toX = toX
    self.toY = toY

  def toList(self):
    return ["uproot", self.actingID, self.fromX, self.fromY, self.toX, self.toY, ]

  def toJson(self):
    return dict(type = "uproot", actingID = self.actingID, fromX = self.fromX, fromY = self.fromY, toX = self.toX, toY = self.toY)

class SoakAnimation:
  def __init__(self, actingID, targetID):
    self.actingID = actingID
    self.targetID = targetID

  def toList(self):
    return ["soak", self.actingID, self.targetID, ]

  def toJson(self):
    return dict(type = "soak", actingID = self.actingID, targetID = self.targetID)

class HealAnimation:
  def __init__(self, actingID, targetID):
    self.actingID = actingID
    self.targetID = targetID

  def toList(self):
    return ["heal", self.actingID, self.targetID, ]

  def toJson(self):
    return dict(type = "heal", actingID = self.actingID, targetID = self.targetID)

class AttackAnimation:
  def __init__(self, actingID, targetID):
    self.actingID = actingID
    self.targetID = targetID

  def toList(self):
    return ["attack", self.actingID, self.targetID, ]

  def toJson(self):
    return dict(type = "attack", actingID = self.actingID, targetID = self.targetID)

class GerminateAnimation:
  def __init__(self, actingID, x, y):
    self.actingID = actingID
    self.x = x
    self.y = y

  def toList(self):
    return ["germinate", self.actingID, self.x, self.y, ]

  def toJson(self):
    return dict(type = "germinate", actingID = self.actingID, x = self.x, y = self.y)

