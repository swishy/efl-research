#include <stdio.h>

#include "Equanime.h"

const char *layer_flags[] = {
	"VISIBILITY",
	"POSITION",
	"SIZE",
	"LEVEL",
};

static void _layer_desc_dump(const Equ_Layer *l)
{
	int i = 0;
	int flags;

	//printf("\t- name = %s\n");
	printf("\t- flags = ");
	while (flags)
	{
		if (flags & 1)
		{
			printf("%s ", layer_flags[i]);
		}
		flags = flags >> 1;
		i++;
	}
	printf("\n");
}

int _layer_cb(Equ_Layer *l, void *data)
{
	int *num = data;
	char *ptr;
	int i;

	printf("Layer %d\n", *num);
	*num = *num + 1;
	_layer_desc_dump(l);

	return 1;
}


static void _controller_desc_dump(const Equ_Controller *c)
{
	//printf("\t- name = %s\n");
}

int _controller_cb(Equ_Controller *c, void *data)
{
	int *num = data;
	int num_layer = 0;

	printf("Controller %d\n", *num++);
	_controller_desc_dump(c);
	equ_controller_layers_get(c, (Equ_Cb)_layer_cb, &num_layer);

	return 1;
}


/**
 * List all controllers, layers, inputs and ouputs.
 */
int main(void)
{
	int num_controller = 0;

	equ_init();
	equ_controllers_get((Equ_Cb)_controller_cb, &num_controller);
	equ_shutdown();
	return 0;
}
