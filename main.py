import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

from handler import Handler

def main():
    builder = Gtk.Builder()
    builder.add_from_file("user_interface.glade")
    builder.connect_signals(Handler())

    window = builder.get_object("main_window")
    window.maximize()
    window.show_all()

    Gtk.main()

if __name__ == "__main__":
    main()
