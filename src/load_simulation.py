from io import BytesIO
from stdout_redirector import stdout_redirector
import libgenesys

def run_simulation(handler, file):
  f = BytesIO()

  with stdout_redirector(f):
    # Instantiate a simulator
    simulator = libgenesys.Simulator()
    
    simulator.getModelManager().loadModel(file)

    model = simulator.getModelManager().current()

    libgenesys.PyGenesysApplication().insertFakePluginsByHand(simulator)

    # Should "handle traces and simulation events to output them"
    tm = model.getTraceManager()
    libgenesys.PyGenesysApplication().setDefaultTraceHandlers(tm);

    # Set the trace level of the simulation
    simulator.getTraceManager().setTraceLevel(libgenesys.TraceLevel.blockArrival)

    # Execute the simulation util completed and show the report
    model.getSimulation().startSimulation()

  # Print to GUI stuff that was just executed
  handler.print_to_log(f.getvalue().decode('utf-8'))
