#ifdef XF
XF(revparse_ext)
XF(revparse_single)
#else
#ifndef PHP_GIT2_REVPARSE
#define PHP_GIT2_REVPARSE
#include <zend_API.h>

#include "revparse_arginfo.h"

// oh my god
#define XF(fn) ZEND_FUNCTION(git_##fn);
#include __FILE__
#undef XF

#endif
#endif
