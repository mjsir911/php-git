#include <zend_API.h>
#include <git2/revparse.h>
#include <git2/errors.h>
#include "object_helpers.h"
#include "reference.h"
#include "repository.h"
#include "error.h"

ZEND_FUNCTION(git_revparse_ext) {
	zval *repo_dp;
	zend_string *spec;
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OS", &repo_dp, repository_class_entry, &spec) == FAILURE)
		RETURN_THROWS();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);

	object_init_ex(return_value, reference_class_entry);
	reference_t *ref = Z_REFERENCE_P(return_value);

	git_object *trash;
	switch (GE(git_revparse_ext(&trash, &O(ref), O(repo), ZSTR_VAL(spec)))) {
		case 0:
			RETURN_OBJ(&ref->std);
		case GIT_ENOTFOUND:
			RETURN_NULL();
		default:
			RETURN_THROWS();
	}

}

ZEND_FUNCTION(git_revparse_single) {
	zval *repo_dp;
	zend_string *spec;
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OS", &repo_dp, repository_class_entry, &spec) == FAILURE)
		RETURN_THROWS();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);

	object_init_ex(return_value, reference_class_entry);

	git_object *out;
	switch (GE(git_revparse_single(&out, O(repo), ZSTR_VAL(spec)))) {
		case 0:
			RETURN_OBJ(php_git2_object_dispatch_new(out));
		case GIT_ENOTFOUND:
			RETURN_NULL();
		default:
			RETURN_THROWS();
	}
}
