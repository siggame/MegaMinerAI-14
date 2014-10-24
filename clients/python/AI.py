#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
import random

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Shell AI"

  meh = 1

  @staticmethod
  def password():
    return "password"

  ##This function is called once, before your first turn
  def init(self):
    if self.playerID == 1:
      self.meh = -1
    pass

  ##This function is called once, after your last turn
  def end(self):
    pass

  ##This function is called each time it is your turn
  ##Return true to end your turn, return false to ask the server for updated information
  def run(self):
    for plant in self.plants:
      if plant.owner == self.playerID:
        if plant.mutation == 0 or plant.mutation == 1:
          self.players[self.playerID].germinate(plant.x + self.meh * plant.range, plant.y, 1)
          self.players[self.playerID].germinate(plant.x + self.meh * plant.range - 2, plant.y, 5)
        elif plant.maxRadiates > 0:
          for plant2 in self.plants:
            if plant2.owner != self.playerID:
              plant.radiate(plant2.x, plant2.y)
    return 1

  def __init__(self, conn):
    BaseAI.__init__(self, conn)
