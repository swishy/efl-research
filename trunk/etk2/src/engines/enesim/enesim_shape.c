/*
 * enesim_shape.c
 *
 *  Created on: 04-feb-2009
 *      Author: jl
 */
#include "Etk2.h"
#include "etk2_private.h"
/*============================================================================*
 *                                  Local                                     *
 *============================================================================*/
static void _rect(void *surface, void *context, int x, int y, int w, int h)
{
#ifdef ETK2_DEBUG
	printf("RENDERING A RECTANGLE at %d %d %d %d\n", x, y, w, h);
#endif
}
/*============================================================================*
 *                                 Global                                     *
 *============================================================================*/
Etk_Shape_Engine etk_shape_engine_enesim = {
	.rect = _rect,
};
/*============================================================================*
 *                                   API                                      *
 *============================================================================*/

