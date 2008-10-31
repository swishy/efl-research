#ifndef EQUANIME_PRIVATE_H_
#define EQUANIME_PRIVATE_H_

/**
 * 
 */
struct _Equanime_Layer
{
	Eina_Inlist list;
	Equanime_Controller *controller;
	const Equanime_Layer_Description *desc;
	const Equanime_Layer_Functions *fncs;
	int x;
	int y;
	int w;
	int h;
	int level;
	unsigned char hidden;
	Enesim_Surface_Format format;
	void *data;
	void *ptr; /* TODO remove this? */
	Equanime_Surface *surface;
	unsigned int surface_ref; /* number of times the surface has been get */
};
/**
 * 
 */
struct _Equanime_Region
{
	Eina_Inlist list;
	Equanime_Layer *layer;
	const Equanime_Region_Description *desc;
	const Equanime_Region_Functions *fncs;
	int x;
	int y;
	int w;
	int h;
	int level;
	unsigned char hidden;
	void *data;
};
/**
 * 
 */
struct _Equanime_Controller
{
	Eina_Inlist list;
	Equanime_Layer **layers;
	int num_layers;
	const Equanime_Controller_Description *desc;
	const Equanime_Controller_Functions *fncs;
	void *data;
};
/**
 * 
 */
struct _Equanime_Output
{
	
};
/**
 * 
 */
struct _Equanime_Input
{
	
};

/**
 * 
 */
struct _Equanime_Surface
{
	Enesim_Surface *es;
	Equanime_Surface_Type type;
};

void equanime_controller_layer_register(Equanime_Controller *ec, Equanime_Layer *el);
void equanime_controller_layer_unregister(Equanime_Layer *el);
Equanime_Controller * equanime_controller_name_get_by(const char *name);


#endif /*EQUANIME_PRIVATE_H_*/