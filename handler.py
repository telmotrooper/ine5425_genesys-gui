from gi.repository import Gtk
import datetime

class Handler:
  def __init__(self, builder):
    self.builder = builder
    self.log = builder.get_object("log")

    self.print("Application started.")

  
  def on_destroy(self, *args):
    Gtk.main_quit()

  def print(self, text, end = "\n"):
    text_view, buffer = self.log, self.log.get_buffer()
    buffer.insert_at_cursor(
      "[" + str(datetime.datetime.now().strftime("%H:%M:%S")) + "] " + text + end
    )
    text_view.scroll_to_mark(buffer.get_insert(), 0, 0, 0, 0)
  
  def show_about_dialog(self, button):
    self.builder.get_object("about_dialog").show_all()
    self.builder.get_object("about_dialog").connect("delete-event", lambda w, e: w.hide() or True)
