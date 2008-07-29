#include "enesim_generator.h"

/**
 * The enesim_generator application can generate the following files
 * include/private/surface_SURFACE_FORMAT_core.h (core)
 * src/lib/drawer/SURFACE_FORMAT.c (drawer)
 *  
 */

const char *type_names[TYPES] = {
	"uint8_t",
	"uint16_t",
	"uint32_t",
};

const char *color_names[COLORS] = {
	"red",
	"green",
	"blue",
	"alpha",
};

/* offset + length */
const int argb_offsets[COLORS] = {
	32,
	24,
	16,
	8
};

const char *rop_names[ROPS] = {
	"blend",
	"fill"
};

const char *pixel_types[PIXELS] = {
	"opaque",
	"transparent"
};

FILE *fout = NULL;


static void help(void)
{
	Format *f;
	int i = 1;
	
	printf("enesim_generator OPTION FORMAT FILE\n");
	printf("OPTION: core, drawer\n");
	printf("FORMAT: argb8888");
	f = formats[1];
	while (f)
	{
		printf(", %s", f->name);
		f = formats[++i];
	}
	printf("\n");
}

static void header(void)
{
	fprintf(fout, "/* File generated by enesim_generator, don't modify it */\n");
}

/* helper function to make uppercase a string */
void strupr(char *dst, const char *src)
{
	while (*src)
	{
		*dst = toupper(*src);
		dst++;
		src++;
	}
	*dst = '\0';
}

Format * format_from_format(Enesim_Surface_Format fmt)
{
	int i = 0;
	Format *f = formats[i];
	
	while (f)
	{
		if (f->sformat == fmt)
			return f;
		f = formats[++i];
	}
	return NULL;
}

int main(int argc, char **argv)
{	
	int i = 0;
	Format *f;
	
	if (argc < 4)
	{
		help();
		return 1;
	}
	
	fout = fopen(argv[3], "w+");
	if (!fout)
	{
		help();
		return 2;
	}
	
	f = formats[0];
	while (f)
	{
		if (!(strcmp(f->name, argv[2])))
			break;
		f = formats[++i];
	}
	if (!f)
	{
		help();
		return 3;
	}
	
	if (!(strcmp(argv[1], "core")))
	{
		header();
		core_functions(f);
	}
	else if (!strcmp(argv[1], "drawer"))
	{
		header();
		drawer_functions(f);
	}

	return 0;
}