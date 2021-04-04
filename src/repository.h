#ifndef PHP_GIT2_REPOSITORY
#define PHP_GIT2_REPOSITORY
#include <php.h>
#include <git2/repository.h>

#include "repository_arginfo.h"

extern zend_class_entry *repository_class_entry;
extern zend_object_handlers repository_object_handlers;

typedef struct repository_t {
	git_repository *repo;
	zend_object std;
} repository_t;

inline repository_t *php_git2_repository_from_obj(zend_object *obj) {
	return ((repository_t *)((char *)(obj) - XtOffsetOf(repository_t, std)));
}
#define Z_REPOSITORY_P(zv) php_git2_repository_from_obj(Z_OBJ_P((zv)))

extern zend_object *php_git2_repository_new(zend_class_entry *ce);
extern void php_git2_repository_free(zend_object *obj);


#elif defined REGISTER_RESOURCE // PHP_GIT2_REPOSITORY
	// REGISTER_RESOURCE(le_git_repository, php_git2_repository_free, le_git_repository_name)
	zend_class_entry ce_repository;
	INIT_CLASS_ENTRY(ce_repository, "Repository", class_git_Repository_methods)
	repository_class_entry = zend_register_internal_class(&ce_repository);
	repository_class_entry->create_object = php_git2_repository_new;
	memcpy(&repository_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	repository_object_handlers.free_obj = php_git2_repository_free;
	repository_object_handlers.offset = XtOffsetOf(repository_t, std);
#elif defined REGISTER_FUNCTION
	// ZEND_NS_NAMED_FE("git\\repository", "init", ZEND_FN(git_repository_init), arginfo_git_repository_init)
	// REGISTER_FUNCTION(git_repository_init)
	// REGISTER_FUNCTION(git_repository_commondir)
	// REGISTER_FUNCTION(git_repository_open)
	// REGISTER_FUNCTION(git_repository_open_bare)
	// REGISTER_FUNCTION(git_repository_discover)
#endif
