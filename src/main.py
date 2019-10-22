#!/usr/bin/env python3

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GdkPixbuf
import sys
from handler import Handler
import example_simulation_1
import file_handler

try:
    import libgenesys
except ModuleNotFoundError:
    print("Error: \"libgenesys.so\" not found in current directory")
    sys.exit()


def main():
    builder = Gtk.Builder()
    builder.add_from_file("user_interface.glade")
    handler = Handler(builder)
    builder.connect_signals(handler)

    window = builder.get_object("main_window")
    window.set_icon_list([
        GdkPixbuf.Pixbuf.new_from_file("icons/icon-16.png"),
        GdkPixbuf.Pixbuf.new_from_file("icons/icon-24.png"),
        GdkPixbuf.Pixbuf.new_from_file("icons/icon-32.png"),
        GdkPixbuf.Pixbuf.new_from_file("icons/icon-64.png"),
        GdkPixbuf.Pixbuf.new_from_file("icons/icon-128.png"),
        GdkPixbuf.Pixbuf.new_from_file("icons/icon-256.png"),
        GdkPixbuf.Pixbuf.new_from_file("icons/icon-512.png")
    ])
    window.maximize()
    window.show_all()

    # Running simulation
    # example_simulation_1.run_simulation(handler)
    file_handler.run_simulation(handler, "src/models/cancian_example_1.txt")

    Gtk.main()


if __name__ == "__main__":
    main()
