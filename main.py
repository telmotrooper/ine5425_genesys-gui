import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

def main():
    builder = Gtk.Builder()
    builder.add_from_file("user_interface.glade")

    window = builder.get_object("main_window")
    window.show_all()

    Gtk.main()

if __name__ == "__main__":
    main()
