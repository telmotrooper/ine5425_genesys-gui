from component_list import ComponentList
from stdout_redirector import stdout_redirector
from io import BytesIO
import libgenesys

class Simulation:
  def __init__(self, handler):
    self.handler = handler
    self.cl = ComponentList()
    self.stream = BytesIO()

    with stdout_redirector(self.stream):
      self.simulator = libgenesys.Simulator()
      libgenesys.PyGenesysApplication().insertFakePluginsByHand(self.simulator)
      # A "self.model" object also has to be defined, but we'll leave that to the child

      # Create an empty model
      self.model = libgenesys.Model(self.simulator)

      # Should "handle traces and simulation events to output them"
      self.tm = self.model.getTraceManager()

      libgenesys.PyGenesysApplication().setDefaultTraceHandlers(self.tm);

      # Get easy access to classes used to insert components and elements into a model
      self.components = self.model.getComponentManager()
      self.elements = self.model.getElementManager()

      # Set the trace level of the simulation
      self.simulator.getTraceManager().setTraceLevel(libgenesys.TraceLevel.blockArrival)
        
    self.write_to_log()

  def prepare_simulation(self):
    pass

  def load_from_file(self):
    pass

  def save_to_file(self, filename):
    with stdout_redirector(self.stream):
      if self.model.checkModel():
        self.model.saveModel("src/models/{}.txt".format(filename)) # Assuming you're running from root folder
    self.write_to_log()

  def run(self):
    with stdout_redirector(self.stream):
      self.model.getSimulation().startSimulation()
    self.write_to_log()

  def add_component(self):
    pass

  def edit_component(self):
    pass

  def write_to_log(self):
    self.handler.print_to_log(self.stream.getvalue().decode('utf-8'))
