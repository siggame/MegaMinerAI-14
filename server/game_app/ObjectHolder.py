import objects

class ObjectHolder(dict):
  def __init__(self, *args, **kwargs):
    dict.__init__(self, *args, **kwargs)
    self.players = []
    self.mappables = []
    self.plants = []
    self.mutations = []

  def __setitem__(self, key, value):
    if key in self:
      self.__delitem__(key)
    dict.__setitem__(self, key, value)
    if isinstance(value, objects.Player):
      self.players.append(value)
    if isinstance(value, objects.Mappable):
      self.mappables.append(value)
    if isinstance(value, objects.Plant):
      self.plants.append(value)
    if isinstance(value, objects.Mutation):
      self.mutations.append(value)

  def __delitem__(self, key):
    value = self[key]
    dict.__delitem__(self, key)
    if value in self.players:
      self.players.remove(value)
    if value in self.mappables:
      self.mappables.remove(value)
    if value in self.plants:
      self.plants.remove(value)
    if value in self.mutations:
      self.mutations.remove(value)

  def clear(self):
    for i in self.keys():
      del self[i]
