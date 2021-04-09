#ifdef X
X(commit, Commit)
#elif defined XO
XO(commit, COMMIT)
#else
#ifndef PHP_GIT2_COMMIT
#define PHP_GIT2_COMMIT
#include <php.h>
#include <git2/commit.h>

#include "commit_arginfo.h"

#define T commit
#include "gitobj.h"

#define Z_COMMIT_P(zv) php_git2_commit_from_obj(Z_OBJ_P((zv)))

#endif
#endif
