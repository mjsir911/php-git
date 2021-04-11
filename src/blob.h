#ifdef X
X(blob, Blob)
#elif defined XO
XO(blob, BLOB, Blob)
#else
#ifndef PHP_GIT2_BLOB
#define PHP_GIT2_BLOB
#include <php.h>
#include <git2/blob.h>

#include "blob_arginfo.h"

#define T blob
#include "gitobj.h"

#define Z_BLOB_P(zv) php_git2_blob_from_obj(Z_OBJ_P((zv)))

#endif
#endif
