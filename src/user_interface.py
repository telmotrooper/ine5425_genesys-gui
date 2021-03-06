import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GdkPixbuf

class UserInterface:  # Singleton
  instance = None

  def __init__(self, builder=None):
    if not UserInterface.instance and builder is not None:
      UserInterface.instance = UserInterface.__UserInterface(builder)

  def __getattr__(self, name):
    return getattr(UserInterface.instance, name)

  # Internal class
  class __UserInterface:
    def __init__(self, builder):
      if (type(builder) is Gtk.Builder):
        self.builder = builder
        # Elements
        self.log = builder.get_object("log")
        self.about_dialog = builder.get_object("about_dialog")
        self.list_store = builder.get_object("list_store")
        self.open_file_chooser = builder.get_object("open_file_chooser")
        self.save_file_chooser = builder.get_object("save_file_chooser")
        self.drawing_area = builder.get_object("drawing_area")
        self.tree_view = builder.get_object("tree_view")
