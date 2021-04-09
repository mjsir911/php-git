#ifndef PHP_GIT2_REFERENCE_ITERATOR
#define PHP_GIT2_REFERENCE_ITERATOR
#include <php.h>
#include <git2/refs.h>
#include <zend_interfaces.h>
#include "reference.h"

#include "reference_iterator_arginfo.h"

extern zend_class_entry *reference_iterator_class_entry;
extern zend_object_handlers reference_iterator_object_handlers;

typedef struct reference_iterator_t {
	git_reference_iterator *reference_iterator;
	reference_t *current;
	zend_object std;
} reference_iterator_t;

inline reference_iterator_t *php_git2_reference_iterator_from_obj(zend_object *obj) {
	return ((reference_iterator_t *)((char *)(obj) - XtOffsetOf(reference_iterator_t, std)));
}
#define Z_REFERENCE_ITERATOR_P(zv) php_git2_reference_iterator_from_obj(Z_OBJ_P((zv)))

extern zend_object *php_git2_reference_iterator_new(zend_class_entry *ce);
extern void php_git2_reference_iterator_free(zend_object *obj);


// #define le_git_reference_iterator_name "Git Rev-Walker"
// extern int le_git_reference_iterator;

// extern void php_git2_reference_iterator_free(zend_resource *rsrc);


#elif defined REGISTER_RESOURCE // PHP_GIT2_REFERENCE_ITERATOR
	// REGISTER_RESOURCE(le_git_reference_iterator, php_git2_reference_iterator_free, le_git_reference_iterator_name)
	zend_class_entry ce_reference_iterator;
	INIT_CLASS_ENTRY(ce_reference_iterator, "ReferenceIterator", class_git_ReferenceIterator_methods)
	reference_iterator_class_entry = zend_register_internal_class(&ce_reference_iterator);
	reference_iterator_class_entry->create_object = php_git2_reference_iterator_new;
	zend_class_implements(reference_iterator_class_entry, 1, zend_ce_iterator);

	memcpy(&reference_iterator_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	reference_iterator_object_handlers.free_obj = php_git2_reference_iterator_free;
	reference_iterator_object_handlers.offset = XtOffsetOf(reference_iterator_t, std);
#elif defined REGISTER_FUNCTION
#endif
