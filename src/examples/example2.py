from stdout_redirector import stdout_redirector
from component_list import ComponentList
from simulation import Simulation
import libgenesys

class Example2(Simulation):
  def __init__(self, handler):
    super().__init__(handler)
  
  def prepare_simulation(self):
    simulator = self.simulator

    with stdout_redirector(self.stream):
      libgenesys.PyGenesysApplication().insertFakePluginsByHand(simulator)

      # Create an empty model
      self.model = libgenesys.Model(simulator)

      # Should "handle traces and simulation events to output them"
      tm = self.model.getTraceManager()
      libgenesys.PyGenesysApplication().setDefaultTraceHandlers(tm);

      # Get easy access to classes used to insert components and elements into a model
      components = self.model.getComponentManager()
      elements = self.model.getElementManager()

      # Set the trace level of the simulation
      simulator.getTraceManager().setTraceLevel(libgenesys.TraceLevel.blockArrival)

      # Create a SourceModelElement of type EntityType, which will be used by a ModelComponent later
      entityType1 = libgenesys.EntityType(elements, "Type_of_Representative_Entity")
      elements.insert(entityType1.getTypename(), entityType1)

      # Create a ModelComponent of type Create, used to insert entities into the model
      create1 = libgenesys.Create(self.model)
      create1.setEntityType(entityType1)
      create1.setTimeBetweenCreationsExpression("1.5")
      components.insert(create1)

      # Create a ModelComponent of type Delay, used to represent a time delay
      delay1 = libgenesys.Delay(self.model)  # By default delay takes 1 second
      components.insert(delay1)

      # Create a SinkModelComponent of type Dispose, used to remove entities from the model
      dispose1 = libgenesys.Dispose(self.model)
      components.insert(dispose1)

      # Connect model components to create a "workflow". Should always start from
      # a SourceModelComponent and end at a SinkModelComponent (it will be checked)
      create1.getNextComponents().insert(delay1)
      delay1.getNextComponents().insert(dispose1)

      # Insert the model into the simulator 
      self.simulator.getModelManager().insert(self.model)

      # Insert components into GUI list
      self.cl.insert(create1)
      self.cl.insert(delay1)
      self.cl.insert(dispose1)

      # If the model is ok then save it into a text file 
      # if self.model.checkModel():
      #     self.model.saveModel("src/models/example_1.txt") # Assuming you're running from root folder
          # If the model is saved into a file, it can be just loaded instead of built

      # Execute the simulation util completed and show the report
      self.model.getSimulation().startSimulation()

    # Print to GUI stuff that was just executed
    self.handler.print_to_log(f.getvalue().decode('utf-8'))
