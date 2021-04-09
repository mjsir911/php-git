#ifdef XF
XF(clone)
#else
#ifndef PHP_GIT2_CLONE
#define PHP_GIT2_CLONE
#include <php.h>

#include "clone_arginfo.h"


// oh my god
#define XF(fn) ZEND_FUNCTION(git_##fn);
#include __FILE__
#undef XF

#endif
#endif
