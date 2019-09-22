#!/usr/bin/env python3

import gi
import io

gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GdkPixbuf
from ctypes import CDLL, c_char_p
import ctypes

from stdout_redirector import stdout_redirector
from handler import Handler


def main():
    libgenesys = CDLL("./genesys/dist/Debug/GNU-Linux/libgenesys.so")
    get_simulator_instance = libgenesys.getSimulatorInstance
    get_simulator_instance.restype = c_char_p

    builder = Gtk.Builder()
    builder.add_from_file("user_interface.glade")
    handler = Handler(builder)
    builder.connect_signals(handler)

    f = io.BytesIO()

    with stdout_redirector(f):
        simulator = get_simulator_instance()
        model = libgenesys.getModelInstance(simulator)
    handler.print(f.getvalue().decode('utf-8'))

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
