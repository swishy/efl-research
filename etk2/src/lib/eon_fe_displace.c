/*
 * TODO
 * + On ekeko we need some kind of notifier whenever a property is an object
 * eon_fe_displace.c
 *
 *  Created on: 07-may-2009
 *      Author: jl
 */
#include "Eon.h"
#include "eon_private.h"
#define EON_FILTER_DEBUG 0
/*============================================================================*
 *                                  Local                                     *
 *============================================================================*/
#define PRIVATE(d) ((Eon_Fe_Displace_Private *)((Eon_Fe_Displace *)(d))->private)
struct _Eon_Fe_Displace_Private
{
	Eon_Filter *src;
	Eon_Filter *map;
	Enesim_Operator op;
};

/* TODO callback whenever this object is referenced */
/* create the enesim operator */
/* TODO callback whenever this object is unreferenced */
/* delete the enesim operator */


static void _ctor(void *instance)
{
	Eon_Fe_Displace *i;
	Eon_Fe_Displace_Private *prv;

	i = (Eon_Fe_Displace *) instance;
	i->private = prv = ekeko_type_instance_private_get(eon_fe_displace_type_get(), instance);
}

static void _dtor(void *filter)
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
Ekeko_Property_Id EON_FE_DISPLACE_SRC;
Ekeko_Property_Id EON_FE_DISPLACE_MAP;

EAPI Ekeko_Type *eon_fe_displace_type_get(void)
{
	static Ekeko_Type *type = NULL;

	if (!type)
	{
		type = ekeko_type_new(EON_TYPE_FILTER, sizeof(Eon_Fe_Displace),
				sizeof(Eon_Fe_Displace_Private), eon_filter_type_get(),
				_ctor, _dtor, _appendable);
		EON_FE_DISPLACE_SRC = TYPE_PROP_SINGLE_ADD(type, "src", PROPERTY_OBJECT, OFFSET(Eon_Fe_Displace_Private, src));
		EON_FE_DISPLACE_MAP = TYPE_PROP_SINGLE_ADD(type, "map", PROPERTY_OBJECT, OFFSET(Eon_Fe_Displace_Private, map));
	}

	return type;
}

EAPI Eon_Fe_Displace * eon_fe_displace_new(Eon_Canvas *c)
{
	Eon_Fe_Displace *fe;

	fe= ekeko_type_instance_new(eon_fe_displace_type_get());
	ekeko_object_child_append((Ekeko_Object *)c, (Ekeko_Object *)fe);

	return fe;
}

EAPI void eon_fe_displace_map_set(Eon_Fe_Displace *d, Eon_Filter *f)
{
	Eon_Fe_Displace_Private *prv = PRIVATE(d);
	prv->map = f;
}

EAPI void eon_fe_displace_src_set(Eon_Fe_Displace *d, Eon_Filter *f)
{
	Eon_Fe_Displace_Private *prv = PRIVATE(d);
	prv->src = f;
}
