#ifndef PHP_GIT2_CLONE
#define PHP_GIT2_CLONE
#include <php.h>

#include "clone_arginfo.h"

PHP_FUNCTION(git_clone);

#elif defined REGISTER_FUNCTION
	REGISTER_FUNCTION(git_clone)
#endif
