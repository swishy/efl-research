#ifndef ENESIM_DRAWER_H_
#define ENESIM_DRAWER_H_

/**
 * Function to draw a point
 * d = Destination surface data
 * s = In case of using the surface as pixel source
 * color = To draw with a color or as a multiplier color in case of using s
 * mask = in case of using a mask
 */
typedef void (*Enesim_Drawer_Point)(Enesim_Surface_Data *d, Enesim_Surface_Data *s,
		unsigned int color, unsigned char *mask);
/**
 * 
 */
typedef void (*Enesim_Drawer_Span)(Enesim_Surface_Data *d, unsigned int len,
		Enesim_Surface_Data *s, unsigned int color, unsigned char *mask);

EAPI Enesim_Drawer_Point enesim_drawer_point_color_get(Enesim_Rop rop, Enesim_Surface_Format dfmt, unsigned int color);
EAPI Enesim_Drawer_Span enesim_drawer_span_color_get(Enesim_Rop rop, Enesim_Surface_Format dfmt, unsigned int color);
EAPI Enesim_Drawer_Span enesim_drawer_span_pixel_get(Enesim_Rop rop, Enesim_Surface_Format dfmt, Enesim_Surface_Format sfmt);

#endif /*ENESIM_DRAWER_H_*/