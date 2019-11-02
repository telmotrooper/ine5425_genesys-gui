from gi.repository import Gtk
import datetime

import example_simulation_1
import file_handler
from display import Display
from user_interface import UserInterface


class EventHandler:
  def __init__(self, builder):
    self.ui = UserInterface()
    self.display = Display(self.ui.drawing_area)

    # Connecting events to UI elements
    self.ui.file_chooser.connect("file-activated", self.choose_file)
  
  def on_destroy(self, *args):
    Gtk.main_quit()

  def print_to_log(self, text, end = "\n"):
    text_view, buffer = self.ui.log, self.ui.log.get_buffer()
    buffer.insert_at_cursor(
      "[" + str(datetime.datetime.now().strftime("%H:%M:%S")) + "] " + text + end
    )
    text_view.scroll_to_mark(buffer.get_insert(), 0, 0, 0, 0)

  def clear_log(self, button):
    buffer = self.ui.log.get_buffer()
    bounds = buffer.get_bounds()
    buffer.delete(bounds.start, bounds.end)

  def run_example_one(self, button):
    example_simulation_1.run_simulation(self)

  def show_about_dialog(self, button):
    self.ui.about_dialog.show_all()
    self.ui.about_dialog.connect("delete-event", lambda w, e: w.hide() or True)
  
  def show_file_chooser(self, button):
    self.ui.file_chooser.show_all()
    self.ui.file_chooser.connect("delete-event", lambda w, e: w.hide() or True)
  
  def hide_file_chooser(self, button):
    self.ui.file_chooser.hide()

  def choose_file(self, button):
    self.ui.file_chooser.hide()
    file_path = self.ui.file_chooser.get_filename()
    file_handler.run_simulation(self, file_path)

  def edit_component(self, tree_view, path, column):
    self.print_to_log(str(path))
