import random 

class Space:

  def __init__(self, shape: tuple):
    self.shape = shape

  def sample(self):
    sample = []
    for dimension in self.shape:
      sample.append(random.randint(0, dimension - 1))
    
    return tuple(sample)

  def __iter__(self):
    self.iterator = [0] * len(self.shape)
    return self 

  def __next__(self) -> tuple:
    x = self.iterator.copy()
    self.__update_next_dimension__(len(self.shape) - 1)

    return tuple(x)
  
  def __update_next_dimension__(self, dimension_index: int) -> None:
    if dimension_index < 0:
      raise StopIteration

    self.iterator[dimension_index] += 1

    # if current dimension has reached 'limit', then increment next dimension
    if self.iterator[dimension_index] == self.shape[dimension_index]:
      self.iterator[dimension_index] = 0
      self.__update_next_dimension__(dimension_index - 1)