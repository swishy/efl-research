#ifndef ESVG_CANVAS_H_
#define ESVG_CANVAS_H_

typedef struct _ESVG ESVG;

/* TODO add a struct to describe the engine_data
 * cairo for example should receive data based on the
 * backend cairo supports (x11 = dpy, etc, etc)
 * for enesim (sw only) we need the flush function: when the
 * backbuffer is drawn we need to flip it into the frontbuffer
 * + TODO how to handle relative coordinates? add callbacks when an object
 * is resized and moved and keep track of the union of every bounding box
 */ 

typedef enum _ESVG_Engine_Type
{
	ESVG_ENGINE_CAIRO,
	ESVG_ENGINE_ENESIM,
	ESVG_ENGINES,
} ESVG_Engine_Type;

EAPI ESVG * esvg_new(int w, int h, ESVG_Engine_Type type, void *engine_data);
EAPI esvg_damage_add(ESVG *e, ESVG_Coord x, ESVG_Coord y, ESVG_Length w, ESVG_Length h);
EAPI void esvg_free(ESVG *e);

#endif /*ESVG_CANVAS_H_*/