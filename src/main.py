#!/usr/bin/env python3

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GdkPixbuf
import sys
from os import path
from event_handler import EventHandler
import example_simulation_1
import file_handler
from user_interface import UserInterface

try:
    import libgenesys
except ModuleNotFoundError:
    print("Error: \"libgenesys.so\" not found in current directory")
    sys.exit()


def main():
    base_path = path.abspath(path.join(path.dirname(__file__), ".."))

    # Load user interface
    builder = Gtk.Builder()
    builder.add_from_file(base_path + "/user_interface.glade")

    # Generate references for the elements
    UserInterface(builder)
    handler = EventHandler(builder)
    builder.connect_signals(handler)
    

    window = builder.get_object("main_window")
    window.set_icon_list([
        GdkPixbuf.Pixbuf.new_from_file(base_path + "/icons/icon-16.png"),
        GdkPixbuf.Pixbuf.new_from_file(base_path + "/icons/icon-24.png"),
        GdkPixbuf.Pixbuf.new_from_file(base_path + "/icons/icon-32.png"),
        GdkPixbuf.Pixbuf.new_from_file(base_path + "/icons/icon-64.png"),
        GdkPixbuf.Pixbuf.new_from_file(base_path + "/icons/icon-128.png"),
        GdkPixbuf.Pixbuf.new_from_file(base_path + "/icons/icon-256.png"),
        GdkPixbuf.Pixbuf.new_from_file(base_path + "/icons/icon-512.png")
    ])
    window.maximize()
    window.show_all()

    # Running simulation
    # example_simulation_1.run_simulation(handler)
    # file_handler.run_simulation(handler, "src/models/cancian_example_1.txt")

    Gtk.main()


if __name__ == "__main__":
    main()
