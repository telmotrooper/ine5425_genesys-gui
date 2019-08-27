from gi.repository import Gtk

class Handler:
  def on_destroy(self, *args):
    Gtk.main_quit()
