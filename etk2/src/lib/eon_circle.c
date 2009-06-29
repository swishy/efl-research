/*
 * eon_circle.c
 *
 *  Created on: 28-jun-2009
 *      Author: jl
 */

#include "Eon.h"
#include "eon_private.h"
#include <limits.h>
/*============================================================================*
 *                                  Local                                     *
 *============================================================================*/
#define PRIVATE(d) ((Eon_Circle_Private *)((Eon_Circle *)(d))->private)
struct _Eon_Circle_Private
{
	Eon_Coord x;
	Eon_Coord y;
	Eon_Coord radius;
	void *engine_data;
};

static void _update_geometry(Eon_Circle *p)
{
	Eon_Circle_Private *prv = PRIVATE(p);
	Eina_Rectangle geom;

	eina_rectangle_coords_from(&geom, prv->x.final - prv->radius.final, prv ->y.final - prv->radius.final, prv->radius.final << 1, prv->radius.final << 1);
	ekeko_renderable_geometry_set((Ekeko_Renderable *)p, &geom);
}

static void _render(Eon_Shape *s, Eon_Engine *eng, void *engine_data, void *canvas_data, Eina_Rectangle *clip)
{
	Eon_Circle *p;
	Eon_Circle_Private *prv;

	p = (Eon_Circle *)s;

#ifdef EON_DEBUG
	printf("[Eon_Circle] Rendering polygon %p into canvas %p\n", r, c);
#endif
	eon_engine_circle_render(eng, engine_data, canvas_data, clip);
}

static void _ctor(void *instance)
{
	Eon_Circle *p;
	Eon_Circle_Private *prv;

	p = (Eon_Circle*) instance;
	p->private = prv = ekeko_type_instance_private_get(eon_polygon_type_get(), instance);
	p->parent.render = _render;
	p->parent.create = eon_engine_circle_create;
}

static void _dtor(void *polygon)
{

}

static Eina_Bool _appendable(void *instance, void *child)
{
	if (!ekeko_type_instance_is_of(child, EON_TYPE_ANIMATION))
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
Ekeko_Property_Id EON_CIRCLE_X;
Ekeko_Property_Id EON_CIRCLE_Y;
Ekeko_Property_Id EON_CIRCLE_RADIUS;

EAPI Ekeko_Type *eon_circle_type_get(void)
{
	static Ekeko_Type *type = NULL;

	if (!type)
	{
		type = ekeko_type_new(EON_TYPE_CIRCLE, sizeof(Eon_Circle),
				sizeof(Eon_Circle_Private), eon_shape_type_get(),
				_ctor, _dtor, _appendable);
		EON_CIRCLE_X = TYPE_PROP_SINGLE_ADD(type, "x", EON_PROPERTY_COORD, OFFSET(Eon_Circle_Private, x));
		EON_CIRCLE_Y = TYPE_PROP_SINGLE_ADD(type, "y", EON_PROPERTY_COORD, OFFSET(Eon_Circle_Private, y));
		EON_CIRCLE_RADIUS = TYPE_PROP_SINGLE_ADD(type, "radius", EON_PROPERTY_COORD, OFFSET(Eon_Circle_Private, radius));
	}

	return type;
}

EAPI Eon_Circle * eon_circle_new(Eon_Canvas *c)
{
	Eon_Circle *p;

	p = ekeko_type_instance_new(eon_circle_type_get());
	ekeko_object_child_append((Ekeko_Object *)c, (Ekeko_Object *)p);

	return p;
}

EAPI void eon_circle_x_rel_set(Eon_Circle *c, int x)
{


}

EAPI void eon_circle_x_set(Eon_Circle *c, int x)
{

}
EAPI void eon_circle_y_set(Eon_Circle *c, int y)
{

}
EAPI void eon_circle_y_rel_set(Eon_Circle *c, int y)
{

}
EAPI void eon_circle_radius_set(Eon_Circle *c, int radius)
{

}
EAPI void eon_circle_radius_rel_set(Eon_Circle *c, int radius)
{

}