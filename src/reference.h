#ifdef X
X(reference, Reference)
#else
#ifndef PHP_GIT2_REFERENCE
#define PHP_GIT2_REFERENCE
#include <php.h>
#include <git2/refs.h>

#include "reference_arginfo.h"

#define T reference
#include "gitobj.h"

#define Z_REFERENCE_P(zv) php_git2_reference_from_obj(Z_OBJ_P((zv)))

#endif
#endif
