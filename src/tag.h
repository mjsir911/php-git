#ifdef X
X(tag, Tag)
#elif defined XO
XO(tag, TAG)
#else
#ifndef PHP_GIT2_TAG
#define PHP_GIT2_TAG
#include <php.h>
#include <git2/tag.h>
#include <zend_interfaces.h>

#include "tag_arginfo.h"

#define T tag
#include "gitobj.h"

#define Z_TAG_P(zv) php_git2_tag_from_obj(Z_OBJ_P((zv)))

#endif
#endif
