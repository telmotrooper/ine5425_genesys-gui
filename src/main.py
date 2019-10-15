#!/usr/bin/env python3

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GdkPixbuf
import sys
from io import BytesIO
from stdout_redirector import stdout_redirector
from handler import Handler

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

    simulator = None
    model = None
    tm = None

    f = BytesIO()
    with stdout_redirector(f):
        simulator = libgenesys.Simulator()
        model = libgenesys.Model(simulator)
        tm = model.getTraceManager()
        components = model.getComponentManager()
        elements = model.getElementManager()

    handler.print(f.getvalue().decode('utf-8'))
    handler.print(f"Model ID: {model.getId()}")
    model.loadModel("genesys/models/model01_CreDelDis.txt")

    Gtk.main()


if __name__ == "__main__":
    main()
