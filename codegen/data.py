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
  Variable('bumbleweedSpeed', int, 'The maximum distance that a bumbleweed can move during an uproot'),
  Variable('poolDamage', int, 'The damage taken from standing in a pool'),
  Variable('poolBuff', int, 'The strength buff taken from standing in a pool'),
  Variable('sporeRate', int, 'The rate which your spores return to maxSpores'),
  Variable('maxSpores', int, 'The maximum number of spores a player can have'),
  Variable('uprootRange', int, 'The maximum range which a plant can move'),
]

playerData = [
  Variable('spores', int, 'Number of spores this player has to spawn a new unit')
  ]

playerFunctions = [
  Function('germinate', [Variable('x', int), Variable('y', int), Variable('mutation', int)],
  doc='Allows a player to germinate a new Plant.'),
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

    Variable('rads', int, 'The current amount of radiation this Plant has.'),
    Variable('maxRads', int, 'The maximum amount of radiation this Plant can have before dying.'),

    Variable('radiatesLeft', int, 'The remaining number of times the plant can radiate.'),
    Variable('maxRadiates', int, 'The maximum number of times the plant can radiate.'),

    Variable('range', int, 'The maximum range this plant can radiate.'),
    
    Variable('uprootsLeft', int, 'The remaining number of times this plant can be uprooted.'),
    Variable('maxUproots', int, 'The maximum number of times this plant can be uprooted.'),

    Variable('strength',     int, 'The current power of this plant.'),
    Variable('minStrength',  int, 'The minimum power of this plant.'),
    Variable('baseStrength', int, 'The base power of this plant.'),
    Variable('maxStrength',  int, 'The maximum power of this plant.'),

    ],
  doc='Represents a single Plant on the map.',
  functions=[
    Function('talk', [Variable('message', str)],
    doc='Allows a plant to display messages on the screen'),

    Function('radiate', [Variable('x', int), Variable('y', int)],
    doc='Command to radiate (heal, attack) another Plant.'),

    Function('uproot', [Variable('x', int), Variable('y', int)],
    doc='Command to uproot a plant and move to a new location.'),
  ],
)

#MUTATIONSPECIFICATION
Mutation = Model('Mutation',
  data = [
    Variable('name', str, 'The name of this mutation of Plant.'),
    Variable('type', int, 'The mutation of this Plant. This value is unique for all Mutations.'),
    Variable('spores', int, 'The current amount of radiation this Plant has.'),

    Variable('maxRadiates', int, 'The maximum number of times the Plant can radiate.'),

    Variable('maxRads', int, 'The maximum amount of radiation this Plant can have before dying.'),

    Variable('range', int, 'The maximum range this plant can radiate.'),

    Variable('maxUproots', int, 'The maximum number of times this plant can be uprooted.'),

    Variable('minStrength',  int, 'The minimum power of this plant.'),
    Variable('baseStrength', int, 'The base power of this plant.'),
    Variable('maxStrength',  int, 'The maximum power of this plant.'),

    ],
  doc='Represents a mutation of Plant.',
  functions=[],
  permanent = True,
  )

move = Animation('uproot',
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

heal = Animation('heal',
  data=[
    Variable('actingID', int),
    Variable('targetID', int)
  ],
  )

soak = Animation('soak',
  data=[
    Variable('actingID', int),
    Variable('targetID', int)
  ],
  )

germinate = Animation('germinate',
  data=[
    Variable('actingID', int),
    Variable('x', int),
    Variable('y', int)
  ],
  )

plantTalk = Animation('plantTalk',
  data=[
    Variable('actingID', int),
    Variable('message', str)
  ],
  )
