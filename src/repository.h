#ifdef X
X(repository, Repository)
#else
#ifndef PHP_GIT2_REPOSITORY
#define PHP_GIT2_REPOSITORY
#include <php.h>
#include <git2/repository.h>

#include "repository_arginfo.h"

#define T repository
#include "gitobj.h"

#define Z_REPOSITORY_P(zv) php_git2_repository_from_obj(Z_OBJ_P((zv)))

#endif
#endif
