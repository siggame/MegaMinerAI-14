# -*- coding: iso-8859-1 -*-
from structures import *

aspects = ['timer']

gameName = "Plants"

constants = [
  ]

modelOrder = ['Player', 'Mappable', 'Plant', 'MutationSpecification']

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

#UNIT
Unit = Model('Unit',
  parent = Mappable,
  data = [
    Variable('owner', int, 'The owner of this Unit.'),
    Variable('mutation', int, 'The mutation of this Unit. This mutation refers to list of MutationSpecifications.'),

    Variable('rads', int, 'The current amount health this Unit has remaining.'),
    Variable('maxRads', int, 'The maximum amount of this health this Unit can have'),
    
    Variable('range', int, 'The maximum range this unit can attack/heal'),
    
    Variable('movementLeft', int, 'The distance this unit has left to move'),
    Variable('maxMovement', int, 'The maximum distance this unit can move each turn'),
    
    Variable('strength', int, 'The power of this unit\'s attack/heal/buff'),

    Variable('storage', int, 'The current amount of radiation this Unit can have'),
    Variable('maxStorage', int, 'The maximum amount of radiation this Unit can have'),

    Variable('sporeCost', int, 'The number of spores required to spawn this unit'),
    ],
  doc='Represents a single Unit on the map.',
  functions=[
    Function('radiate', [Variable('x', int), Variable('y', int)],
    doc='Command to radiate (heal, attack) another Unit.'),

    Function('talk', [Variable('message', str)],
    doc='Command for a plant to send a message.'),
  ],
)

#PLANT
Plant = Model('Plant',
  parent = Mappable,
  data = [
    Variable('owner', int, 'The owner of this Plant.'),
    Variable('mutation', int, 'The mutation of this Plant. This mutation refers to list of MutationSpecifications.'),

    Variable('rads', int, 'The current amount health this Plant has remaining.'),
    Variable('maxRads', int, 'The maximum amount of this health this Plant can have'),
    
    Variable('range', int, 'The maximum range this plant can attack/heal'),
    
    Variable('movementLeft', int, 'The distance this plant has left to move'),
    Variable('maxMovement', int, 'The maximum distance this plant can move each turn'),
    
    Variable('strength', int, 'The power of this plant\'s attack/heal/buff'),
    
    Variable('storage', int, 'The current amount of radiation this Plant can have'),
    Variable('maxStorage', int, 'The maximum amount of radiation this Plant can have'),
    ],
  doc='Represents a single Plant on the map.',
  functions=[
    Function('radiate', [Variable('x', int), Variable('y', int)],
    doc='Command to radiate (heal, attack) another Plant.'),
  ],
)

#MUTATIONSPECIFICATION
MutationSpecification = Model('MutationSpecification',
  data = [
    Variable('name', str, 'The name of this mutation of Plant.'),
    Variable('mutation', int, 'The MutationSpecification specific id representing this mutation of Plant.'),
    Variable('cost', int, 'The scrap cost to spawn this Plant mutation into the game.'),
    Variable('maxAttacks', int, 'The maximum number of times the Plant can attack.'),
    Variable('maxHealth', int, 'The maximum amount of this health this Plant can have'),
    Variable('maxMovement', int, 'The maximum number of moves this Plant can move.'),
    Variable('range', int, 'The range of this Plant\'s attack.'),
    Variable('attack', int, 'The power of this Plant mutation\'s attack.'),
    Variable('maxArmor', int, 'How much armor the Plant has which reduces damage taken.'),
    Variable('scrapWorth', int, 'The amount of scrap the Plant drops.'),
    Variable('turnsToBeHacked', int, 'The number of turns this unit will be hacked, if it is hacked. If 0, the Plant cannot be hacked.'),
    Variable('hacketsMax', int, 'The maximum number of hackets that can be sustained before hacked. If 0, the Plant cannot be hacked.')
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
