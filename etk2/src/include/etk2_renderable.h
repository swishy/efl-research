/*
 * etk2_renderable.h
 *
 *  Created on: 12-ene-2009
 *      Author: jl
 */

/*============================================================================*
 *                                  Local                                     *
 *============================================================================*/
/*============================================================================*
 *                                 Global                                     *
 *============================================================================*/
/*============================================================================*
 *                                   API                                      *
 *============================================================================*/

#ifndef ETK2_RENDERABLE_H_
#define ETK2_RENDERABLE_H_

typedef struct _Renderable_Private Renderable_Private;

struct _Renderable
{
	Object parent;
	/* TODO add the public functions like
	 * the flush function
	 */
	Renderable_Private *private;
};

Type *renderable_type_get(void);

#endif /* ETK2_RENDERABLE_H_ */
