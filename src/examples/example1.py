from io import BytesIO
from stdout_redirector import stdout_redirector
from component_list import ComponentList
from simulation import Simulation
import libgenesys

class Example1(Simulation):
  def __init__(self, handler):
    super().__init__(handler)
  
  def prepareSimulation(self):
    f = BytesIO()

    with stdout_redirector(f):
      # Set the trace level of the simulation
      self.simulator.getTraceManager().setTraceLevel(libgenesys.TraceLevel.blockArrival)

      # Create a SourceModelElement of type EntityType, which will be used by a ModelComponent later
      self.entityType1 = libgenesys.EntityType(self.elements, "Type_of_Representative_Entity")
      self.elements.insert(self.entityType1.getTypename(), self.entityType1)

      # Create a ModelComponent of type Create, used to insert entities into the model
      self.create1 = libgenesys.Create(self.model)
      self.create1.setEntityType(self.entityType1)
      self.create1.setTimeBetweenCreationsExpression("1.5")
      self.components.insert(self.create1)

      # Create a ModelComponent of type Delay, used to represent a time delay
      self.delay1 = libgenesys.Delay(self.model)  # By default delay takes 1 second
      self.components.insert(self.delay1)

      # Create a SinkModelComponent of type Dispose, used to remove entities from the model
      self.dispose1 = libgenesys.Dispose(self.model)
      self.components.insert(self.dispose1)

      # Connect model components to create a "workflow". Should always start from
      # a SourceModelComponent and end at a SinkModelComponent (it will be checked)
      self.create1.getNextComponents().insert(self.delay1)
      self.delay1.getNextComponents().insert(self.dispose1)

      # Insert the model into the simulator 
      self.simulator.getModelManager().insert(self.model)

      # Insert components into GUI list
      self.cl.insert(self.create1)
      self.cl.insert(self.delay1)
      self.cl.insert(self.dispose1)

      # If the model is ok then save it into a text file 
      # if self.model.checkModel():
      #     self.model.saveModel("src/models/example_1.txt") # Assuming you're running from root folder
          # If the model is saved into a file, it can be just loaded instead of built

      # Execute the simulation util completed and show the report
      self.model.getSimulation().startSimulation()

    # Print to GUI stuff that was just executed
    self.handler.print_to_log(f.getvalue().decode('utf-8'))
