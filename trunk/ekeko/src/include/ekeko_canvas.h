#ifndef EKEKO_CANVAS_H_
#define EKEKO_CANVAS_H_

typedef struct _Ekeko_Canvas_Private Ekeko_Canvas_Private;
typedef struct _Ekeko_Canvas
{
	int (*flush)(void *data, Eina_Rectangle *r);
	Ekeko_Canvas_Private *priv;
	/* what about the idle? */
	/* canvas_changed -> if some object has changed, then the canvas has changed, we could notify upward that so we can call
	 * the canvas_process
	 **/
} Ekeko_Canvas;

EAPI Ekeko_Canvas * ekeko_canvas_new(int type, int w, int h);
EAPI void ekeko_canvas_damage_add(Ekeko_Canvas *c, Eina_Rectangle *r);
EAPI void ekeko_canvas_obscure_add(Ekeko_Canvas *c, Eina_Rectangle *r);
EAPI void ekeko_canvas_obscure_del(Ekeko_Canvas *c, Eina_Rectangle *r);
EAPI void ekeko_canvas_process(Ekeko_Canvas *c);
EAPI void ekeko_canvas_geometry_get(Ekeko_Canvas *c, unsigned int *w, unsigned int *h);
EAPI void ekeko_canvas_geometry_set(Ekeko_Canvas *c, unsigned int w, unsigned int h);
EAPI void * ekeko_canvas_class_data_get(Ekeko_Canvas *c);
EAPI Ekeko_Object * ekeko_canvas_object_from_last_get(Ekeko_Canvas *c, Ekeko_Object_Cmp_Func cmp, void *data);
EAPI Ekeko_Object * ekeko_canvas_object_from_first_get(Ekeko_Canvas *c, Ekeko_Object_Cmp_Func cmp, void *data);

/** TODO
 * typedef enum _Ekeko_Canvas_Event
 * {
 * 	EKEKO_CANVAS_EVENT_RESIZE,
 * 	EKEKO_CANVAS_EVENTS,
 * } Ekeko_Canvas_Event;

/**
 * @}
 */


#endif /*EKEKO_CANVAS_H_*/
