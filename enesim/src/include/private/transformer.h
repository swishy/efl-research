#ifndef TRANSFORMER_H_
#define TRANSFORMER_H_

#define MATRIX_XX 0
#define MATRIX_XY 1
#define MATRIX_XZ 2
#define MATRIX_YX 3
#define MATRIX_YY 4
#define MATRIX_YZ 5
#define MATRIX_ZX 6
#define MATRIX_ZY 7
#define MATRIX_ZZ 8
#define MATRIX_SIZE 9

typedef enum
{
	ENESIM_TRANSFORMATION_IDENTITY,
	ENESIM_TRANSFORMATION_AFFINE,
	ENESIM_TRANSFORMATION_PROJECTIVE,
	ENESIM_TRANSFORMATIONS 
} Enesim_Transformation_Type;

typedef enum
{
	ENESIM_SCALE_NO,
	ENESIM_SCALE_UP,
	ENESIM_SCALE_DOWN
} Enesim_Scale;

struct _Enesim_Transformation
{
	float matrix[MATRIX_SIZE];
	Eina_F16p16 matrix_fixed[MATRIX_SIZE];
	Enesim_Transformation_Type type;
	int quality; // TODO fix this
	/* TODO also add the case were the src surface uses borders */
	Enesim_Rop rop;
#ifdef DEBUG
	Enesim_Magic magic;
#endif
};

/* identity[quality][xscale][yscale]
 * affine[quality][xscale][yscale]
 * projective[quality][xscale][yscale]
 */

typedef void (*Enesim_Transformer_Func)(Enesim_Transformation *t, Enesim_Surface *ss, Eina_Rectangle *srect, Enesim_Surface *ds, Eina_Rectangle *drect);

#endif /*TRANSFORMER_H_*/
