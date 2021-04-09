#include <php.h>
#include <git2/refs.h>
#include "reference.h"
#include "oid.h"
#include "repository.h"
#include "error.h"

zend_class_entry *reference_class_entry = NULL;
zend_object_handlers reference_object_handlers;

zend_object *php_git2_reference_new(zend_class_entry *ce) {
	reference_t *ref = zend_object_alloc(sizeof(reference_t), ce);
	zend_object_std_init(&ref->std, ce);
	object_properties_init(&ref->std, ce);
	ref->std.handlers = &reference_object_handlers;
	return &ref->std;
}

void php_git2_reference_free(zend_object *obj) {
	reference_t *ref = php_git2_reference_from_obj(obj);

	if (ref->reference) {
		git_reference_free(ref->reference);
	}
	zend_object_std_dtor(&ref->std);
}

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

	if (GE(git_reference_dwim(&ref->reference, repo->repo, ZSTR_VAL(shorthand))))
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

	if (GE(git_reference_lookup(&ref->reference, repo->repo, ZSTR_VAL(name))))
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

	if (GE(git_reference_name_to_id(&oid->oid, repo->repo, ZSTR_VAL(name))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Reference, target) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_t *ref = Z_REFERENCE_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);

	const git_oid *tmpoid;

	if (!(tmpoid = git_reference_target(ref->reference)))
		RETURN_NULL();

	memcpy(&oid->oid, tmpoid, sizeof(oid->oid));
}

ZEND_METHOD(git_Reference, name) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_t *ref = Z_REFERENCE_P(ZEND_THIS);

	RETURN_STRING(git_reference_name(ref->reference));
}
