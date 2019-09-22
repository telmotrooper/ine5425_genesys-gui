from io import BytesIO
from ctypes import CDLL, c_char_p
from stdout_redirector import stdout_redirector

class Integration:
  # Class attributes
  libgenesys = CDLL("./genesys/dist/Debug/GNU-Linux/libgenesys.so") 

  def __init__(self, handler):
    Integration.handler = handler  
    get_simulator_instance = Integration.libgenesys.getSimulatorInstance
    get_simulator_instance.restype = c_char_p

    f = BytesIO()
    with stdout_redirector(f):
      simulator = get_simulator_instance()
      model = Integration.libgenesys.getModelInstance(simulator)
    handler.print(f.getvalue().decode('utf-8'))
