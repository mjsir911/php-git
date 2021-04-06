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

	reference_t *ref = php_git2_reference_from_obj(php_git2_reference_new(reference_class_entry));

	if (git_reference_dwim(&ref->reference, repo->repo, ZSTR_VAL(shorthand)))
		RETURN_GITERROR();

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

	reference_t *ref = php_git2_reference_from_obj(php_git2_reference_new(reference_class_entry));

	if (git_reference_lookup(&ref->reference, repo->repo, ZSTR_VAL(name)))
		RETURN_GITERROR();

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

	git_oid oid;

	if (git_reference_name_to_id(&oid, repo->repo, ZSTR_VAL(name)))
		RETURN_GITERROR();

	RETURN_RES(zend_register_resource(php_git2_oid_copy(&oid), le_git_oid));
}

ZEND_METHOD(git_Reference, target) {
	ZEND_PARSE_PARAMETERS_NONE();

	reference_t *ref = Z_REFERENCE_P(ZEND_THIS);

	const git_oid *oid;

	if (!(oid = git_reference_target(ref->reference)))
		RETURN_NULL();

	RETURN_RES(zend_register_resource(php_git2_oid_copy(oid), le_git_oid));
}
