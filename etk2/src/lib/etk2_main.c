/*
 * etk2_main.c
 *
 *  Created on: 07-ene-2009
 *      Author: jl
 */
#include "Etk2.h"
#include "etk2_private.h"
/*============================================================================*
 *                                  Local                                     *
 *============================================================================*/
static Ecore_Idle_Enterer *_idler = NULL;
static int _count = 0;

static int _emage_idler_cb(void *data)
{
	emage_dispatch();
	return 1;
}
/*============================================================================*
 *                                 Global                                     *
 *============================================================================*/
/*============================================================================*
 *                                   API                                      *
 *============================================================================*/
EAPI int etk_init(void)
{
	if (_count) goto done;
		eina_init();
		ecore_init();
		ekeko_init();
		emage_init();
		etk_value_init();
		etk_engine_init();
		/* create the Emage idler */
		_idler = ecore_idle_enterer_add(_emage_idler_cb, NULL);
done:
	return ++_count;
}

EAPI int etk_shutdown(void)
{
	if (_count != 1) goto done;
		ecore_idle_enterer_del(_idler);
		etk_engine_shutdown();
		etk_value_shutdown();
		emage_shutdown();
		ekeko_shutdown();
		ecore_shutdown();
		eina_shutdown();
done:
	return --_count;
}

EAPI void etk_loop(void)
{
	ecore_main_loop_begin();
}
