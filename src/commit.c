#include <php.h>
#include <git2/commit.h>
#include <zend_interfaces.h>
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
	if (GE(git_commit_lookup(&O(commit), O(repo), O(oid))))
		RETURN_THROWS();
}

ZEND_METHOD(git_Commit, id) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(O(oid), git_commit_id(O(commit)), sizeof(*O(oid)));
}

ZEND_METHOD(git_Commit, message_encoding) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	const char *msg_encoding;
	if (GE(!(msg_encoding = git_commit_message_encoding(O(commit)))))
		RETURN_STRING("UTF-8");
	char buf[strlen(msg_encoding) + 1];
	strcpy(buf, msg_encoding);
	RETURN_STRING(buf);
}

ZEND_METHOD(git_Commit, message) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	const char *commit_msg;
	if (GE(!(commit_msg = git_commit_message(O(commit)))))
		RETURN_THROWS();

	char buf[strlen(commit_msg) + 1];
	strcpy(buf, commit_msg);
	RETURN_STRING(buf);
}

ZEND_METHOD(git_Commit, summary) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	const char *commit_summary;
	if (GE(!(commit_summary = git_commit_summary(O(commit)))))
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

	if (GE(git_signature_dup(&O(sig), git_commit_committer(O(commit)))))
		RETURN_THROWS();

	RETURN_OBJ(&sig->std);
}

ZEND_METHOD(git_Commit, author) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	signature_t *sig = php_git2_signature_from_obj(
		php_git2_signature_new(signature_class_entry)
	);

	if (GE(git_signature_dup(&O(sig), git_commit_author(O(commit)))))
		RETURN_THROWS();

	RETURN_OBJ(&sig->std);
}

ZEND_METHOD(git_Commit, tree_id) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(O(oid), git_commit_tree_id(O(commit)), sizeof(*O(oid)));
}

ZEND_METHOD(git_Commit, parents) {
	ZEND_PARSE_PARAMETERS_NONE();

	commit_t *commit = Z_COMMIT_P(ZEND_THIS);

	array_init(return_value);

	for (int i=0; i < git_commit_parentcount(O(commit)); i++) {
		zval zparent;
		object_init_ex(&zparent, commit_class_entry);
		commit_t *parent = Z_COMMIT_P(&zparent);
		git_commit_parent(&O(parent), O(commit), i);
		add_next_index_zval(return_value, &zparent);
	}
}

ZEND_METHOD(git_Commit, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "id", return_value);
	zend_call_method_with_0_params(Z_OBJ_P(return_value), Z_OBJCE_P(return_value), NULL, "__toString", return_value);
}

ZEND_METHOD(git_Commit, __debugInfo) {
	ZEND_PARSE_PARAMETERS_NONE();

	zval id, encoding, message, summary, time, committer, author, header;
	array_init(return_value);

	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "short_id", &id);
	add_assoc_zval(return_value, "id", &id);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "message_encoding", &encoding);
	add_assoc_zval(return_value, "encoding", &encoding);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "message", &message);
	add_assoc_zval(return_value, "message", &message);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "summary", &summary);
	add_assoc_zval(return_value, "summary", &summary);
	// zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "time", &time);
	// add_assoc_zval(return_value, "time", &time);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "committer", &committer);
	add_assoc_zval(return_value, "committer", &committer);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "author", &author);
	add_assoc_zval(return_value, "author", &author);
	// zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "header", &header);
	// add_assoc_zval(return_value, "header", &header);
}
