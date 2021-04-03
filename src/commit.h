#ifndef PHP_GIT2_COMMIT
#define PHP_GIT2_COMMIT
#include <php.h>

#define le_git_commit_name "Git Commit"
extern int le_git_commit;

extern void php_git2_commit_free(zend_resource *rsrc);

#include "commit_arginfo.h"

#elif defined REGISTER_RESOURCE // PHP_GIT2_REPOSITORY
	REGISTER_RESOURCE(le_git_commit, php_git2_commit_free, le_git_commit_name)
#elif defined REGISTER_FUNCTION
	REGISTER_FUNCTION(git_commit_lookup)
#endif
