#include <php.h>
#include <git2/revwalk.h>
#include <git2/repository.h>
#include "revwalk.h"
#include "repository.h"
#include "oid.h"
#include "error.h"

int le_git_revwalk;

PHP_FUNCTION(git_revwalk_new) {
	zval *repo_dp;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);

	git_revwalk *walker;
	if (git_revwalk_new(&walker, repo->repo))
		RETURN_GITERROR();
	RETURN_RES(zend_register_resource(walker, le_git_revwalk));
}

PHP_FUNCTION(git_revwalk_push_range) {
	zval *revwalk_dp;
	zend_string *range;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "rP", &revwalk_dp, &range) == FAILURE)
		RETURN_THROWS();

	git_revwalk *revwalk;
	if ((revwalk = (git_revwalk *)zend_fetch_resource(Z_RES_P(revwalk_dp), le_git_revwalk_name, le_git_revwalk)) == NULL)
		RETURN_THROWS();

	if (git_revwalk_push_range(revwalk, ZSTR_VAL(range)))
		RETURN_GITERROR();

	RETURN_NULL();
}

PHP_FUNCTION(git_revwalk_push_head) {
	zval *revwalk_dp;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &revwalk_dp) == FAILURE)
		RETURN_THROWS();

	git_revwalk *revwalk;
	if ((revwalk = (git_revwalk *)zend_fetch_resource(Z_RES_P(revwalk_dp), le_git_revwalk_name, le_git_revwalk)) == NULL)
		RETURN_THROWS();

	if (git_revwalk_push_head(revwalk))
		RETURN_GITERROR();

	RETURN_NULL();
}

PHP_FUNCTION(git_revwalk_next) {
	zval *revwalk_dp;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &revwalk_dp) == FAILURE)
		RETURN_THROWS();

	git_revwalk *revwalk;
	if ((revwalk = (git_revwalk *)zend_fetch_resource(Z_RES_P(revwalk_dp), le_git_revwalk_name, le_git_revwalk)) == NULL)
		RETURN_THROWS();

	git_oid oid;
	if (git_revwalk_next(&oid, revwalk))
		RETURN_NULL();

	// copy oid
	git_oid *ret = php_git2_oid_copy(&oid);

	RETURN_RES(zend_register_resource(ret, le_git_oid));
}

void php_git2_revwalk_free(zend_resource *rsrc) {
	git_revwalk *repo = (git_revwalk  *) rsrc->ptr;

	if (repo) {
		git_revwalk_free(rsrc->ptr);
		rsrc->ptr = NULL;
	}
}
