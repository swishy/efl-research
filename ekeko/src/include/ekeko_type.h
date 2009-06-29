#ifndef EKEKO_TYPE_H
#define EKEKO_TYPE_H

/**
 * @brief A property can either have a single or dual state.
 */
typedef enum
{
	PROPERTY_VALUE_SINGLE_STATE,/**< Single state property */ //!< PROPERTY_VALUE_SINGLE_STATE
	PROPERTY_VALUE_DUAL_STATE   /**< Dual state property */   //!< PROPERTY_VALUE_DUAL_STATE
} Type_Property_Type;

typedef void (*Ekeko_Type_Constructor)(void *);
typedef void (*Ekeko_Type_Destructor)(void *);
typedef Eina_Bool (*Ekeko_Type_Appendable)(void *parent, void *child);

Ekeko_Type *ekeko_type_new(char *name, size_t size, size_t priv_size, Ekeko_Type *parent,
		Ekeko_Type_Constructor ctor, Ekeko_Type_Destructor dtor, Ekeko_Type_Appendable append);
void * ekeko_type_instance_new_name_from(const char *name);
void *ekeko_type_instance_new(Ekeko_Type *type);
void ekeko_type_instance_delete(void *instance);
Ekeko_Property_Id ekeko_type_property_new(Ekeko_Type *type, char *prop_name,
		Type_Property_Type prop_type, Ekeko_Value_Type value_type,
		ssize_t curr_offset, ssize_t prev_offset, ssize_t changed_offset);
void * ekeko_type_instance_private_get(Ekeko_Type *type, void *instance);
EAPI Eina_Bool ekeko_type_instance_is_of(void *instance, const char *type);

/* Some macros to make easier the addition of single and double properties */
#define TYPE_PROP_SINGLE_ADD(t, name, vt, fo)  \
	ekeko_type_property_new(t, name, PROPERTY_VALUE_SINGLE_STATE, vt, fo, 0, 0)
#define TYPE_PROP_DOUBLE_ADD(t, name, vt, co, po, cho) \
	ekeko_type_property_new(t, name, PROPERTY_VALUE_DUAL_STATE, vt, co, po, cho)
#endif /* EKEKO_TYPE.H */