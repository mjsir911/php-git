#include <php.h>
#include <git2/signature.h>
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
