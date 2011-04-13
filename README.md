
##rFactor HUD Plugin#

###HUD for 7" Display#
The client is designed for those USB 7" LCD displays for around $100USD (2010/2011). It outputs a fixed resolution though positioning the window needs work. It's funtional in that it retrieves and displays data as output by the game accurately however it could be more human friendly by remembering values when you go back to pits etc.

###Artist needed#
From here I'm trying to get designs, I need a car graphic with sprites such as sparks from bottoming out, wheels losing traction, flicking up dirt, brakes glowing etc etc.  Idea being that when certain conditions are met I can overlay the sprites on the graphic. Numerical data just isn't practical. Also need a better display, need to go much bigger writing.

###rFactor plugin#
Currently the rFactor side is pretty much complete, it exports everything... that could be culled once you know exactly what you want.  I've not seen any performance decrease due to this plugin so far, though it's only been tested on a handful of PCs.

There's interest in a G25 rFactor display which could be implemented as a client to this plugin. If someone with G25 would like to try I'll be happy to help wherever I can, and hey it's worth trying... if someone wants to buy me a G25 I'll get to work right away :)

###Developer info#
The rFactor plugin opens a shared memory area and dumps data there, it uses a mutex to signal when there has been an update.  It only performs updates every 100ms or so (from memory).

The client uses SDL and is fixed resolution to suit the 7" displays, it waits on the mutex and grabs all the data the game has spat out and displays some of it to the screen.

I should clean this up, I just remembered it and thought I should post here at the very least so I have a back up. The plugin is Source/example.cpp and the client is in DisplayPanel. Everything else is related junk.



