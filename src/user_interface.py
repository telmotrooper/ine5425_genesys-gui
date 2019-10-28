import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GdkPixbuf

class UserInterface:  # Singleton
  instance = None

  # Internal class
  class __UserInterface:
    def __init__(self, builder):
      if (type(builder) is Gtk.Builder):
        self.builder = builder
        # Elements
        self.log = builder.get_object("log")
        self.about_dialog = builder.get_object("about_dialog")
        self.list_store = builder.get_object("list_store")
        self.file_chooser = builder.get_object("file_chooser")
        self.drawing_area = builder.get_object("drawing_area")
        self.tree_view = builder.get_object("tree_view")

  def __init__(self, builder):
    if not UserInterface.instance:
      UserInterface.instance = UserInterface.__UserInterface(builder)

  def __getattr__(self, name):
    return getattr(UserInterface.instance, name)