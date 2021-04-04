#include <php.h>
#include <git2/commit.h>
#include "commit.h"
#include "oid.h"
#include "repository.h"
#include "error.h"

int le_git_commit;

PHP_FUNCTION(git_commit_lookup) {
	zval *oid_dp, *repo_dp;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
		Z_PARAM_RESOURCE(oid_dp)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);
	git_oid *oid;
	if ((oid = (git_oid *)zend_fetch_resource(Z_RES_P(oid_dp), le_git_oid_name, le_git_oid)) == NULL)
		RETURN_THROWS();

	git_commit *commit;
	if (git_commit_lookup(&commit, repo->repo, oid))
		RETURN_GITERROR();

	RETURN_RES(zend_register_resource(commit, le_git_commit));
}

PHP_FUNCTION(git_commit_id) {
	zval *commit_dp;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &commit_dp) == FAILURE)
		RETURN_THROWS();

	git_commit *commit;
	if ((commit = (git_commit *)zend_fetch_resource(Z_RES_P(commit_dp), le_git_commit_name, le_git_commit)) == NULL)
		RETURN_THROWS();

	git_oid *oid = php_git2_oid_alloc();
	memcpy(oid, git_commit_id(commit), sizeof(*oid));
	RETURN_RES(zend_register_resource(oid, le_git_oid));
}

PHP_FUNCTION(git_commit_message_encoding) {
	zval *commit_dp;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &commit_dp) == FAILURE)
		RETURN_THROWS();

	git_commit *commit;
	if ((commit = (git_commit *)zend_fetch_resource(Z_RES_P(commit_dp), le_git_commit_name, le_git_commit)) == NULL)
		RETURN_THROWS();

	const char *msg_encoding;
	if (!(msg_encoding = git_commit_message_encoding(commit)))
		RETURN_STRING("UTF-8");
	char buf[strlen(msg_encoding) + 1];
	strcpy(buf, msg_encoding);
	RETURN_STRING(buf);
}

PHP_FUNCTION(git_commit_message) {
	zval *commit_dp;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &commit_dp) == FAILURE)
		RETURN_THROWS();

	git_commit *commit;
	if ((commit = (git_commit *)zend_fetch_resource(Z_RES_P(commit_dp), le_git_commit_name, le_git_commit)) == NULL)
		RETURN_THROWS();

	const char *commit_msg;
	if (!(commit_msg = git_commit_message(commit)))
		RETURN_THROWS();

	char buf[strlen(commit_msg) + 1];
	strcpy(buf, commit_msg);
	RETURN_STRING(buf);
}

PHP_FUNCTION(git_commit_summary) {
	zval *commit_dp;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &commit_dp) == FAILURE)
		RETURN_THROWS();

	git_commit *commit;
	if ((commit = (git_commit *)zend_fetch_resource(Z_RES_P(commit_dp), le_git_commit_name, le_git_commit)) == NULL)
		RETURN_THROWS();

	const char *commit_summary;
	if (!(commit_summary = git_commit_summary(commit)))
		RETURN_THROWS();

	char buf[strlen(commit_summary) + 1];
	strcpy(buf, commit_summary);
	RETURN_STRING(buf);
}

void php_git2_commit_free(zend_resource *rsrc) {
	git_commit *commit = (git_commit *) rsrc->ptr;

	if (commit) {
		git_commit_free(rsrc->ptr);
		rsrc->ptr = NULL;
	}
}
