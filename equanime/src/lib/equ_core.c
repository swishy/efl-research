#include "Equanime.h"
#include "equ_private.h"
/*============================================================================*
 *                                  Local                                     *
 *============================================================================*/
static int _init = 0;
/*============================================================================*
 *                                   API                                      *
 *============================================================================*/
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void equ_init(void)
{
	if (_init) return;

	_init++;
	eina_init();
	eet_init();
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void equ_shutdown(void)
{
	if (_init == 1)
	{
		eina_shutdown();
		eet_shutdown();
	}
	_init--;
}