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
        # Instantiate a simulator
        simulator = libgenesys.Simulator()

        # Create an empty model
        model = libgenesys.Model(simulator)

        # Should "handle traces and simulation events to output them"
        tm = model.getTraceManager()
        # this->setDefaultTraceHandlers(tm);

        # Get easy access to classes used to insert components and elements into a model
        components = model.getComponentManager()
        elements = model.getElementManager()

    # Print to GUI stuff that was just executed
    handler.print(f.getvalue().decode('utf-8'))

    # Set the trace level of the simulation
    simulator.getTraceManager().setTraceLevel(libgenesys.TraceLevel.mostDetailed)

    # Create a SourceModelElement of type EntityType, which will be used by a ModelComponent later
    entityType1 = libgenesys.EntityType(elements, "Type_of_Representative_Entity")
    elements.insert(entityType1.getTypename(), entityType1)

    # Create a ModelComponent of type Create, used to insert entities into the model
    create1 = libgenesys.Create(model)
    create1.setEntityType(entityType1)
    create1.setTimeBetweenCreationsExpression("1.5")
    components.insert(create1)

    # Create a ModelComponent of type Delay, used to represent a time delay
    delay1 = libgenesys.Delay(model)  # By default delay takes 1 second
    components.insert(delay1)

    # Create a SinkModelComponent of type Dispose, used to remove entities from the model
    dispose1 = libgenesys.Dispose(model)
    components.insert(dispose1)

    # Connect model components to create a "workflow". Should always start from
    # a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    create1.getNextComponents().insert(delay1)
    delay1.getNextComponents().insert(dispose1)

    # Insert the model into the simulator 
    simulator.getModelManager().insert(model)

    # If the model is ok then save the model into a text file 
    # if(model.checkModel()):
        # model.saveModel("./temp/firstExampleOfSimulation.txt")
        # If the model is saved into a file, it can be just loaded instead of built

    # // execute the simulation util completed and show the report
    # model->getSimulation()->startSimulation();

    Gtk.main()


if __name__ == "__main__":
    main()
