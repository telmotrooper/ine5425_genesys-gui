from stdout_redirector import stdout_redirector
from simulation import Simulation
import libgenesys

class Example3(Simulation):
  def __init__(self, handler):
    super().__init__(handler)
  
  def prepare_simulation(self):
    with stdout_redirector(self.stream):
      self.infos = self.model.getInfos()
      self.infos.setAnalystName("Your name")
      self.infos.setProjectTitle("The title of the project")
      self.infos.setDescription("This simulation model tests one of the most basic models possible.")
      self.infos.setReplicationLength(30)
      self.infos.setReplicationLengthTimeUnit(libgenesys.TimeUnit.minute)
      self.infos.setNumberOfReplications(3)

      # Create a SourceModelElement of type EntityType, which will be used by a ModelComponent later
      self.entityType1 = libgenesys.EntityType(self.elements, "Type_of_Representative_Entity")
      self.elements.insert(self.entityType1.getTypename(), self.entityType1)

      # Create a ModelComponent of type Create, used to insert entities into the model
      self.create1 = libgenesys.Create(self.model)
      self.create1.setEntityType(self.entityType1)
      self.create1.setTimeBetweenCreationsExpression("Expo(2)")
      self.create1.setTimeUnit(libgenesys.TimeUnit.minute)
      self.create1.setEntitiesPerCreation(1)
      self.components.insert(self.create1)

      # Create a ModelComponent of type Delay, used to represent a time delay
      self.delay1 = libgenesys.Delay(self.model)  # By default delay takes 1 second
      self.delay1.setDelayExpression("NORM(1,0.2)")
      self.delay1.setDelayTimeUnit(libgenesys.TimeUnit.minute)
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

    # Print to GUI stuff that was just executed
    self.write_to_log()
