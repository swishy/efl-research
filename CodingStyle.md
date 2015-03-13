# Indentation #
# Naming Conventions #
  * All functions should have the verb at the end and separated by underscores
```
ekeko_object_add(Ekeko_Canvas *c);
```
  * All API functions should have the prefix EAPI
```
EAPI int eina_list_append(Eina_List * list, void *data);
```
  * Global variables but static should be underscored:
```
static int _my_global_bar;
```
  * Static functions should be underscored:
```
static int _my_local_func(void);
```
  * Functions accessible from other source files but not exported through the API should start with the project's name and then the subsystem:
```
Enesim_Rasterizer * enesim_rasterizer_new(void);
```
  * All headers files that can be included only once should have a define with the same name as the file formatted like this:
```
#ifndef ENESIM_PRIVATE_H_
#define ENESIM_PRIVATE_H_

#endif
```
# Filenames #
  * Header files that can be included more than once should be prefixed with an underscore.
```
_2x2_conv.h
```