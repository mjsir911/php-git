#ifndef PHP_GIT2_COMMIT
#define PHP_GIT2_COMMIT
#include <php.h>
#include <git2/commit.h>

#include "commit_arginfo.h"

extern zend_class_entry *commit_class_entry;
extern zend_object_handlers commit_object_handlers;

typedef struct commit_t {
	git_commit *commit;
	zend_object std;
} commit_t;

inline commit_t *php_git2_commit_from_obj(zend_object *obj) {
	return ((commit_t *)((char *)(obj) - XtOffsetOf(commit_t, std)));
}
#define Z_COMMIT_P(zv) php_git2_commit_from_obj(Z_OBJ_P((zv)))

extern zend_object *php_git2_commit_new(zend_class_entry *ce);
extern void php_git2_commit_free(zend_object *obj);

#elif defined REGISTER_RESOURCE // PHP_GIT2_commit
	zend_class_entry ce_commit;
	INIT_CLASS_ENTRY(ce_commit, "Commit", class_git_Commit_methods)
	commit_class_entry = zend_register_internal_class(&ce_commit);
	commit_class_entry->create_object = php_git2_commit_new;
	memcpy(&commit_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	commit_object_handlers.free_obj = php_git2_commit_free;
	commit_object_handlers.offset = XtOffsetOf(commit_t, std);
#elif defined REGISTER_FUNCTION
#endif
