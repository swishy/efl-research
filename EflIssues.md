# Ecore #

_Ecore_ currently has several **subsystems**, from basic data types (lists, double lists, ...) to specific purpose like _Ecore DirectFB_. As more subsystems get in the main _Ecore_, even if the different subsystems are well split (as they are now), the functionality of this library is far from its initial purpose and most of the subsystems can be another library.

## Ecore Plugin ##
_Ecore Plugin_ has several functions that load modules of compiled code into memory, i.e dynamically loading of application's plugins. It is written in a very generic way, but ironically almost all applications that use _Ecore_ as their main loop handler (or just data library) and have some kind of _module_ concept, **don't use _Ecore Plugin_ for this task but their own implementation**, namely:

(Ecore based applications/libraries)

  * Ewl
  * Etk
  * Etk Server
  * Entropy

(Not Ecore based applications/libraries)

  * Evas
  * Esmart Container
  * Imlib2

Doing a simple search for some libraries or applications that use _Ecore Plugin_ shows that  **there isn't any development that use it**.

Using the same Plugin technique it would be much more easy to add static module support to the EFL (We are loosing a lot of time during start up just doing link, that could be done once and for all in some case).

## Ecore Data ##

Is not really efficient to say the least, but it's used by other application like the one base on ewl. So we need to keep compatibility around for it, but still improve it.

# Evas #
Most of the ideas exposed here come from a couple of threads on the enlightenment-devel mailing list at http://sourceforge.net/mailarchive/message.php?msg_id=36565630 and http://sourceforge.net/mailarchive/message.php?msg_id=37463742

## Headers ##
Split huge headers (`Evas.h evas_common.h, etc`) into smaller ones.

## Data ##
Evas has a very good support for data types (Lists, Hashes, Stringshare and Object Lists) and honestly Evas has a very good performance and a well defined API, most of the E-developers agree on that. But is a problem that to use this data types on your application/library you have to link against Evas even if your development has nothing to do with Evas main purpose: graphics.

## Objects ##
Objects should be made loadable modules
New Object Types:
Filters
Proxies

We should make the polygons a first class citizen, so that they could be used more easily. This means cleaning up what they mean and make move/resize work on them.

We should define and give the possibility for smart object to use the render\_pre and render\_post if possible (during render\_pre you are not allowed to move/resize/show/hide other object, so I don't know if it would be really usefull).

We should fixe the text object support. It must be possible to include other evas object in the text path. It would be nice if the rendered text could follow some curve or some kind of non linear path.

## Engines ##
All engines should currently be developped inside Evas. Most of their code are just a copy/paste and a nightmare to maintain. Engine could be divided in two categorie:

  * the one than upload the pixels to the underlying system (OpenGL, Xrender, maybe Direct3D)
  * the one that have a direct access to the pixels (software\_x11, ddraw, sdl, WinCE)

And we have the corresponding two cache systems :
  * Evas\_Cache\_Engine\_Image for the first case
  * Evas\_Cache\_Image for the second case

But most engine didn't use them really. So instead of merging code we are duplicating effort for nothing and worse we are loosing speed for most engine.

We should also review the engine API to clean it up a bit.

I would like to make Evoak functionnality working with Evas again.

Evas should provide a way to change the orientation at runtime

## Images ##

Evas is all about image, but we have some serious limitation. We can't load/request image in the background and we dont share the pixels surface with other application.

Sharing image with other application means that we need some kind of daemon that will do the image loading and answer to evas request. I believe that for ease of implementation and security the daemon must be per users. But this function should stay pluggable and not an absolute need to evas, as it would impact speed and memory consumption when only one application is running.

Loading or requesting image in the background is absolutly needed if we want to do nice image viewer. It should stay optional as it will be in the critical path and we don't want to losse speed for this also. The logic behind this function is not linked with the previous, but they should work together.

And as image surface are not always "sharable" in the same way on all architecture/engine. It should be possible to easily plug our own mecanism on a per engine basis.

# Edje #

It does recalc every thing each time a little stuff change, that's why we need edje\_freeze/thaw. Their is no dependencies graph that would give us information about what need to be really recalc and during animation both start and end states are recalculated at each frame. This is a problem when you don't have FPU, you are loosing a lot of time doing the same math again and again.

Textblock support could be improved. It would be great if the object could be resized depending on it's content, so that we could make other object depend on it's size.

We should add Polygons object support when Evas API is fixed.

# Eet #

It would be nice to have the possibility to cypher each Eet directory with a different key
.

Having a way to sign an entire Eet file would be a nice feature too.

It would be good if we can add other dumper/undumper like a JSON/EET converter.

Would be good if we could pack audio and video stream inside eet.