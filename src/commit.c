#include <php.h>
#include <git2/commit.h>
#include "commit.h"
#include "oid.h"
#include "repository.h"
#include "signature.h"
#include "error.h"

zend_class_entry *commit_class_entry = NULL;
zend_object_handlers commit_object_handlers;

zend_object *php_git2_commit_new(zend_class_entry *ce) {
	commit_t *commit = zend_object_alloc(sizeof(commit_t), ce);
	zend_object_std_init(&commit->std, ce);
	object_properties_init(&commit->std, ce);
	commit->std.handlers = &commit_object_handlers;
	return &commit->std;
}

void php_git2_commit_free(zend_object *obj) {
	commit_t *commit = php_git2_commit_from_obj(obj);

	if (commit->commit) {
		git_commit_free(commit->commit);
	}
	zend_object_std_dtor(&commit->std);
}

ZEND_METHOD(git_Commit, __construct) {
	zval *repo_dp, *oid_dp;
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(repo_dp, repository_class_entry)
		Z_PARAM_OBJECT_OF_CLASS(oid_dp, oid_class_entry)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);
	oid_t *oid = Z_OID_P(oid_dp);

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);
	if (GE(git_commit_lookup(&commit->commit, repo->obj, oid->oid)))
		RETURN_THROWS();
}

ZEND_METHOD(git_Commit, id) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(oid->oid, git_commit_id(commit->commit), sizeof(*oid->oid));
}

ZEND_METHOD(git_Commit, message_encoding) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	const char *msg_encoding;
	if (!(msg_encoding = git_commit_message_encoding(commit->commit)))
		RETURN_STRING("UTF-8");
	char buf[strlen(msg_encoding) + 1];
	strcpy(buf, msg_encoding);
	RETURN_STRING(buf);
}

ZEND_METHOD(git_Commit, message) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	const char *commit_msg;
	if (!(commit_msg = git_commit_message(commit->commit)))
		RETURN_THROWS();

	char buf[strlen(commit_msg) + 1];
	strcpy(buf, commit_msg);
	RETURN_STRING(buf);
}

ZEND_METHOD(git_Commit, summary) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	const char *commit_summary;
	if (!(commit_summary = git_commit_summary(commit->commit)))
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

	if (git_signature_dup(&sig->signature, git_commit_committer(commit->commit)))
		RETURN_THROWS();

	RETURN_OBJ(&sig->std);
}

ZEND_METHOD(git_Commit, author) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	signature_t *sig = php_git2_signature_from_obj(
		php_git2_signature_new(signature_class_entry)
	);

	if (git_signature_dup(&sig->signature, git_commit_author(commit->commit)))
		RETURN_THROWS();

	RETURN_OBJ(&sig->std);
}

ZEND_METHOD(git_Commit, tree_id) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(oid->oid, git_commit_tree_id(commit->commit), sizeof(*oid->oid));
}
