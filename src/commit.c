#include <php.h>
#include <git2/commit.h>
#include "commit.h"
#include "oid.h"
#include "repository.h"
#include "signature.h"
#include "error.h"

ZEND_METHOD(git_Commit, __construct) {
	zval *repo_dp, *oid_dp;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
		Z_PARAM_OBJECT_OF_CLASS(oid_dp, oid_class_entry)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);
	oid_t *oid = Z_OID_P(oid_dp);

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);
	if (GE(git_commit_lookup(&commit->obj, repo->obj, oid->obj)))
		RETURN_THROWS();
}

ZEND_METHOD(git_Commit, id) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(oid->obj, git_commit_id(commit->obj), sizeof(*oid->obj));
}

ZEND_METHOD(git_Commit, message_encoding) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	const char *msg_encoding;
	if (!(msg_encoding = git_commit_message_encoding(commit->obj)))
		RETURN_STRING("UTF-8");
	char buf[strlen(msg_encoding) + 1];
	strcpy(buf, msg_encoding);
	RETURN_STRING(buf);
}

ZEND_METHOD(git_Commit, message) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	const char *commit_msg;
	if (!(commit_msg = git_commit_message(commit->obj)))
		RETURN_THROWS();

	char buf[strlen(commit_msg) + 1];
	strcpy(buf, commit_msg);
	RETURN_STRING(buf);
}

ZEND_METHOD(git_Commit, summary) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	const char *commit_summary;
	if (!(commit_summary = git_commit_summary(commit->obj)))
		RETURN_THROWS();

	char buf[strlen(commit_summary) + 1];
	strcpy(buf, commit_summary);
	RETURN_STRING(buf);
}

ZEND_METHOD(git_Commit, committer) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	signature_t *sig = php_git2_signature_from_obj(
		php_git2_signature_new(signature_class_entry)
	);

	if (git_signature_dup(&sig->obj, git_commit_committer(commit->obj)))
		RETURN_THROWS();

	RETURN_OBJ(&sig->std);
}

ZEND_METHOD(git_Commit, author) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	signature_t *sig = php_git2_signature_from_obj(
		php_git2_signature_new(signature_class_entry)
	);

	if (git_signature_dup(&sig->obj, git_commit_author(commit->obj)))
		RETURN_THROWS();

	RETURN_OBJ(&sig->std);
}

ZEND_METHOD(git_Commit, tree_id) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(oid->obj, git_commit_tree_id(commit->obj), sizeof(*oid->obj));
}
