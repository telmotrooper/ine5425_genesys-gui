import cairo
from os import path

class Display:
  def __init__(self, da):
    Display.da = da
    Display.da.connect("draw", self.draw)
  
  def redraw(self):
    self.da.queue_draw()
  
  def draw(self, da, ctx):
    ctx.set_source_rgb(255, 255, 255)  # color white
    ctx.paint()

    base_path = path.abspath(path.join(path.dirname(__file__), ".."))

    image = cairo.ImageSurface.create_from_png(base_path + "/icons/icon-256.png")
    ctx.set_source_surface(image, 0, 0)
    ctx.paint()
