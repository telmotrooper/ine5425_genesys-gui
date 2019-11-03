from component_list import ComponentList
import libgenesys

class Simulation:
  def __init__(self, handler):
    self.handler = handler
    self.cl = ComponentList()
    self.simulator = libgenesys.Simulator()
    libgenesys.PyGenesysApplication().insertFakePluginsByHand(self.simulator)
    # A "self.model" object also has to be defined, but we'll leave that to the child

  def prepareSimulation(self):
    pass

  def loadFromFile(self):
    pass

  def saveToFile(self):
    if self.model.checkModel():
      self.model.saveModel("src/models/example_1.txt") # Assuming you're running from root folder

  def run(self):
    self.model.getSimulation().startSimulation()

  def addComponent(self):
    pass

  def editComponent(self):
    pass
