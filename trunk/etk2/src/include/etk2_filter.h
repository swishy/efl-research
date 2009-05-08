/*
 * etk2_image.h
 *
 *  Created on: 26-feb-2009
 *      Author: jl
 */
#ifndef ETK2_FILTER_H_
#define ETK2_FILTER_H_

/*============================================================================*
 *                                 Events                                     *
 *============================================================================*/
/*============================================================================*
 *                               Properties                                   *
 *============================================================================*/
Property_Id ETK_FILTER_EFFECT_X;
Property_Id ETK_FILTER_EFFECT_Y;
Property_Id ETK_FILTER_EFFECT_W;
Property_Id ETK_FILTER_EFFECT_H;
/*============================================================================*
 *                                 Class                                      *
 *============================================================================*/
typedef struct _Etk_Filter_Private Etk_Filter_Private;
struct _Etk_Filter
{
	Ekeko_Object parent;
	Etk_Filter_Private *private;
};
/*============================================================================*
 *                                Functions                                   *
 *============================================================================*/
EAPI Ekeko_Type *etk_filter_type_get(void);
EAPI Etk_Filter * etk_filter_new(Etk_Canvas *c);

#endif
