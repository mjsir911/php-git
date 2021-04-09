#ifdef X
X(oid, Oid)
#else
#ifndef PHP_GIT2_OID
#define PHP_GIT2_OID
#include <php.h>
#include <git2/oid.h>

#include "oid_arginfo.h"

#define T oid
#define NOMAIN
#include "gitobj.h"

#define Z_OID_P(zv) php_git2_oid_from_obj(Z_OBJ_P((zv)))

#endif
#endif
