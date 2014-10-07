# -*- coding: iso-8859-1 -*-
from structures import *

aspects = ['timer']

gameName = "Plants"

constants = [
  ]

modelOrder = ['Player', 'Mappable', 'Plant', 'Mutation']

globals = [
  Variable('mapWidth', int, 'The width of the total map.'),
  Variable('mapHeight', int, 'The height of the total map.'),
  Variable('turnNumber', int, 'The current turn number.'),
  Variable('maxPlants', int, 'The maximum number of Plants allowed per player.'),
  Variable('playerID', int, 'The id of the current player.'),
  Variable('gameNumber', int, 'What number game this is for the server.'),
]

playerData = [
  Variable('spores', int, 'Number of spores this player has to spawn a new unit')
  ]

playerFunctions = [
  Function('talk', [Variable('message', str)], doc='Allows a player to display messages on the screen'),
  Function('spawnPlant', [Variable('x', int), Variable('y', int), Variable('mutation', int)], doc='Allows a player to spawn a Plant.'),
]

#MAPPABLE
Mappable = Model('Mappable',
  data=[
    Variable('x', int, 'X position of the object'),
    Variable('y', int, 'Y position of the object')
  ],
  doc='A mappable object!',
)

#PLANT
Plant = Model('Plant',
  parent = Mappable,
  data = [
    Variable('owner', int, 'The owner of this Plant.'),
    Variable('mutation', int, 'The mutation of this Plant. This mutation refers to list of MutationSpecifications.'),

    Variable('rads', int, 'The current amount health this Plant has remaining.'),
    Variable('maxRads', int, 'The maximum amount of this health this Plant can have'),
    
    Variable('range', int, 'The maximum range this plant can radiate'),
    
    Variable('movementLeft', int, 'The distance this plant has left to move'),
    Variable('maxMovement', int, 'The maximum distance this plant can move each turn'),

    Variable('strength',     int, 'The current power of this plant\'s radiation'),
    Variable('minStrength',  int, 'The minimum power of this plant\'s radiation'),
    Variable('baseStrength', int, 'The base power of this plant\'s radiation'),
    Variable('maxStrength',  int, 'The maximum power of this plant\'s radiation'),
    
    Variable('storage', int, 'The current amount of radiation this Plant can have'),
    Variable('maxStorage', int, 'The maximum amount of radiation this Plant can have'),

    Variable('spores', int, 'The number of spores required to spawn this unit'),
    ],
  doc='Represents a single Plant on the map.',
  functions=[
    Function('radiate', [Variable('x', int), Variable('y', int)],
    doc='Command to radiate (heal, attack) another Plant.'),
  ],
)

#MUTATIONSPECIFICATION
Mutation = Model('Mutation',
  data = [
    Variable('name', str, 'The name of this mutation of Plant.'),
    Variable('mutation', int, 'The Mutation specific id representing this mutation of Plant.'),
    Variable('spores', int, 'The spore cost to spawn this Plant mutation into the game.'),
    Variable('maxAttacks', int, 'The maximum number of times the Plant can attack.'),
    Variable('maxHealth', int, 'The maximum amount of this health this Plant can have'),
    Variable('maxMovement', int, 'The maximum number of moves this Plant can move.'),
    Variable('range', int, 'The range of this Plant\'s attack.'),

    Variable('minStrength',  int, 'The minimum strength of this mutation\'s attack/heal/buff'),
    Variable('baseStrength', int, 'The base strength of this mutation\'s attack/heal/buff'),
    Variable('maxStrength',  int, 'The power of this plant\'s attack/heal/buff'),

    Variable('maxStorage', int, 'The power of this Plant mutation\'s attack.'),


    ],
  doc='Represents a mutation of Plant.',
  functions=[],
  permanent = True,
  )

move = Animation('move',
  data=[
    Variable('actingID', int),
    Variable('fromX', int),
    Variable('fromY', int),
    Variable('toX', int),
    Variable('toY', int)
  ],
  )

attack = Animation('attack',
  data=[
    Variable('actingID', int),
    Variable('targetID', int)
  ],
  )

repair = Animation('repair',
  data=[
    Variable('actingID', int),
    Variable('targetID', int)
  ],
  )

hack = Animation('hack',
  data=[
    Variable('actingID', int),
    Variable('targetID', int)
  ],
  )

spawn = Animation('spawn',
  data=[
    Variable('sourceID', int),
    Variable('unitID', int)
  ],
  )

orbitalDrop = Animation('orbitalDrop',
  data=[
    Variable('sourceID', int)
  ],
  )
