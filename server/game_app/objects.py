import networking.config.config

cfgMutations = networking.config.config.readConfig("config/mutations.cfg")

class Player(object):
  game_state_attributes = ['id', 'playerName', 'time', 'spores']
  def __init__(self, game, id, playerName, time, spores):
    self.game = game
    self.id = id
    self.playerName = playerName
    self.time = time
    self.spores = spores
    self.updatedAt = game.turnNumber
    self.toSpawn = []

    self.spawners = []

  def toList(self):
    return [self.id, self.playerName, self.time, self.spores, ]
  
  # This will not work if the object has variables other than primitives
  def toJson(self):
    return dict(id = self.id, playerName = self.playerName, time = self.time, spores = self.spores, )
  
  def nextTurn(self):
    if self.game.playerID == self.id:
      #spores to test spawning
      self.spores += 300

    for plantStats in self.toSpawn:
      plant = self.game.addObject(Plant, plantStats)

      # Update caches
      self.game.plantsByPosition[plant.x, plant.y] = plant
      if plant.mutation in (self.game.mother, self.game.spawner):
        self.spawners.append(plant)

    #get rid of old spawns
    self.toSpawn = []
    return

  def germinate(self, x, y, mutation):
    mutationNum = mutation
    mutation = self.game.getMutation(mutation)

    if mutation is None:
      return 'Turn {}: {} is not a valid variant.'.format(self.game.turnNumber, mutationNum)
    elif mutation.spores == 0:
      return 'Turn {}: You cannot germinate a {}.'.format(self.game.turnNumber, mutation.name)
    elif self.spores < mutation.spores:
      return 'Turn {}: You do not have enough spores to germinate. Need: {} Have: {}'.format(self.game.turnNumber, mutation.spores, self.spores)
    elif not 0 <= x < self.game.mapWidth or not 0 <= y < self.game.mapHeight:
      return 'Turn {}: You are trying to germinate outside of the map.'.format(self.game.turnNumber)
    elif sum(x.owner == self.id for x in self.game.objects.plants) >= self.game.maxPlants:
      return 'Turn {}: You already have the maximum number of plants.'.format(self.game.turnNumber)

    # Make sure there are no plants on the tile
    if (x, y) in self.game.plantsByPosition:
      return 'Turn {}: You cannot germinate on top of another plant.'.format(self.game.turnNumber)

    # Check if germinate location is in the range of an owned spawner
    inRange = False
    for spawner in self.spawners:
      if self.game.dist(x, y, spawner.x, spawner.y) <= spawner.range:
        inRange = True
        break
    if not inRange:
      return 'Turn {}: ({}, {}) is not in the range of a Spawner or Mother Weed'.format(self.game.turnNumber, x, y)

    # Make sure nothing is trying to be spawned there
    for almostPlant in self.toSpawn:
      x2 = almostPlant[0]
      y2 = almostPlant[1]
      if (x2 == x) and (y2 == y):
        return 'Turn {}: A plant is already germinating on ({}, {})'.format(self.game.turnNumber, x, y)
    #now spawn the object [actually add to the list of things to spawn]
    self.toSpawn.append([x, y, self.id, mutation.type, 0, mutation.maxRads, 0, mutation.maxRadiates, mutation.range, 0, mutation.maxUproots, mutation.baseStrength, mutation.minStrength, mutation.baseStrength, mutation.maxStrength])
    #subtract the cost
    self.spores -= mutation.spores
    return True

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

  def handleDeath(self):
    if self.rads >= self.maxRads:
      self.game.removeObject(self)

      # Update caches
      del self.game.plantsByPosition[(self.x, self.y)]
      if self.mutation in (self.game.mother, self.game.spawner):
        self.game.objects.players[self.owner].spawners.remove(self)

  def nextTurn(self):
    # Pool damage/buff
    if self.mutation == self.game.pool:
      for plant in self.game.objects.plants:
        # Only affect plants at the beginning of that player's turn
        if plant.owner == self.game.playerID:
          if self.game.dist(plant.x, plant.y, self.x, self.y) <= self.range:
            if plant.mutation != self.game.soaker:
              plant.rads += self.game.poolDamage
              plant.strength = min(plant.strength + self.game.poolBuff, plant.maxStrength)
              plant.handleDeath()
            self.strength -= 1
      if self.strength <= 0:
        self.game.removeObject(self)
    # Titan debuff
    elif self.mutation == self.game.titan and self.owner == (1 - self.game.playerID):
      for plant in self.game.objects.plants:
        if plant.owner == self.game.playerID:
          if self.game.dist(plant.x, plant.y, self.x, self.y) <= self.range:
            plant.strength = max(plant.strength - self.game.titanDebuff, plant.minStrength)

    if self.owner == self.game.playerID:
      self.uprootsLeft = self.maxUproots
      self.radiatesLeft = self.maxRadiates

      # Normalize strength
      if self.strength < self.baseStrength:
        self.strength += 1
      elif self.strength > self.baseStrength:
        self.strength -= 1

      self.handleDeath()
    return

  def talk(self, message):
    pass

  def radiate(self, x, y):
    if self.owner != self.game.playerID:
      return 'Turn {}: You cannot control the opponent\'s plant {}.'.format(self.game.turnNumber, self.id)
    elif self.radiatesLeft <= 0:
      return 'Turn {}: Your {} does not have any radiates left.'.format(self.game.turnNumber, self.id)
    elif not (0 <= x < self.game.mapWidth) or not (0 <= y < self.game.mapHeight):
      return 'Turn {}: Your {} cannot radiate off the map.'.format(self.game.turnNumber, self.id)
    elif not (self.game.dist(self.x, self.y, x, y) < self.range):
      return 'Turn {}: Your {} cannot radiate outside of its range.'.format(self.game.turnNumber, self.id)

    target_plant = None
    if (x, y) in self.game.plantsByPosition:
      target_plant = self.game.plantsByPosition[(x, y)]
      if target_plant.mutation == self.game.pool:
        target_plant = None

    if not target_plant:
      return 'Turn {}: Your {} must radiate another plant'.format(self.game.turnNumber, self.id)
    if self.mutation in (self.game.choker, self.game.aralia):
      if target_plant.owner != (1 - self.game.playerID):
        return 'Turn {}: Your {} cannot attack your own plants'.format(self.game.turnNumber, self.id)

      # Deal damage
      #TODO: Higher rads affects damage/range
      damage = self.strength
      target_plant.rads += damage
      target_plant.handleDeath()

    elif self.mutation in (self.game.tumbleweed, self.game.soaker):
      if target_plant.plant.owner != self.game.playerID:
        return 'Turn {}: Your {} cannot heal opponent\'s plants'.format(self.game.turnNumber, self.id)
      elif target_plant.mutation == self.game.mother:
        return 'Turn {}: Your {} cannot heal or buff the mother weed.'.format(self.game.turnNumber, self.id)
      elif self.mutation == self.game.soaker and target_plant.mutation == self.game.soaker:
        return 'Turn {}: Your {} cannot buff another soaker.'.format(self.game.turnNumber, self.id)

      if self.mutation == self.game.tumbleweed:
        # Heal
        target_plant.rads = max(target_plant.rads - self.strength, 0)
      else:
        # Soaker; buff
        buff = int(1 + self.strength/4)
        target_plant.strength = max(target_plant.strength + buff, target_plant.maxStrength)

    self.radiatesLeft -= 1
    if self.mutation == self.game.tumbleweed:
      self.game.addAnimation(HealAnimation(self.id, target_plant.id))
    else:
      self.game.addAnimation(AttackAnimation(self.id, target_plant.id))

    return True


  def uproot(self, x, y):
    if self.owner != self.game.playerID:
      return 'Turn {}: You cannot uproot the opponent\'s plant {}.'.format(self.game.turnNumber, self.id)
    elif self.uprootsLeft <= 0:
      return 'Turn {}: Your plant {} does not have any uproots left.'.format(self.game.turnNumber, self.id)
    elif not (0 <= x < self.game.mapWidth) or not (0 <= y < self.game.mapHeight):
      return 'Turn {}: Your plant {} cannot move off the map.'.format(self.game.turnNumber, self.id)

    # Make sure there are no plants on the destination
    if (x, y) in self.game.plantsByPosition:
      return 'Turn {}: Your plant {} cannot move on top of another plant.'.format(self.game.turnNumber, self.id)

    # Find a spawner to move with
    if self.mutation != self.game.tumbleweed:
      inRange = False
      for spawner in self.game.objects.players[self.owner].spawners:
        if spawner.id != self.id:
          if self.game.dist(x, y, spawner.x, spawner.y) <= spawner.range:
            if self.game.dist(self.x, self.y, spawner.x, spawner.y) <= spawner.range:
              inRange = True
              break

      if not inRange:
        return 'Turn {}: Your plant {} is trying to move out of the range of a spawner it is in range of.'.format(self.game.turnNumber, self.id)

    # Update cache
    del self.game.plantsByPosition[(self.x, self.y)]
    self.game.plantsByPosition[(x, y)] = self

    # Update position
    self.x = x
    self.y = y
    self.uprootsLeft -= 1
    self.game.addAnimation(UprootAnimation(self.id, self.x, self.y, x, y))

    return True

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

