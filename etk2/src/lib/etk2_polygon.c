/*
 * etk2_polygon.c
 */
#include "Etk2.h"
#include "etk2_private.h"
#if 0
/*============================================================================*
 *                                  Local                                     *
 *============================================================================*/
#define PRIVATE(d) ((Etk_Polygon_Private *)((Etk_Polygon *)(d))->private)
struct _Etk_Polygon_Private
{

};

static void _geometry_calc(const Ekeko_Object *o, Event *e, void *data)
{
	Etk_Polygon *r = (Etk_Polygon *)o;
	Eina_Polygonangle geom;
	Etk_Coord x, y, w, h;

	etk_square_coords_get((Etk_Square *)r, &x, &y, &w, &h);
	eina_polygonangle_coords_from(&geom, x.final, y.final, w.final,
			h.final);
#ifdef ETK_DEBUG
	printf("[Etk_Polygon] Setting geometry of size %d %d %d %d\n",
			x.final, y.final, w.final, h.final);
#endif
	ekeko_renderable_geometry_set((Ekeko_Renderable *)r, &geom);
}

static void _render(Etk_Shape *s, Etk_Engine *func, Etk_Surface *surface, Etk_Context *context)
{
	Etk_Polygon *r;
	Etk_Polygon_Private *prv;
	Etk_Coord x, y, w, h;

	r = (Etk_Polygon *)s;
	prv = PRIVATE(r);

	etk_square_coords_get((Etk_Square *)r, &x, &y, &w, &h);
#ifdef ETK_DEBUG
	printf("[Etk_Polygon] Rendering polygonangle %p into canvas %p\n", r, c);
#endif
	func->shape->polygon(surface, context, x.final, y.final, w.final, h.final);
}

static void _ctor(void *instance)
{
	Etk_Polygon *r;
	Etk_Polygon_Private *prv;

	r = (Etk_Polygon*) instance;
	r->private = prv = ekeko_type_instance_private_get(etk_polygon_type_get(), instance);
	r->parent.parent.render = _render;
	ekeko_event_listener_add((Ekeko_Object *)r, ETK_SQUARE_X_CHANGED, _geometry_calc, EINA_FALSE, NULL);
	ekeko_event_listener_add((Ekeko_Object *)r, ETK_SQUARE_Y_CHANGED, _geometry_calc, EINA_FALSE, NULL);
	ekeko_event_listener_add((Ekeko_Object *)r, ETK_SQUARE_W_CHANGED, _geometry_calc, EINA_FALSE, NULL);
	ekeko_event_listener_add((Ekeko_Object *)r, ETK_SQUARE_H_CHANGED, _geometry_calc, EINA_FALSE, NULL);
}

static void _dtor(void *polygon)
{

}

static Eina_Bool _appendable(void *instance, void *child)
{
	if (!ekeko_type_instance_is_of(child, ETK_TYPE_ANIMATION))
	{
		return EINA_FALSE;
	}
	return EINA_TRUE;
}
/*============================================================================*
 *                                 Global                                     *
 *============================================================================*/

/*============================================================================*
 *                                   API                                      *
 *============================================================================*/
EAPI Ekeko_Type *etk_polygon_type_get(void)
{
	static Ekeko_Type *type = NULL;

	if (!type)
	{
		type = ekeko_type_new(ETK_TYPE_POLYGON, sizeof(Etk_Polygon),
				sizeof(Etk_Polygon_Private), etk_shape_type_get(),
				_ctor, _dtor, _appendable);
	}

	return type;
}

EAPI Etk_Polygon * etk_polygon_new(Etk_Canvas *c)
{
	Etk_Polygon *p;

	p = ekeko_type_instance_new(etk_polygon_type_get());
	ekeko_object_child_append((Ekeko_Object *)c, (Ekeko_Object *)p);

	return r;
}

EAPI void etk_polygon_point_add(Etk_Polygon *p, Etk_Coord c)
{
	Etk_Polygon_Private *pp;

	pp = PRIVATE(p);
	/* call the engine polygon_new */
	/* call the engine polygon_point_add */
}

#endif
