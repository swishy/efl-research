#include "Ekeko.h"
#include "ekeko_private.h"
/*============================================================================*
 *                                  Local                                     * 
 *============================================================================*/
static inline Eina_Bool _object_is_valid(Ekeko_Object *o)
{
	return o->valid;
}
static void _object_change(Ekeko_Object *o)
{
	if (o->changed == EINA_TRUE)
		return;
	o->changed = EINA_TRUE;
	if (o->valid)
	{
		printf("canvas changed!!\n");
		ekeko_canvas_change(o->canvas);
	}
}

/*============================================================================*
 *                                 Global                                     * 
 *============================================================================*/
void ekeko_object_event_callback_call(Ekeko_Object *o, Ekeko_Event_Type ect, Ekeko_Event *ev)
{
	Eina_Inlist *l;
	
	for (l = (Eina_Inlist *)o->callbacks[ect]; l; l = l->next)
	{
		Ekeko_Object_Cb *cb;
		cb = (Ekeko_Object_Cb *)l;
		
		//printf("calling callback for event %d\n", ect);
		cb->func(o->canvas, o, ev, cb->data);
	}
}
/**
 * To be documented
 * FIXME: To be fixed
 */
void ekeko_object_event_move_call(Ekeko_Object *o)
{
	Ekeko_Event ev;
	
	ekeko_object_event_callback_call(o, EKEKO_EVENT_MOVE, &ev);
}
/**
 * To be documented
 * FIXME: To be fixed
 */
void ekeko_object_event_resize_call(Ekeko_Object *o)
{
	Ekeko_Event ev;
	
	ekeko_object_event_callback_call(o, EKEKO_EVENT_RESIZE, &ev);
}
/**
 * To be documented
 * FIXME: To be fixed
 */
Eina_Bool ekeko_object_intersection_get(Ekeko_Object *o, Ekeko_Rectangle *r, Eina_Rectangle *drect)
{
	drect->x = o->curr.geometry.x;
	drect->y = o->curr.geometry.y;
	drect->w = o->curr.geometry.w;
	drect->h = o->curr.geometry.h;

	return eina_rectangle_intersection(drect, &r->r);
}
/**
 * To be documented
 * FIXME: To be fixed
 */
void ekeko_object_pre_process(Ekeko_Object *o)
{
	if (!o->valid)
		printf("error pre processing an invalid object\n");
	/* check visibility */
	if (o->curr.visible ^ o->prev.visible)
	{
		ekeko_tiler_rect_add(o->canvas->tiler, &o->prev.geometry);
		ekeko_tiler_rect_add(o->canvas->tiler, &o->curr.geometry);
		/* update the visibility */
		o->prev.visible = o->curr.visible;
		goto ok;
	}
	/* check geometry */
	if ((o->curr.geometry.x != o->prev.geometry.x) ||
			(o->curr.geometry.y != o->prev.geometry.y) ||
			(o->curr.geometry.w != o->prev.geometry.w) ||
			(o->curr.geometry.h != o->prev.geometry.h))
	{
		/* add both rectangles, previous and new */
		//printf("adding[1] %d %d %d %d\n", o->prev.geometry.x, o->prev.geometry.y, o->prev.geometry.w, o->prev.geometry.h);
		ekeko_tiler_rect_add(o->canvas->tiler, &o->prev.geometry);
		//printf("adding[2] %d %d %d %d\n", o->curr.geometry.x, o->curr.geometry.y, o->curr.geometry.w, o->curr.geometry.h);
		ekeko_tiler_rect_add(o->canvas->tiler, &o->curr.geometry);
		/* update the geometry */
		o->prev.geometry.x = o->curr.geometry.x;
		o->prev.geometry.y = o->curr.geometry.y;
		o->prev.geometry.w = o->curr.geometry.w;
		o->prev.geometry.h = o->curr.geometry.h;
		goto ok;
			
	}
	return;
	/* call class function */
ok:
	o->oclass->pre_process(o->cdata);
}
/**
 * To be documented
 * FIXME: To be fixed
 */
