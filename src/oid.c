#include <php.h>
#include <git2/oid.h>
#include "oid.h"
#include "error.h"

zend_class_entry *oid_class_entry = NULL;
zend_object_handlers oid_object_handlers;

zend_object *php_git2_oid_new(zend_class_entry *ce) {
	oid_t *this = zend_object_alloc(sizeof(oid_t), ce);
	zend_object_std_init(&this->std, ce);
	object_properties_init(&this->std, ce);
	this->std.handlers = &oid_object_handlers;
	return &this->std;
}

void php_git2_oid_free(zend_object *obj) {
	zend_object_std_dtor(obj);
}

PHP_METHOD(git_Oid, __construct) {
	zend_string *sha;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(sha)
	ZEND_PARSE_PARAMETERS_END();

	oid_t *this = Z_OID_P(ZEND_THIS);
	if (GE(git_oid_fromstr(&this->oid, ZSTR_VAL(sha))))
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
	git_oid_tostr(buf, len, &this->oid);
	RETURN_STRING(buf);
}
