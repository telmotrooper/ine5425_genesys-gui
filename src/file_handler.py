from io import BytesIO
from stdout_redirector import stdout_redirector
import libgenesys

def run_simulation(handler, file):
  f = BytesIO()

  with stdout_redirector(f):
    # Instantiate a simulator
    simulator = libgenesys.Simulator()

    libgenesys.PyGenesysApplication().insertFakePluginsByHand(simulator)

    # Create an empty model
    model = libgenesys.Model(simulator)

    # Load model from file
    model.loadModel(file)

    # Should "handle traces and simulation events to output them"
    tm = model.getTraceManager()
    libgenesys.PyGenesysApplication().setDefaultTraceHandlers(tm);

    # Set the trace level of the simulation
    simulator.getTraceManager().setTraceLevel(libgenesys.TraceLevel.blockArrival)

    # Insert the model into the simulator 
    simulator.getModelManager().insert(model)

    # Execute the simulation util completed and show the report
    model.getSimulation().startSimulation()

  # Print to GUI stuff that was just executed
  handler.print(f.getvalue().decode('utf-8'))
