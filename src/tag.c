#include <php.h>
#include <zend_interfaces.h>
#include <zend_API.h>
#include <git2/tag.h>
#include <git2/strarray.h>
#include <git2/revparse.h>
#include <git2/repository.h>
#include "tag.h"
#include "oid.h"
#include "repository.h"
#include "error.h"
#include "object.h"

ZEND_METHOD(git_Tag, lookup) {
	zval *id_dp, *repo_dp;
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "OO", &repo_dp, repository_class_entry, &id_dp, oid_class_entry) == FAILURE)
		RETURN_THROWS();

	oid_t *id = Z_OID_P(id_dp);
	repository_t *repo = Z_REPOSITORY_P(repo_dp);

	object_init_ex(return_value, tag_class_entry);
	tag_t *out = Z_TAG_P(return_value);
	if (GE(git_tag_lookup(&O(out), O(repo), O(id))))
		RETURN_THROWS();
	if (!O(out))
		RETURN_NULL();
}

ZEND_METHOD(git_Tag, list) {
	zval *repo_dp;
	zend_string *pattern = NULL;
	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "O|S", &repo_dp, repository_class_entry, &pattern) == FAILURE)
		RETURN_THROWS();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);

	git_strarray tags;
	if (pattern)
		git_tag_list_match(&tags, ZSTR_VAL(pattern), O(repo));
	else
		git_tag_list(&tags, O(repo));


	array_init(return_value);
	for (char *const *tag = tags.strings; tag < tags.strings + tags.count; tag++) {
		git_object *obj;
		git_revparse_single(&obj, O(repo), *tag);

		zval tmp;
		ZVAL_OBJ(&tmp, php_git2_object_dispatch_new(obj));
		add_assoc_zval(return_value, *tag, &tmp);
	}
}

ZEND_METHOD(git_Tag, name) {
	ZEND_PARSE_PARAMETERS_NONE();

	tag_t *tag = Z_TAG_P(ZEND_THIS);

	RETURN_STRING(git_tag_name(O(tag)));
}

ZEND_METHOD(git_Tag, target_id) {
	ZEND_PARSE_PARAMETERS_NONE();

	tag_t *tag = Z_TAG_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(O(oid), git_tag_target_id(O(tag)), sizeof(*O(oid)));
}
ZEND_METHOD(git_Tag, target_type) {
	ZEND_PARSE_PARAMETERS_NONE();
	tag_t *this = Z_TAG_P(ZEND_THIS);
	RETURN_STRING(php_git2_object_dispatch_typename(git_tag_target_type(O(this))));
}

ZEND_METHOD(git_Tag, id) {
	ZEND_PARSE_PARAMETERS_NONE();

	tag_t *tag = Z_TAG_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(O(oid), git_tag_id(O(tag)), sizeof(*O(oid)));
}
#include "signature.h"
ZEND_METHOD(git_Tag, tagger) {
	ZEND_PARSE_PARAMETERS_NONE();

	tag_t *this = Z_TAG_P(ZEND_THIS);

	object_init_ex(return_value, signature_class_entry);
	signature_t *sig = Z_SIGNATURE_P(return_value);
	if (git_signature_dup(&O(sig), git_tag_tagger(O(this))))
		RETURN_THROWS();
}
ZEND_METHOD(git_Tag, message) {
	ZEND_PARSE_PARAMETERS_NONE();

	tag_t *this = Z_TAG_P(ZEND_THIS);

	const char *message;
	if (!(message = git_tag_message(O(this))))
		RETURN_THROWS();
	RETURN_STRING(message);
}

ZEND_METHOD(git_Tag, __debugInfo) {
	ZEND_PARSE_PARAMETERS_NONE();

	zval id, name, tagger, message; 
	array_init(return_value);

	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "id", &id);
	zend_call_method_with_0_params(Z_OBJ(id), Z_OBJCE(id), NULL, "__toString", &id);
	add_assoc_zval(return_value, "id", &id);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "name", &name);
	add_assoc_zval(return_value, "name", &name);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "tagger", &tagger);
	add_assoc_zval(return_value, "tagger", &tagger);
	zend_call_method_with_0_params(Z_OBJ_P(ZEND_THIS), Z_OBJCE_P(ZEND_THIS), NULL, "message", &message);
	add_assoc_zval(return_value, "message", &message);
}

struct php_git2_fcall {
	zend_fcall_info i;
	zend_fcall_info_cache c;
	repository_t *repo;
};

int php_git2_tag_foreach_cb(const char *name, git_oid *oid, void *payload) {
	struct php_git2_fcall *fc = (struct php_git2_fcall *) payload;
	zval args[1], ret;

	git_object *git_obj;

	git_object_lookup(&git_obj, O(fc->repo), oid, GIT_OBJECT_ANY);

	ZVAL_OBJ(&args[0], php_git2_object_dispatch_new(git_obj));

	fc->i.param_count = 1;
	fc->i.params = args;
	fc->i.retval = &ret;
	zend_call_function(&fc->i, &fc->c);
	return 0;
}

ZEND_METHOD(git_Tag, foreach) {
	zval *repo_dp;
	struct php_git2_fcall fc;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS(), getThis(), "Of", &repo_dp, repository_class_entry, &fc.i, &fc.c) == FAILURE)
		RETURN_THROWS();

	repository_t *repo = Z_REPOSITORY_P(repo_dp);
	fc.repo = repo;

	git_tag_foreach(O(repo), php_git2_tag_foreach_cb, &fc);
}
