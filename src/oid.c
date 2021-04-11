#include <php.h>
#include <git2/oid.h>
#include <zend_interfaces.h>
#include "oid.h"
#include "error.h"

zend_object *php_git2_oid_new(zend_class_entry *ce) {
	oid_t *this = zend_object_alloc(sizeof(oid_t), ce);
	O(this) = emalloc(sizeof(*O(this)));
	zend_object_std_init(&this->std, ce);
	object_properties_init(&this->std, ce);
	this->std.handlers = &oid_object_handlers;
	return &this->std;
}

void php_git2_oid_free(zend_object *obj) {
	oid_t *this = php_git2_oid_from_obj(obj);
	if (O(this))
		efree(O(this));
	zend_object_std_dtor(obj);
}

PHP_METHOD(git_Oid, __construct) {
	zend_string *sha;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(sha)
	ZEND_PARSE_PARAMETERS_END();

	oid_t *this = Z_OID_P(ZEND_THIS);
	if (GE(git_oid_fromstr(O(this), ZSTR_VAL(sha))))
		RETURN_THROWS();
}

PHP_METHOD(git_Oid, __toString) {
	zend_long len = 64;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(len)
	ZEND_PARSE_PARAMETERS_END();

	oid_t *this = Z_OID_P(ZEND_THIS);

	len++; // for the trailing null
	char buf[len];
	git_oid_tostr(buf, len, O(this));
	RETURN_STRING(buf);
}

ZEND_METHOD(git_Oid, __debugInfo) {
	ZEND_PARSE_PARAMETERS_NONE();

	zval len, sha;
	ZVAL_LONG(&len, 8);

	array_init(return_value);
	zend_call_method_with_1_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "__toString", &sha, &len);
	add_assoc_zval(return_value, "sha", &sha);

	RETURN_ARR(Z_ARR_P(return_value));
}
