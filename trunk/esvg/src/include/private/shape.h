#ifndef SHAPE_H_
#define SHAPE_H_


/* id
 * xml:base
 * xml:lang
 * xml:space
 */
typedef struct _ESVG_Attribute_Core
{
	char *id;
} ESVG_Attribute_Core;

typedef enum _ESVG_Fill_Rule
{
	ESVG_FILL_RULE_NONZERO,
	ESVG_FILL_RULE_EVENODD,
} ESVG_Fill_Rule;

typedef enum _ESVG_Stroke_Line_Cap
{
	ESVG_STROKE_LINE_CAP_BUTT,
	ESVG_STROKE_LINE_CAP_ROUND,
	ESVG_STROKE_LINE_CAP_SQUARE,
} ESVG_Stroke_Line_Cap;

typedef enum _ESVG_Stroke_Line_Join
{
	ESVG_STROKE_LINE_JOIN_MITER,
	ESVG_STROKE_LINE_JOIN_ROUND,
	ESVG_STROKE_LINE_JOIN_BEVEL,
} ESVG_Stroke_Line_Join;

typedef enum _ESVG_Interpolation
{
	ESVG_INTERPOLATION_AUTO,
	ESVG_INTERPOLATION_SRGB,
	ESVG_INTERPOLATION_LINEAR_RGB,
} ESVG_Interpolation;

typedef struct _ESVG_Attribute_Paint
{
	ESVG_Color color;
	ESVG_Color fill;
	ESVG_Fill_Rule fill_rule;
	ESVG_Color stroke;
	char stroke_dash_array;
	ESVG_Length stroke_dashoffset;
	ESVG_Stroke_Line_Cap stroke_linecap;
	ESVG_Stroke_Line_Join stroke_linejoin;	
	double stroke_miterlimit; /* >= 1 */
	ESVG_Length stroke_width;
	ESVG_Interpolation color_interpolation;
	ESVG_Interpolation color_interpolation_rendering;
} ESVG_Attribute_Paint;

typedef struct _ESVG_Attribute_Opacity
{
	double opacity; /* 0.0 -> 1.0 */
	double stroke_opacity; /* 0.0 -> 1.0 */
	double fill_opacity; /* 0.0 -> 1.0 */
} ESVG_Attribute_Opacity;

/* display
 * image-rendering
 * pointer-events
 * shape-rendering
 * text-rendering
 * visibility
 */
typedef struct _ESVG_Attribute_Graphics
{
	
} ESVG_Attribute_Graphics;

/* clip-path
 * clip-rule
 */
typedef struct _ESVG_Attribute_Clip
{
	
} ESVG_Attribute_Clip;

/* mask
 */
typedef struct _ESVG_Attribute_Mask
{
	
} ESVG_Attribute_Mask;

/*  Filter.attrib  	filter
FilterColor.attrib 	color-interpolation-filters
FilterPrimitive.attrib 	x, y, width, height, result
FilterPrimitiveWithIn.attrib 	FilterPrimitive.attrib, in
*/

/* cursor */
typedef struct _ESVG_Attribute_Cursor
{
	
} ESVG_Attribute_Cursor;


struct _ESVG_Shape
{
	Eina_Inlist list;
	ESVG *canvas;
	Ekeko_Object *object;
	/* state */
	/* attributes */
	struct 
	{
		ESVG_Attribute_Core core;
#if 0
		ESVG_Attribute_Conditional conditional;
		ESVG_Attribute_Style style;
#endif
		ESVG_Attribute_Paint paint;
#if 0
		ESVG_Attribute_Color color;
#endif
		ESVG_Attribute_Opacity opacity;
		ESVG_Attribute_Graphics graphics;
		ESVG_Attribute_Clip clip;
		ESVG_Attribute_Mask mask;
#if 0
		ESVG_Attribute_Filter filter;
		ESVG_Attribute_Graphical_Events graphical_events;
#endif
		ESVG_Attribute_Cursor cursor;
	} attributes;
	/* implementation */
	struct
	{
		void *context;
	} engine;
};


struct _ESVG_Rect
{
	ESVG_Shape shape;
	ESVG_Coord x;
	ESVG_Coord y;
	ESVG_Length rx;
	ESVG_Length ry;
	ESVG_Length width;
	ESVG_Length height;
};

void esvg_shape_geometry_set(ESVG_Shape *s, ESVG_Coord x, ESVG_Coord y, ESVG_Length width, ESVG_Length height);

#endif /*SHAPE_H_*/