#include <php.h>
#include <git2/signature.h>
#include "signature.h"
#include "oid.h"
#include "repository.h"
#include "error.h"

zend_class_entry *signature_class_entry = NULL;
zend_object_handlers signature_object_handlers;

zend_object *php_git2_signature_new(zend_class_entry *ce) {
	signature_t *signature = zend_object_alloc(sizeof(signature_t), ce);
	zend_object_std_init(&signature->std, ce);
	object_properties_init(&signature->std, ce);
	signature->std.handlers = &signature_object_handlers;
	return &signature->std;
}

void php_git2_signature_free(zend_object *obj) {
	signature_t *signature = php_git2_signature_from_obj(obj);

	if (signature->signature) {
		git_signature_free(signature->signature);
	}
	zend_object_std_dtor(&signature->std);
}

ZEND_METHOD(git_Signature, name) {
	ZEND_PARSE_PARAMETERS_NONE();

	signature_t *signature = Z_SIGNATURE_P(ZEND_THIS);

	RETURN_STRING(signature->signature->name);
}

ZEND_METHOD(git_Signature, email) {
	ZEND_PARSE_PARAMETERS_NONE();

	signature_t *signature = Z_SIGNATURE_P(ZEND_THIS);

	RETURN_STRING(signature->signature->email);
}

/*
ZEND_METHOD(git_Signature, when) {
	ZEND_PARSE_PARAMETERS_NONE();

	signature_t *signature = Z_SIGNATURE_P(ZEND_THIS);

	RETURN_STRING(signature->signature->name);
}
*/
