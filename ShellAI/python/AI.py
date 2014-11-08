#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
import random
import math

def distance(c1, c2):
    return math.floor( math.sqrt( (c1[0]-c2[0])**2 + (c1[1]-c2[1])**2 ) )

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Shell AI"

  @staticmethod
  def password():
    return "password"

  ##This function is called once, before your first turn
  def init(self):
    self.MUT = {}
    for m in self.mutations:
        self.MUT[m.name] = m 

  ##This function is called once, after your last turn
  def end(self):
    pass

  ##This function is called each time it is your turn
  ##Return true to end your turn, return false to ask the server for updated information
  def run(self):
    if self.playerID == 0:
        direction = 1
    else:
        direction = -1  
 
    myspawns = []
    first = True

    print len(self.plants)

    for spwn in self.plants:
        #Filter down to my spawners
        if spwn.owner != self.playerID:
            continue
        if spwn.mutation != self.MUT['Mother'].type and spwn.mutation != self.MUT['Spawner'].type:
            continue

        d = int(math.sqrt((self.MUT['Spawner'].range**2)/2)-1) * direction

        # Location of spawner
        
        
        if self.MUT['Spawner'].spores <= self.players[self.playerID].spores:
            if not self.players[self.playerID].germinate(spwn.x+d, spwn.y, self.MUT['Spawner'].type):
                if self.MUT['Choker'].spores <= self.players[self.playerID].spores:
                    self.players[self.playerID].germinate(spwn.x+d, spwn.y+d, self.MUT['Choker'].type)
        
        myspawns.append(spwn)

    for chkr in self.plants:
        if chkr.owner != self.playerID:
            continue
        if chkr.mutation != self.MUT['Choker'].type:
            continue 
    
        for plant in self.plants:
            if plant.owner == self.playerID:
                continue
            if plant.mutation == self.MUT['Pool'].type:
                continue
            if chkr.radiatesLeft <= 0:
                continue
            if distance( (plant.x, plant.y), (chkr.x,chkr.y) ) <= chkr.range:
                chkr.radiate(plant.x, plant.y)
        
        if chkr.uprootsLeft <= 0:
            continue
        
        d = int(math.sqrt((self.MUT['Spawner'].range**2)/2)-1) * direction
        
        spwn = min(myspawns, key=lambda x: distance( (x.x, x.y), (chkr.x, chkr.y) ))
       
        d *= random.random()
        d = int(d)
    
        if distance( (chkr.x, chkr.y), (spwn.x, spwn.y) ) <= spwn.range:
            chkr.uproot(spwn.x+d, spwn.y+d)
        

    return 1

  def __init__(self, conn):
    BaseAI.__init__(self, conn)
