#include <php.h>
#include <zend_interfaces.h>
#include <git2/refs.h>
#include "reference.h"
#include "oid.h"
#include "repository.h"
#include "object_helpers.h"
#include "error.h"

ZEND_METHOD(git_Reference, dwim) {
	zval *repo_dp;
	zend_string *shorthand;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
		Z_PARAM_STR(shorthand)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);

	object_init_ex(return_value, reference_class_entry);
	reference_t *ref = Z_REFERENCE_P(return_value);

	if (GE(git_reference_dwim(&O(ref), O(repo), ZSTR_VAL(shorthand))))
		RETURN_THROWS();

	RETURN_OBJ(&ref->std);
}

ZEND_METHOD(git_Reference, lookup) {
	zval *repo_dp;
	zend_string *name;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);

	object_init_ex(return_value, reference_class_entry);
	reference_t *ref = Z_REFERENCE_P(return_value);

	if (GE(git_reference_lookup(&O(ref), O(repo), ZSTR_VAL(name))))
		RETURN_THROWS();

	RETURN_OBJ(&ref->std);
}

ZEND_METHOD(git_Reference, name_to_id) {
	zval *repo_dp;
	zend_string *name;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);

	if (GE(git_reference_name_to_id(O(oid), O(repo), ZSTR_VAL(name))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Reference, target) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_t *ref = Z_REFERENCE_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);

	const git_oid *tmpoid;

	if (!(tmpoid = git_reference_target(O(ref))))
		RETURN_NULL();

	memcpy(O(oid), tmpoid, sizeof(*O(oid)));
}

ZEND_METHOD(git_Reference, peel) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_t *this = Z_REFERENCE_P(ZEND_THIS);

	git_object *obj;
	git_reference_peel(&obj, O(this), GIT_OBJECT_ANY);
	object_init_ex(return_value, oid_class_entry);
	RETURN_OBJ(php_git2_object_dispatch_new(obj));
}

ZEND_METHOD(git_Reference, name) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_t *ref = Z_REFERENCE_P(ZEND_THIS);

	RETURN_STRING(git_reference_name(O(ref)));
}
ZEND_METHOD(git_Reference, shorthand) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_t *ref = Z_REFERENCE_P(ZEND_THIS);

	RETURN_STRING(git_reference_shorthand(O(ref)));
}

ZEND_METHOD(git_Reference, __debugInfo) {
       ZEND_PARSE_PARAMETERS_NONE();

       zval shorthand, peel;
       array_init(return_value);

       zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "shorthand", &shorthand);
       add_assoc_zval(return_value, "name", &shorthand);
       zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "peel", &peel);
       add_assoc_zval(return_value, "peel", &peel);
}