void ekeko_object_process(Ekeko_Object *o, Eina_Rectangle *r)
{
	/* call class function */
	o->oclass->process(o->cdata, r);
}
/**
 * To be documented
 * FIXME: To be fixed
 */
void ekeko_object_post_process(Ekeko_Object *o)
{	
	/* call class function */
	o->changed = EINA_FALSE;
	o->oclass->post_process(o->cdata);
}
/**
 * Validate an object, add the object to the list of valid objects
 * FIXME: To be fixed
 */
void ekeko_object_validate(Ekeko_Object *o)
{
	printf("validating\n");
	if (o->valid)
		return;
	o->valid = EINA_TRUE;
	o->canvas->valid = eina_list_append(o->canvas->valid, o);
	o->canvas->invalid = eina_list_remove(o->canvas->invalid, o);
}
/**
 * Invalidate an object, remove the object from the list of valid objects
 * FIXME: To be fixed
 */
void ekeko_object_invalidate(Ekeko_Object *o)
{
	printf("invalidating\n");
	if (!o->valid)
		return;
	o->valid = EINA_FALSE;
	o->canvas->invalid = eina_list_append(o->canvas->invalid, o);
	o->canvas->valid = eina_list_remove(o->canvas->valid, o);
	
}
/*============================================================================*
 *                                   API                                      * 
 *============================================================================*/
/**
 * To be documented
 * FIXME: To be fixed
 * FIXME this function and the object class create aren't too good, refactor them :)
 */
