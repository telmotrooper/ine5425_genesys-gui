#!/usr/bin/env python3

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GdkPixbuf
from ctypes import *

from handler import Handler

def main():
    libgenesys = CDLL("./genesys/dist/Debug/GNU-Linux/libgenesys.so")
    libgenesys.getSimulatorInstance()
    
    builder = Gtk.Builder()
    builder.add_from_file("user_interface.glade")
    builder.connect_signals(Handler(builder))

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

    Gtk.main()

if __name__ == "__main__":
    main()
