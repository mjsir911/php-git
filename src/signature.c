#include <php.h>
#include <git2/signature.h>
#include <zend_interfaces.h>
#include "signature.h"
#include "oid.h"
#include "repository.h"
#include "error.h"

ZEND_METHOD(git_Signature, name) {
	ZEND_PARSE_PARAMETERS_NONE();

	signature_t *signature = Z_SIGNATURE_P(ZEND_THIS);

	RETURN_STRING(O(signature)->name);
}

ZEND_METHOD(git_Signature, email) {
	ZEND_PARSE_PARAMETERS_NONE();

	signature_t *signature = Z_SIGNATURE_P(ZEND_THIS);

	RETURN_STRING(O(signature)->email);
}

/*
ZEND_METHOD(git_Signature, when) {
	ZEND_PARSE_PARAMETERS_NONE();

	signature_t *signature = Z_SIGNATURE_P(ZEND_THIS);

	RETURN_STRING(O(signature)->name);
}
*/

ZEND_METHOD(git_Signature, __debugInfo) {
	ZEND_PARSE_PARAMETERS_NONE();

	zval name, email, when;
	array_init(return_value);

	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "name", &name);
	add_assoc_zval(return_value, "name", &name);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "email", &email);
	add_assoc_zval(return_value, "email", &email);
	// zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "when", &when);
	// add_assoc_zval(return_value, "when", &when);
}
