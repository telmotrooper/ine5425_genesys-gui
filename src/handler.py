from gi.repository import Gtk
import datetime

import example_simulation_1
import file_handler

class Handler:
  def __init__(self, builder):
    self.builder = builder
    self.log = builder.get_object("log")
    self.about_dialog = self.builder.get_object("about_dialog")
    self.file_chooser = self.builder.get_object("file_chooser")
  
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
    self.about_dialog.show_all()
    self.about_dialog.connect("delete-event", lambda w, e: w.hide() or True)
  
  def show_file_chooser(self, button):
    self.file_chooser.show_all()
    self.file_chooser.connect("delete-event", lambda w, e: w.hide() or True)
  
  def hide_file_chooser(self, button):
    self.file_chooser.hide()

  def choose_file(self, button):
    self.file_chooser.hide()
    file_path = self.file_chooser.get_filename()
    file_handler.run_simulation(self, file_path)
