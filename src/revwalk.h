#ifndef PHP_GIT2_REVWALK
#define PHP_GIT2_REVWALK
#include <php.h>
#include <git2/revwalk.h>

#define le_git_revwalk_name "Git Rev-Walker"
extern int le_git_revwalk;

extern void php_git2_revwalk_free(zend_resource *rsrc);

#include "revwalk_arginfo.h"

#elif defined REGISTER_RESOURCE // PHP_GIT2_REPOSITORY
	REGISTER_RESOURCE(le_git_revwalk, php_git2_revwalk_free, le_git_revwalk_name)
#elif defined REGISTER_FUNCTION
	REGISTER_FUNCTION(git_revwalk_new)
	REGISTER_FUNCTION(git_revwalk_push_range)
	REGISTER_FUNCTION(git_revwalk_push_head)
	REGISTER_FUNCTION(git_revwalk_next)
#endif
