#include <git2/object.h>
#include <zend_types.h>

zend_object *php_git2_object_dispatch_new(git_object *obj);
char *php_git2_object_dispatch_typename(git_object_t type);
