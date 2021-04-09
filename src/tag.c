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

zend_class_entry *tag_class_entry = NULL;
zend_object_handlers tag_object_handlers;

zend_object *php_git2_tag_new(zend_class_entry *ce) {
	tag_t *iter = zend_object_alloc(sizeof(tag_t), ce);
	zend_object_std_init(&iter->std, ce);
	object_properties_init(&iter->std, ce);
	iter->std.handlers = &tag_object_handlers;
	return &iter->std;
}

void php_git2_tag_free(zend_object *obj) {
	tag_t *tag = php_git2_tag_from_obj(obj);

	if (tag->tag) {
		git_tag_free(tag->tag);
	}
	zend_object_std_dtor(&tag->std);
}


ZEND_METHOD(git_Repository, lookup_tag) {
	zval *id_dp;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(id_dp, oid_class_entry)
	ZEND_PARSE_PARAMETERS_END();

	oid_t *id = Z_OID_P(id_dp);
	repository_t *repo = Z_REPOSITORY_P(ZEND_THIS);

	object_init_ex(return_value, tag_class_entry);
	tag_t *out = Z_TAG_P(return_value);
	if (GE(git_tag_lookup(&out->tag, repo->repo, &id->oid)))
		RETURN_THROWS();
	if (!out->tag)
		RETURN_NULL();
}

ZEND_METHOD(git_Repository, tags) {
	zend_string *pattern = NULL;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR_OR_NULL(pattern)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(ZEND_THIS);

	git_strarray tags;
	if (pattern)
		git_tag_list_match(&tags, ZSTR_VAL(pattern), repo->repo);
	else
		git_tag_list(&tags, repo->repo);


	array_init(return_value);
	for (char *const *tag = tags.strings; tag < tags.strings + tags.count; tag++) {
		git_object *obj;
		git_revparse_single(&obj, repo->repo, *tag);

		zval tmp;
		ZVAL_OBJ(&tmp, php_git2_object_dispatch_new(obj));
		add_assoc_zval(return_value, *tag, &tmp);
	}
}

ZEND_METHOD(git_Tag, name) {
	ZEND_PARSE_PARAMETERS_NONE();

	tag_t *tag = Z_TAG_P(ZEND_THIS);

	RETURN_STRING(git_tag_name(tag->tag));
}

ZEND_METHOD(git_Tag, target_id) {
	ZEND_PARSE_PARAMETERS_NONE();

	tag_t *tag = Z_TAG_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(&oid->oid, git_tag_target_id(tag->tag), sizeof(oid->oid));
}

ZEND_METHOD(git_Tag, id) {
	ZEND_PARSE_PARAMETERS_NONE();

	tag_t *tag = Z_TAG_P(ZEND_THIS);

	object_init_ex(return_value, oid_class_entry);
	oid_t *oid = Z_OID_P(return_value);
	memcpy(&oid->oid, git_tag_id(tag->tag), sizeof(oid->oid));
}
#include "signature.h"
ZEND_METHOD(git_Tag, tagger) {
	ZEND_PARSE_PARAMETERS_NONE();

	tag_t *this = Z_TAG_P(ZEND_THIS);

	object_init_ex(return_value, signature_class_entry);
	signature_t *sig = Z_SIGNATURE_P(return_value);
	if (git_signature_dup(&sig->signature, git_tag_tagger(this->tag)))
		RETURN_THROWS();
}
ZEND_METHOD(git_Tag, message) {
	ZEND_PARSE_PARAMETERS_NONE();

	tag_t *this = Z_TAG_P(ZEND_THIS);

	const char *message;
	if (!(message = git_tag_message(this->tag)))
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

	git_object_lookup(&git_obj, fc->repo->repo, oid, GIT_OBJECT_ANY);

	ZVAL_OBJ(&args[0], php_git2_object_dispatch_new(git_obj));

	fc->i.param_count = 1;
	fc->i.params = args;
	fc->i.retval = &ret;
	zend_call_function(&fc->i, &fc->c);
	return 0;
}

ZEND_METHOD(git_Repository, foreach_tag) {
	struct php_git2_fcall fc;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_FUNC(fc.i, fc.c)
	ZEND_PARSE_PARAMETERS_END();

	repository_t *repo = Z_REPOSITORY_P(ZEND_THIS);
	fc.repo = repo;

	git_tag_foreach(repo->repo, php_git2_tag_foreach_cb, &fc);
}
