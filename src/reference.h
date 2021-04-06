#ifndef PHP_GIT2_REFERENCE
#define PHP_GIT2_REFERENCE
#include <php.h>
#include <git2/refs.h>

#include "reference_arginfo.h"

extern zend_class_entry *reference_class_entry;
extern zend_object_handlers reference_object_handlers;

typedef struct reference_t {
	git_reference *reference;
	zend_object std;
} reference_t;

inline reference_t *php_git2_reference_from_obj(zend_object *obj) {
	return ((reference_t *)((char *)(obj) - XtOffsetOf(reference_t, std)));
}
#define Z_REFERENCE_P(zv) php_git2_reference_from_obj(Z_OBJ_P((zv)))

extern zend_object *php_git2_reference_new(zend_class_entry *ce);
extern void php_git2_reference_free(zend_object *obj);

#elif defined REGISTER_RESOURCE // PHP_GIT2_reference
	zend_class_entry ce_reference;
	INIT_CLASS_ENTRY(ce_reference, "Reference", class_git_Reference_methods)
	reference_class_entry = zend_register_internal_class(&ce_reference);
	reference_class_entry->create_object = php_git2_reference_new;
	memcpy(&reference_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	reference_object_handlers.free_obj = php_git2_reference_free;
	reference_object_handlers.offset = XtOffsetOf(reference_t, std);
#elif defined REGISTER_FUNCTION
#endif
