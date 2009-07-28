#include <stdio.h>
#include <neko.h>
#include <neko_vm.h>

#include "Eon.h"
#include "eon_private.h"

typedef struct _Eon_Neko
{
	value module;
} Eon_Neko;


static void * neko_init(void)
{
	Eon_Neko *en;
	neko_vm *vm;
	value module;

	en = malloc(sizeof(Eon_Neko));
	neko_global_init(NULL);
	vm = neko_vm_alloc(NULL);
	neko_vm_select(vm);
 
	return en;
}

static void neko_shutdown(void *data)
{
	neko_global_free();
	free(data);
}

/* Handle the this attribute which is the first parameter on the call */
static Eina_Bool neko_execute(void *d, char *fname)
{
	Eon_Neko *en = d;
	value f;
	value ret;

	f = val_field(en->module, val_id(fname));
	/* FIXME the function should have three arguments? */
	if (!val_is_function(f) || val_fun_nargs(f) != 0)
		return EINA_FALSE;
	val_call0(f);
	return EINA_TRUE;
}

static Eina_Bool neko_load(void *data, char *file)
{
	Eon_Neko *en = data;
	value loader;
	value args[2];
	value exc = NULL;
	value ret;
	loader = neko_default_loader(NULL, 0);
	args[0] = alloc_string(file);
	args[1] = loader;
	ret = val_callEx(loader, val_field(loader, val_id("loadmodule")), args, 2, &exc);
	if (exc != NULL)
	{

		buffer b = alloc_buffer(NULL);
		val_buffer(b, exc);
		printf("Uncaught exception - %s\n", val_string(buffer_to_string(b)));
		return EINA_FALSE;
	}
	printf("File %s loaded correctly %d\n", file, val_type(ret));
	en->module = ret;
	return EINA_TRUE;
}

static struct _Eon_Script_Module sm =
{
	.init = neko_init,
	.shutdown = neko_shutdown,
	.load = neko_load,
	.execute = neko_execute,
};

void script_neko_init(void)
{
	eon_script_register("neko", &sm);
}