EAPI Ekeko_Object * ekeko_object_add(Ekeko_Canvas *c, Ekeko_Object_Class *oclass, void *cdata)
{
	Ekeko_Object *o;

	assert(oclass);
	
	o = calloc(1, sizeof(Ekeko_Object));
	assert(o);
	o->canvas = c;
	
	/* default object properties */
	o->curr.visible = EINA_FALSE; 
	
	/* TODO check the class */
	o->oclass = oclass;
	o->cdata = cdata;
	
	c->objects = eina_inlist_append(c->objects, o);
	return o;
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ekeko_object_delete(Ekeko_Object *o)
{
	/* TODO change the valid/invalid lists */
	/* update the object's list */
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ekeko_object_change_notify(Ekeko_Object *o)
{
	assert(o);
	_object_change(o);
}
/**
 * @brief Moves an object to the given coordinate
 * @param o Object to move
 * @param x X coordinate
 * @param y Y coordinate
 */
EAPI void ekeko_object_move(Ekeko_Object *o, int x, int y)
{
	Eina_Inlist *l;
	
	assert(o);
	
	if ((o->curr.geometry.x == x) && (o->curr.geometry.y == y))
	{
		goto callback;
	}
	o->curr.geometry.x = x;
	o->curr.geometry.y = y;
	/* valid */
	if (eina_rectangles_intersect(&o->curr.geometry, &o->canvas->size))
		ekeko_object_validate(o);
	else
		ekeko_object_invalidate(o);
	_object_change(o);
	/* FIXME this should happen only on the valid objects */
	for (l = (Eina_Inlist *)o->canvas->inputs; l; l = l->next)
	{
		Ekeko_Input *i = (Ekeko_Input *)l;
		
		/* if the object is inside any input, call the callback */
		if (eina_rectangle_coords_inside(&o->curr.geometry, i->pointer.x, i->pointer.y))
		{
			ekeko_input_feed_mouse_move(i, i->pointer.x, i->pointer.y, i->last_timestamp);
		}
		/* if the object was one of the inside objects, call the callback */
		else if (o == i->pointer.obj)
		{
			ekeko_input_feed_mouse_move(i, i->pointer.x, i->pointer.y, i->last_timestamp);
		}
	}
callback:
	ekeko_object_event_move_call(o);
}
/**
 * @brief Resize an object
 * @param w New width of the object
 * @param h New height of the object
 */
EAPI void ekeko_object_resize(Ekeko_Object *o, int w, int h)
{
	assert(o);
	if ((o->curr.geometry.w == w) && (o->curr.geometry.h == h))
	{
		goto callback;
	}
	o->curr.geometry.w = w;
	o->curr.geometry.h = h;
	if (eina_rectangles_intersect(&o->curr.geometry, &o->canvas->size))
		ekeko_object_validate(o);
	else
		ekeko_object_invalidate(o);
	_object_change(o);
callback:
	ekeko_object_event_resize_call(o);
}
/**
 * @brief Shows the object on the canvas
 * @param o Object to show
 */
EAPI void ekeko_object_show(Ekeko_Object *o)
{
	assert(o);
	o->curr.visible = EINA_TRUE;
	_object_change(o);
//callback:
}
/**
 * @brief Hides the object from the canvas
 * @param o Object to hide
 */
EAPI void ekeko_object_hide(Ekeko_Object *o)
{
	assert(o);
	o->curr.visible = EINA_FALSE;
	_object_change(o);
//callback:
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ekeko_object_stack_above(Ekeko_Object *o, Ekeko_Object *object_rel)
{
	assert(o);
	assert(object_rel);
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ekeko_object_stack_below(Ekeko_Object *o, Ekeko_Object *object_rel)
{
	assert(o);
	assert(object_rel);
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void * ekeko_object_class_data_get(Ekeko_Object *o)
{
	assert(o);
	
	return o->cdata;
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ekeko_Canvas * ekeko_object_canvas_get(Ekeko_Object *o)
{
	assert(o);
	
	return o->canvas;
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ekeko_object_geometry_get(Ekeko_Object *o, Eina_Rectangle *r)
{
	assert(o);
	assert(r);
	
	r->x = o->curr.geometry.x;
	r->y = o->curr.geometry.y;
	r->w = o->curr.geometry.w;
	r->h = o->curr.geometry.h;
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Eina_Bool ekeko_object_is_visible(Ekeko_Object *o)
{
	return o->curr.visible;
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ekeko_object_event_callback_add(Ekeko_Object *o, Ekeko_Event_Type etype, Ekeko_Event_Cb cb, void *data)
{
	Ekeko_Object_Cb *ocb;
	
	ocb = malloc(sizeof(Ekeko_Object_Cb));
	ocb->func = cb;
	ocb->data = data;
	
	o->callbacks[etype] = eina_inlist_append(o->callbacks[etype], ocb);
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ekeko_Object * ekeko_object_rel_get_up(Ekeko_Object *rel, Ekeko_Object_Cmp_Func cmp, void *data)
{
	Eina_Inlist *l;

	assert(rel);
	assert(cmp);
	
	for (l = (Eina_Inlist *)rel; l; l = l->prev)
	{
		Ekeko_Object *o = (Ekeko_Object*)l;
		if (cmp(o, data))
			return o;
	}
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ekeko_Object * ekeko_object_rel_get_down(Ekeko_Object *rel, Ekeko_Object_Cmp_Func cmp, void *data)
{
	Eina_Inlist *l;
	
	assert(rel);
	assert(cmp);
			
	for (l = (Eina_Inlist *)rel; l; l = l->next)
	{
		Ekeko_Object *o = (Ekeko_Object*)l;
		if (cmp(o, data))
			return o;
	}
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Eina_Bool ekeko_object_is_inside(Ekeko_Object *o, Eina_Rectangle *r)
{
	if (!(ekeko_object_geometry_is_inside(o, r)))
		return EINA_FALSE;
	
	if (!(o->oclass->is_inside))
		return EINA_TRUE;
	return o->oclass->is_inside(&o->curr.geometry, r);
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Eina_Bool ekeko_object_geometry_is_inside(Ekeko_Object *o, Eina_Rectangle *r)
{
	return eina_rectangles_intersect(&o->curr.geometry, r);
}

