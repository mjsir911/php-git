#ifndef PHP_GIT2_OID
#define PHP_GIT2_OID
#include <php.h>
#include <git2/oid.h>

#include "oid_arginfo.h"

extern zend_class_entry *oid_class_entry;
extern zend_object_handlers oid_object_handlers;

typedef struct oid_t {
	git_oid *oid;
	zend_object std;
} oid_t;

inline oid_t *php_git2_oid_from_obj(zend_object *obj) {
	return ((oid_t *)((char *)(obj) - XtOffsetOf(oid_t, std)));
}
#define Z_OID_P(zv) php_git2_oid_from_obj(Z_OBJ_P((zv)))

extern zend_object *php_git2_oid_new(zend_class_entry *ce);
extern void php_git2_oid_free(zend_object *obj);

#elif defined REGISTER_RESOURCE // PHP_GIT2_REPOSITORY
	zend_class_entry ce_oid;
	INIT_CLASS_ENTRY(ce_oid, "Oid", class_git_Oid_methods)
	oid_class_entry = zend_register_internal_class(&ce_oid);
	oid_class_entry->create_object = php_git2_oid_new;

	memcpy(&oid_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	oid_object_handlers.free_obj = php_git2_oid_free;
	oid_object_handlers.offset = XtOffsetOf(oid_t, std);
#elif defined REGISTER_FUNCTION
#endif
