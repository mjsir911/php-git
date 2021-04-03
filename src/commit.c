#include <php.h>
#include <git2/commit.h>
#include "commit.h"
#include "oid.h"
#include "repository.h"
#include "error.h"

int le_git_commit;

PHP_FUNCTION(git_commit_lookup) {
	git_commit *commit;
	zval *oid_dp, *repo_dp;
	git_oid *oid;
	git_repository *repo;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "rr", &repo_dp, &oid_dp) == FAILURE)
		RETURN_THROWS();

	if ((oid = (git_oid *)zend_fetch_resource(Z_RES_P(oid_dp), le_git_oid_name, le_git_oid)) == NULL)
		RETURN_THROWS();

	if ((repo = (git_repository *)zend_fetch_resource(Z_RES_P(repo_dp), le_git_repository_name, le_git_repository)) == NULL)
		RETURN_THROWS();

	if (git_commit_lookup(&commit, repo, oid))
		RETURN_GITERROR();

	RETURN_RES(zend_register_resource(commit, le_git_commit));
}

void php_git2_commit_free(zend_resource *rsrc) {
	git_commit *commit = (git_commit *) rsrc->ptr;

	if (commit) {
		git_commit_free(rsrc->ptr);
		rsrc->ptr = NULL;
	}
}
