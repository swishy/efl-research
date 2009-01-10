/*
 * etk2_container.h
 *
 *  Created on: 10-ene-2009
 *      Author: jl
 */
#ifndef ETK2_CONTAINER_H_
#define ETK2_CONTAINER_H_

typedef struct _Container_Private Container_Private;

struct _Container
{
	Object parent;
	Eina_Bool (*appendable)(const char *name);
	Container_Private *private;
};

Type *container_type_get(void);

EAPI void container_child_append(Container *p, Container *o);
EAPI void container_child_remove(Container *p, Container *o);

#endif /* ETK2_CONTAINER_H_ */
