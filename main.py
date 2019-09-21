#!/usr/bin/env python3

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GdkPixbuf
from ctypes import *
from contextlib import redirect_stdout
import io
from stdout_redirector import stdout_redirector

from handler import Handler

def main():
  libgenesys = CDLL("./genesys/dist/Debug/GNU-Linux/libgenesys.so")

  builder = Gtk.Builder()
  builder.add_from_file("user_interface.glade")
  handler = Handler(builder)
  builder.connect_signals(handler)

  f = io.BytesIO()
  
  with stdout_redirector(f):
    libgenesys.getSimulatorInstance()
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
