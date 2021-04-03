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
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &repo_dp) == FAILURE)
		RETURN_THROWS();

	git_repository *repo;
	if ((repo = (git_repository *)zend_fetch_resource(Z_RES_P(repo_dp), le_git_repository_name, le_git_repository)) == NULL)
		RETURN_THROWS();

	git_revwalk *walker;
	if (git_revwalk_new(&walker, repo))
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
