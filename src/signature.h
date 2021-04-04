#ifndef PHP_GIT2_SIGNATURE
#define PHP_GIT2_SIGNATURE
#include <php.h>
#include <git2/signature.h>

#include "signature_arginfo.h"

extern zend_class_entry *signature_class_entry;
extern zend_object_handlers signature_object_handlers;

typedef struct signature_t {
	git_signature *signature;
	zend_object std;
} signature_t;

inline signature_t *php_git2_signature_from_obj(zend_object *obj) {
	return ((signature_t *)((char *)(obj) - XtOffsetOf(signature_t, std)));
}
#define Z_SIGNATURE_P(zv) php_git2_signature_from_obj(Z_OBJ_P((zv)))

extern zend_object *php_git2_signature_new(zend_class_entry *ce);
extern void php_git2_signature_free(zend_object *obj);

#elif defined REGISTER_RESOURCE // PHP_GIT2_signature
	zend_class_entry ce_signature;
	INIT_CLASS_ENTRY(ce_signature, "Signature", class_git_Signature_methods)
	signature_class_entry = zend_register_internal_class(&ce_signature);
	signature_class_entry->create_object = php_git2_signature_new;
	memcpy(&signature_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	signature_object_handlers.free_obj = php_git2_signature_free;
	signature_object_handlers.offset = XtOffsetOf(signature_t, std);
#elif defined REGISTER_FUNCTION
#endif
