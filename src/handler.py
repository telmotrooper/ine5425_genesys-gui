from gi.repository import Gtk
import datetime
import example_simulation_1

class Handler:
  def __init__(self, builder):
    self.builder = builder
    self.log = builder.get_object("log")
  
  def on_destroy(self, *args):
    Gtk.main_quit()

  def print_to_log(self, text, end = "\n"):
    text_view, buffer = self.log, self.log.get_buffer()
    buffer.insert_at_cursor(
      "[" + str(datetime.datetime.now().strftime("%H:%M:%S")) + "] " + text + end
    )
    text_view.scroll_to_mark(buffer.get_insert(), 0, 0, 0, 0)

  def clear_log(self, button):
    buffer = self.log.get_buffer()
    bounds = buffer.get_bounds()
    buffer.delete(bounds.start, bounds.end)

  def run_example_one(self, button):
    example_simulation_1.run_simulation(self)

  def show_about_dialog(self, button):
    self.builder.get_object("about_dialog").show_all()
    self.builder.get_object("about_dialog").connect("delete-event", lambda w, e: w.hide() or True)
