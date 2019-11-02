import cairo
from os import path
from graphviz import Digraph

class Display:  # Singleton
  instance = None

  def __init__(self, da=None):
    if not Display.instance and da is not None:
      Display.instance = Display.__Display(da)

  def __getattr__(self, name):
    return getattr(Display.instance, name)

  # Internal class
  class __Display:
    def __init__(self, da):
      Display.da = da
      Display.da.connect("draw", self.draw)
    
    def redraw(self):
      self.da.queue_draw()
    
    def draw(self, da, ctx):
      ctx.set_source_rgb(255, 255, 255)  # color white
      ctx.paint()

      diag = self.generate_diagram()
      image = cairo.ImageSurface.create_from_png(diag)

      ctx.set_source_surface(image, 0, 0)
      ctx.paint()
    
    def generate_diagram(self):
      dot = Digraph(comment='The Round Table')
      dot.node('A', 'King Arthur')
      dot.node('B', 'Sir Bedevere the Wise')
      dot.node('L', 'Sir Lancelot the Brave')
      dot.edges(['AB', 'AL'])
      dot.edge('B', 'L', constraint='false')
      dot.render(filename="diagram", directory="temp", format="png")

      return path.abspath(path.join(path.dirname(__file__), "../temp/diagram.png"))
