#ifndef PHP_GIT2_OID
#define PHP_GIT2_OID
#include <php.h>
#include <git2/oid.h>

#define le_git_oid_name "Git OID"
extern int le_git_oid;

extern void php_git2_oid_free(zend_resource *rsrc);
extern git_oid* php_git2_oid_alloc(void);

#include "oid_arginfo.h"

#elif defined REGISTER_RESOURCE // PHP_GIT2_REPOSITORY
	REGISTER_RESOURCE(le_git_oid, php_git2_oid_free, le_git_oid_name)
#elif defined REGISTER_FUNCTION
	REGISTER_FUNCTION(git_oid_fromstr)
	REGISTER_FUNCTION(git_oid_tostr)
#endif
