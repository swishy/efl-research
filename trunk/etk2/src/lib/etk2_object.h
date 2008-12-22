#ifndef _OBJECT_H
#define _OBJECT_H

#include "etk2_types.h"
#include "etk2_type.h"

typedef struct _Object_Private Object_Private;

struct _Object
{
	Object_Private *private;
};

Object *object_new(void);

void object_name_set(Object *object, const char *name);
const char *object_name_get(Object *object);

void object_type_set(Object *object, Type *type);
Type *object_type_get(void);

void object_property_value_set(Object *object, char *prop_name, Type_Property_Value *value);
Type_Property_Value *object_property_value_get(Object *object, char *prop_name);

#endif
