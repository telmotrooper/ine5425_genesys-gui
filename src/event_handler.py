from gi.repository import Gtk
import datetime

from examples.example1 import Example1
from examples.example2 import Example2
import load_simulation
from display import Display
from user_interface import UserInterface


class EventHandler:
  def __init__(self, builder):
    self.current_simulation = None
    self.ui = UserInterface()
    self.display = Display(self.ui.drawing_area)

    # Connecting events to UI elements
    self.ui.open_file_chooser.connect("file-activated", self.choose_file)
  
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

  def load_example_one(self, button):
    self.current_simulation = Example1(self)

  def load_example_two(self, button):
    simulation = Example2(self)

  def save_simulation(self, button):
    self.current_simulation.save_to_file("example_one")

  def run_simulation(self, button):
    self.current_simulation.run()

  def show_about_dialog(self, button):
    self.ui.about_dialog.show_all()
    self.ui.about_dialog.connect("delete-event", lambda w, e: w.hide() or True)
  
  def hide_about_dialog(self, dialog, value):
    self.ui.about_dialog.hide()

  def show_open_file_chooser(self, button):
    self.ui.open_file_chooser.show_all()
    self.ui.open_file_chooser.connect("delete-event", lambda w, e: w.hide() or True)
  
  def show_save_file_chooser(self, button):
    self.ui.save_file_chooser.show_all()
    self.ui.save_file_chooser.connect("delete-event", lambda w, e: w.hide() or True)

  def hide_open_file_chooser(self, button):
    self.ui.open_file_chooser.hide()

  def hide_save_file_chooser(self, button):
    self.ui.save_file_chooser.hide()

  def choose_file(self, button):
    self.ui.open_file_chooser.hide()
    file_path = self.ui.open_file_chooser.get_filename()
    load_simulation.run_simulation(self, file_path)

  def save_file(self, button):
    folder = self.ui.save_file_chooser.get_current_folder()
    file_name = self.ui.save_file_chooser.get_current_name()

    if file_name[-4:] != ".txt":
      file_name += ".txt"
    
    self.current_simulation.save_to_file(folder + "/" + file_name)
    self.print_to_log(folder + "/" + file_name)
    self.ui.save_file_chooser.hide()

  def edit_component(self, tree_view, path, column):
    self.print_to_log(str(path))
