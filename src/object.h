#ifdef X
zend_class_entry ce_object;
INIT_CLASS_ENTRY(ce_object, "Object", class_git_Object_methods);
object_class_entry = zend_register_internal_interface(&ce_object);
object_class_entry->interface_gets_implemented = php_git2_object_instanceof;
#else
#ifndef PHP_GIT2_OBJECT
#define PHP_GIT2_OBJECT
#include <php.h>
#include <git2/object.h>
#include <zend_types.h>

#include "object_arginfo.h"

#define T object
#include "gitobj.h"

#define Z_OBJECT_P(zv) php_git2_object_from_obj(Z_OBJ_P((zv)))

int php_git2_object_instanceof(zend_class_entry *interface, zend_class_entry *implementor);

#endif
#endif
