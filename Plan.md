# Data in the EFL #

As described inside [EflIssues](http://code.google.com/p/efl-research/wiki/EflIssues), we have many data type around. Some optimised, some not. By merging them, we will be able to improve them on a global scale.

## The plan ##

  * Move Evas data type inside Evas\_Data.h.
  * Introduce Eina inside EFL libs CVS.
  * Provide a set of macros to replace Evas data type by Eina one.
  * Add recent data type to Eina (Evas\_Array, Evas\_StringShare at least).
  * Make Evas depend on Eina.
  * Do the same for Eet data type.
  * Provide a set of macros or functions that do the same for Ecore data.
  * Improve Eina List allocation to do some garbage collection and reduce memory hole.
  * Improve Eina List merge sort (I have a pending one on my disk that is even faster than the one we have).
  * Improve Eina plugins support.
  * Add static plugins support to Eina.
  * Move Evas plugins to Eina's one.
  * Move Ecore plugins to Eina's one.

# Evas Image and engine #

Evas Image support could benefit of some improvement as described in EflIssues.

## The plan ##

  * Add async preload request of image data to Evas.h.
  * Use Evas\_Cache\_Image and Evas\_Cache\_Engine\_Image directly in the different engine.
  * Add a program to share data pixels between Evas programs.
  * Add inside Evas a way to optionaly request data pixels from an outside program.
  * Add a program to request pixels from a server.
  * Add a new Evas engine that send Evas engine order to another computer.
  * Improve Evoak to receive Evas engine order and directly send them to any Evas engine. (That's the part I am not sure about).