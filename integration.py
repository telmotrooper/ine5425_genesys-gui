from io import BytesIO
from ctypes import CDLL, c_char_p
from stdout_redirector import stdout_redirector

class Integration:
  # Class attributes
  libgenesys = CDLL("./genesys/dist/Debug/GNU-Linux/libgenesys.so") 

  def __init__(self, handler):
    Integration.handler = handler

    # Functions
    get_simulator_instance = Integration.libgenesys.getSimulatorInstance
    get_model_instance     = Integration.libgenesys.getModelInstance
    
    # Response types
    get_simulator_instance.restype = c_char_p
    get_model_instance.restype     = c_char_p

    f = BytesIO()
    with stdout_redirector(f):
      Integration.simulator = get_simulator_instance()
      Integration.model = get_model_instance(Integration.simulator)
      Integration.tm = Integration.model.getTraceManager()
    handler.print(f.getvalue().decode('utf-8'))
