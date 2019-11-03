from os import path
from user_interface import UserInterface
from graphviz import Digraph
import libgenesys

class ComponentList:  # Singleton
  instance = None

  def __init__(self):
    if not ComponentList.instance:
      ComponentList.instance = ComponentList.__ComponentList()

  def __getattr__(self, name):
    return getattr(ComponentList.instance, name)

  # Internal class
  class __ComponentList:
    def __init__(self):
      self.component_dict = dict()

    def insert(self, component):
      ui = UserInterface()
      text = component.show().split(",")

      nextText = ["=(End)"]

      if type(component) != libgenesys.Dispose:
        nextComponent = component.getNextComponents().front()
        nextText = nextComponent.show().split(",")

      # Add to list in GUI
      ui.list_store.append([
        text[1].split('"')[1],
        component.__class__.__name__,
        text[0].split("=")[1],
        nextText[0].split("=")[1]
      ])

      # Add to control dictionary
      self.component_dict[text[0].split("=")[1]] = {
        "name": text[1].split('"')[1],
        "type": component.__class__.__name__,
        "nextId": nextText[0].split("=")[1]
      }

      # Ask for a redraw to update GUI
      ui.drawing_area.queue_draw()

    def generate_diagram(self):
      if len(self.component_dict) == 0:
        return None
      
      dot = Digraph(comment="Genesys Model")
      dot.graph_attr["rankdir"] = "LR"

      for key in self.component_dict.keys():
        component = self.component_dict.get(key)
        attr = self.get_visual_attributes(component["type"])
        dot.node(key, component["name"],
          shape=attr["shape"],
          height=attr["height"],
          style=attr["style"],
          fillcolor=attr["fillcolor"],
          orientation=attr["orientation"]
        )
      
      for key in self.component_dict.keys():
        component = self.component_dict.get(key)
        if component["nextId"] and component["nextId"] != "(End)":
          dot.edge(key, component["nextId"])

      dot.render(filename="diagram", directory="temp", format="png")

      return path.abspath(path.join(path.dirname(__file__), "../temp/diagram.png"))


    def get_visual_attributes(self, componentType):
      if componentType == "Create":
        return {
          "shape": "cds",
          "height": ".8",
          "style": "filled",
          "fillcolor": "#fef6cd",
          "orientation": "0"
        }
      elif componentType == "Dispose":
        return {
          "shape": "cds",
          "height": ".8",
          "style": "filled",
          "fillcolor": "#fef6cd",
          "orientation": "90"
        }
      else:
        return {
          "shape": "rect",
          "height": ".8",
          "style": "filled",
          "fillcolor": "#fef6cd",
          "orientation": "0"
        }
