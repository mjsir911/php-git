#ifdef X
X(signature, Signature)
#else
#ifndef PHP_GIT2_SIGNATURE
#define PHP_GIT2_SIGNATURE
#include <php.h>
#include <git2/signature.h>

#include "signature_arginfo.h"

#define T signature
#include "gitobj.h"

#define Z_SIGNATURE_P(zv) php_git2_signature_from_obj(Z_OBJ_P((zv)))

#endif
#endif
