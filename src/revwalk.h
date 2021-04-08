#ifndef PHP_GIT2_REVWALK
#define PHP_GIT2_REVWALK
#include <php.h>
#include <git2/revwalk.h>
#include <zend_interfaces.h>

#include "revwalk_arginfo.h"

extern zend_class_entry *revwalk_class_entry;
extern zend_object_handlers revwalk_object_handlers;

typedef struct revwalk_t {
	git_revwalk *revwalk;
	git_oid oid;
	bool more;
	zend_object std;
} revwalk_t;

inline revwalk_t *php_git2_revwalk_from_obj(zend_object *obj) {
	return ((revwalk_t *)((char *)(obj) - XtOffsetOf(revwalk_t, std)));
}
#define Z_REVWALK_P(zv) php_git2_revwalk_from_obj(Z_OBJ_P((zv)))

extern zend_object *php_git2_revwalk_new(zend_class_entry *ce);
extern void php_git2_revwalk_free(zend_object *obj);

extern zend_object_iterator *php_git2_revwalk_get_iterator(zend_class_entry *ce, zval *object, int by_ref);

// #define le_git_revwalk_name "Git Rev-Walker"
// extern int le_git_revwalk;

// extern void php_git2_revwalk_free(zend_resource *rsrc);


#elif defined REGISTER_RESOURCE // PHP_GIT2_REVWALK
	// REGISTER_RESOURCE(le_git_revwalk, php_git2_revwalk_free, le_git_revwalk_name)
	zend_class_entry ce_revwalk;
	INIT_CLASS_ENTRY(ce_revwalk, "Revwalk", class_git_Revwalk_methods)
	revwalk_class_entry = zend_register_internal_class(&ce_revwalk);
	revwalk_class_entry->create_object = php_git2_revwalk_new;
	zend_class_implements(revwalk_class_entry, 1, zend_ce_iterator);

	memcpy(&revwalk_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	revwalk_object_handlers.free_obj = php_git2_revwalk_free;
	revwalk_object_handlers.offset = XtOffsetOf(revwalk_t, std);
#elif defined REGISTER_FUNCTION
#endif
