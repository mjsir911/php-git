#ifdef X
X(revwalk, Revwalk)
#elif defined XI
XI(revwalk, zend_ce_iterator)
#else
#ifndef PHP_GIT2_REVWALK
#define PHP_GIT2_REVWALK
#include <php.h>
#include <git2/revwalk.h>
#include <zend_interfaces.h>
#include "oid.h"

#include "revwalk_arginfo.h"

#define T revwalk
#define E oid_t *oid;
#include "gitobj.h"
#define Z_REVWALK_P(zv) php_git2_revwalk_from_obj(Z_OBJ_P((zv)))

#endif
#endif
