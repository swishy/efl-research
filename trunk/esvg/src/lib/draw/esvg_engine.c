#include "esvg_common.h"
#include "ESVG.h"
#include "esvg_private.h"
/* For now we can only have one engine, i.e one ESVG instance
 * this code is very bad, we allocate an engine on every property
 * change
 */
typedef struct _ESVG_Engine ESVG_Engine;

struct _ESVG_Engine
{
	void *data;
	unsigned int w;
	unsigned int h;
	ESVG_Engine_Type type;
	ESVG_Engine_Func *func;
};

static ESVG_Engine *_engine = NULL;
/*============================================================================*
 *                                  Local                                     * 
 *============================================================================*/
void _engine_new(void)
{
	if (!_engine)
	{
		_engine = calloc(1, sizeof(ESVG_Engine));
	}
}
/*============================================================================*
 *                                 Global                                     * 
 *============================================================================*/
void * esvg_engine_context_new(void)
{
	return _engine->func->context_new(_engine->data);
}

void esvg_engine_context_free(void *context)
{
	_engine->func->context_free(_engine->data, context);
}

void esvg_engine_rect_draw(void *context, ESVG_Rect *r, Eina_Rectangle *rclip)
{
	_engine->func->rect_draw(_engine->data, context, r, rclip);
}
/*============================================================================*
 *                                   API                                      * 
 *============================================================================*/
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Eina_Bool esvg_engine_output_size_get(unsigned int *width, unsigned int *height)
{
	if (!_engine)
		_engine_new();
	if (width) *width = _engine->w;
	if (height) *height = _engine->h;
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Eina_Bool esvg_engine_output_size_set(unsigned int width, unsigned int height)
{
	if (!_engine)
		_engine_new();
	if ((_engine->w == width) && (_engine->h == height))
		return EINA_TRUE;
	_engine->w = width;
	_engine->h = height;
	/* notify the change to the topmost svg */
#if 0	
	if (!e->background)
		return EINA_TRUE;
	
	/* if the size of the canvas is relative update the background size */
	if (esvg_length_type_is_relative(e->background->width.type))
		esvg_length_calculate(&e->background->width, e->width);
	if (esvg_length_type_is_relative(e->background->height.type))
		esvg_length_calculate(&e->background->width, e->height);
	printf("relative!!\n");
#endif
	return EINA_TRUE;
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Eina_Bool esvg_engine_set(ESVG_Engine_Type type, void *engine_data)
{
	/* engine already set */
	if ((_engine) && (_engine->type != ESVG_ENGINE_UNKNOWN))
		return EINA_FALSE;
	if (!_engine)
		_engine_new();
	_engine->data = engine_data;
	_engine->type = type;
	switch (type)
	{
		case ESVG_ENGINE_CAIRO:
		_engine->func = &esvg_engine_cairo;
		break;
		
		default:
		break;
	}
	return EINA_TRUE;
}
