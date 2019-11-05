from gi.repository import Gtk
import datetime

from examples.example1 import Example1
from examples.example2 import Example2
from examples.example3 import Example3
import load_simulation
from display import Display
from user_interface import UserInterface
from component_list import ComponentList

class EventHandler:
  def __init__(self, builder):
    self.current_simulation = None
    self.current_file = None
    self.ui = UserInterface()
    self.cl = ComponentList()
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
    self.current_simulation = Example2(self)

  def load_example_three(self, button):
    self.current_simulation = Example3(self)

  def save_simulation(self, button):
    self.current_simulation.save_to_file("example_one")

  def run_simulation(self, button):
    if self.current_simulation != None:
      self.current_simulation.run()
    else:
      self.print_to_log("Error: There's no model defined, so a simulation cannot be executed.")

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

  def save_as(self, button):
    self.show_save_file_chooser(button)
  
  def save(self, button):
    if self.current_file == None:
      self.show_save_file_chooser(button)
    else:
      self.save_file(button)

  def hide_open_file_chooser(self, button):
    self.ui.open_file_chooser.hide()

  def hide_save_file_chooser(self, button):
    self.ui.save_file_chooser.hide()

  def choose_file(self, button):
    self.ui.open_file_chooser.hide()
    file_path = self.ui.open_file_chooser.get_filename()
    load_simulation.run_simulation(self, file_path)

  def save_file(self, button):
    if self.current_simulation == None:
      self.print_to_log("Error: There's no model to be saved.")
    else:
      folder = self.ui.save_file_chooser.get_current_folder()
      file_name = self.ui.save_file_chooser.get_current_name()

      if file_name[-4:] != ".txt":
        file_name += ".txt"
      
      file_path = folder + "/" + file_name
      self.current_simulation.save_to_file(file_path)
      self.current_file = file_path
      self.print_to_log(file_path)

    self.ui.save_file_chooser.hide()

  def edit_component(self, tree_view, path, column):
    tree_selection = tree_view.get_selection()
    selected = tree_selection.get_selected()
    self.print_to_log(selected[0].get_value(selected[0].get_iter(path), 2))
    # print(self.cl.component_dict)
    # print(str(path))
