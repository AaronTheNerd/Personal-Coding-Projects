import gi
import time
from animation import Animation, Frame, Color
from animationIO import importAnimation, exportAnimation

# Global Variables
animation = Animation()
index = 0
copy_frame = Frame()



class EventHandler(object):
    def onDestroy(self, *args):
        Gtk.main_quit()

    # File IO
    def importClicked(self):
        # Open File System
        global animation
        global index
        index = 0
        filepath = 'out'
        animation = importAnimation(filepath)

    def exportClicked(self, button):
        global animation
        exportAnimation(animation)
        # Tell user if the export completed successfully

    # Frame Movement
    def prevClicked(self, button):
        global index
        if index > 0:
            index -= 1
            # Update Everything

    def nextClicked(self, button):
        global animation
        global index
        index += 1
        if index == len(animation.frames):
            animation.frames.append(Frame())
        # Update Everything

    def copyClicked(self, button):
        global animation
        global index
        global copy_frame
        copy_frame = animation.frames[index]

    def pasteClicked(self, button):
        global animation
        global index
        global copy_frame
        animation.frames[index] = copy_frame
        # Update Everything

    def insertClicked(self, button):
        global animation
        global index
        index += 1
        animation.frames.insert(index, Frame())
        # Update Everything

    def deleteClicked(self, button):
        global animation
        global index
        animation.frames.pop(index)
        # Update Everything

    # Parameter Changing
    def holdChanged(self, entry):
        global animation
        global index
        animation.frames[index].hold = int(Gtk.get_event_widget().get_text())

    def repeatChanged(self, entry):
        global animation
        animation.repeat = int(Gtk.get_event_widget().get_text())

    def fillColorSet(self, color_button):
        global animation
        global index
        gtk_color = Gtk.get_event_widget().get_rgba()
        color = Color(int(gtk_color.red * 255), int(gtk_color.green * 255), int(gtk_color.blue * 255))
        for i in range(50):
            animation.frames[index].leds[i] = color
        # Update Everything

    # LED modification
    def ledColorSet(self, color_button):
        color_button.get_name()

    # Playback
    def playClicked(self, button):
        global animation
        for frame in animation.frames:
            # Update Everything
            time.sleep(frame.hold)
        # Update Everything

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk
def main():
    builder = Gtk.Builder()
    builder.add_from_file("config.glade")
    builder.connect_signals(EventHandler())
    window = builder.get_object("Window")
    window.show_all()
    Gtk.main()

if __name__ == "__main__":
    main()
    