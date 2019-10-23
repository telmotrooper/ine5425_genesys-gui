import cairo

class Display:
  def __init__(self, da):
    Display.da = da
    Display.da.connect("draw", self.draw)
    Display.da.set_size_request(1250, 750)
  
  def redraw(self):
    self.da.queue_draw()
  
  def draw(self, da, ctx):
    ctx.set_source_rgb(255, 255, 255)  # color white
    ctx.paint()

    image = cairo.ImageSurface.create_from_png("icons/icon-256.png")
    ctx.set_source_surface(image, 0, 0)
    ctx.paint()
