#include <zend_API.h>
#include <git2/revparse.h>
#include <git2/errors.h>
#include "object.h"
#include "reference.h"
#include "repository.h"
#include "error.h"

ZEND_FUNCTION(git_revparse_ext) {
	zval *repo_dp;
	zend_string *spec;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
		Z_PARAM_STR(spec)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);

	object_init_ex(return_value, reference_class_entry);
	reference_t *ref = Z_REFERENCE_P(return_value);

	git_object *trash;
	switch (GE(git_revparse_ext(&trash, &O(ref), O(repo), ZSTR_VAL(spec)))) {
		case 0:
			return; // return_value
		case GIT_ENOTFOUND:
			RETURN_NULL();
		default:
			RETURN_THROWS();
	}

}

ZEND_FUNCTION(git_revparse_single) {
	zval *repo_dp;
	zend_string *spec;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
		Z_PARAM_STR(spec)
	ZEND_PARSE_PARAMETERS_END();

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
