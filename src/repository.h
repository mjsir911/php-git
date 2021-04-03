#ifndef PHP_GIT2_REPOSITORY
#define PHP_GIT2_REPOSITORY
#include <php.h>

#define le_git_repository_name "Git Repository"
extern int le_git_repository;

extern void php_git2_repository_free(zend_resource *rsrc);

#include "repository_arginfo.h"

#elif defined REGISTER_RESOURCE // PHP_GIT2_REPOSITORY
	REGISTER_RESOURCE(le_git_repository, php_git2_repository_free, le_git_repository_name)
#elif defined REGISTER_FUNCTION
	// ZEND_NS_NAMED_FE("git\\repository", "init", ZEND_FN(git_repository_init), arginfo_git_repository_init)
	REGISTER_FUNCTION(git_repository_init)
	REGISTER_FUNCTION(git_repository_commondir)
	REGISTER_FUNCTION(git_repository_open)
	REGISTER_FUNCTION(git_repository_open_bare)
	REGISTER_FUNCTION(git_repository_discover)
#endif
