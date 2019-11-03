import cairo
from component_list import ComponentList
from os import path

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
      self.da = da
      self.da.connect("draw", self.draw)
      self.ci = ComponentList()
    
    def draw(self, da, ctx):
      ctx.set_source_rgb(255, 255, 255)  # color white
      ctx.paint()

      diag = self.ci.generate_diagram()

      if(diag):
        image = cairo.ImageSurface.create_from_png(diag)
        adj = 15
        self.da.set_size_request(image.get_width()+adj, image.get_height()+adj)
        ctx.set_source_surface(image, adj, adj)
        ctx.paint()
